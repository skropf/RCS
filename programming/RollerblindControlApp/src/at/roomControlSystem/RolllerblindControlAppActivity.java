/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package at.roomControlSystem;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;

import util.VerticalSeekBar;
import util.VerticalSeekBar.OnSeekBarChangeListener;

import entity.Device;
import entity.DeviceAddedListener;
import entity.DeviceManager;
import entity.MessageInterpreter;
import entity.ResultMessageListener;
import entity.device.RollerBlind;
import entity.device.SensorDevice;

import mcp.CallMessage;
import mcp.Message;
import mcp.ResultMessage;
import mcp.administration.MCPADKListener;
import mcp.administration.MCPADKWriter;
import mcp.administration.MCPWriter;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import android.hardware.usb.UsbAccessory;
import android.hardware.usb.UsbManager;

public class RolllerblindControlAppActivity extends Activity implements DeviceAddedListener, ResultMessageListener, OnSeekBarChangeListener {
	private static final String TAG = "DemoKit";

	private static final String ACTION_USB_PERMISSION = "com.google.android.DemoKit.action.USB_PERMISSION";

	private UsbManager mUsbManager;
	private PendingIntent mPermissionIntent;
	private boolean mPermissionRequestPending;
	private RollerBlind mRollerblind;

	UsbAccessory mAccessory;
	ParcelFileDescriptor mFileDescriptor;
	FileInputStream mInputStream;
	FileOutputStream mOutputStream;


	private final BroadcastReceiver mUsbReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (action.endsWith("USB_PERMISSION")) {//TODO
				synchronized (this) {
					UsbAccessory accessory = (UsbAccessory) intent.getParcelableExtra(UsbManager.EXTRA_ACCESSORY);
					if (intent.getBooleanExtra(
							UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
						openAccessory(accessory);
					} else {
						Log.d(TAG, "permission denied for accessory "
								+ accessory);
					}
					mPermissionRequestPending = false;
					checkConnectionType();
				}
			} else if (UsbManager.ACTION_USB_ACCESSORY_DETACHED.equals(action)) {
				UsbAccessory accessory = (UsbAccessory) intent.getParcelableExtra(UsbManager.EXTRA_ACCESSORY);
				if (accessory != null && accessory.equals(mAccessory)) {
					closeAccessory();
				}
				checkConnectionType();
			}
		}
	};
	VerticalSeekBar mBar;

	private SensorDevice mSensorDevice;

	private EditText mBrightnessCondition;

	private TextView mTextViewTemperature;

	private TextView mTextViewLum;
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.main);
		DeviceManager.getInstance().addListener(this);
		MessageInterpreter.getInstance().addResultMessageListener(this);
		ContextHolder.getInstance().setContext(this);
		mUsbManager = (UsbManager) getSystemService(Context.USB_SERVICE);
		mPermissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(
				ACTION_USB_PERMISSION), 0);
		IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
		filter.addAction(UsbManager.ACTION_USB_ACCESSORY_DETACHED);
		registerReceiver(mUsbReceiver, filter);

		if (getLastNonConfigurationInstance() != null) {
			mAccessory = (UsbAccessory) getLastNonConfigurationInstance();
			openAccessory(mAccessory);
		}

		enableControls(false);
		mBar =  (VerticalSeekBar) findViewById(R.id.verticalSeekBar);
		mBar.setOnSeekBarChangeListener(this);
		mBrightnessCondition = (EditText) findViewById(R.id.editTextBrightnessCondition);
		checkConnectionType();
		sendDeviceMessage();
		mTextViewTemperature = (TextView) findViewById(R.id.TextViewTemperature);
		mTextViewLum = (TextView) findViewById(R.id.TextViewLum);
	}

	@Override
	public Object onRetainNonConfigurationInstance() {
		if (mAccessory != null) {
			return mAccessory;
		} else {
			return super.onRetainNonConfigurationInstance();
		}
	}

	@Override
	public void onResume() {
		super.onResume();

		if (MCPADKWriter.getInstance().getFileOutputStream() != null && MCPADKListener.getInstance().getFileInputStream() != null) {
			return;
		}

		UsbAccessory[] accessories = mUsbManager.getAccessoryList();
		UsbAccessory accessory = (accessories == null ? null : accessories[0]);
		if (accessory != null) {
			if (mUsbManager.hasPermission(accessory)) {
				openAccessory(accessory);
			} else {
				synchronized (mUsbReceiver) {
					if (!mPermissionRequestPending) {
						mUsbManager.requestPermission(accessory,
								mPermissionIntent);
						mPermissionRequestPending = true;
					}
				}
			}
		} else {
			Log.d(TAG, "mAccessory is null");
		}
		checkConnectionType();
		sendDeviceMessage();
		
	}

	@Override
	public void onPause() {
		super.onPause();
		closeAccessory();
	}

	@Override
	public void onDestroy() {
		unregisterReceiver(mUsbReceiver);
		super.onDestroy();
	}

	private void openAccessory(UsbAccessory accessory) {
		this.mAccessory = accessory;
		mUsbManager = (UsbManager) ContextHolder.getInstance().getContext().getSystemService(Context.USB_SERVICE);
		mFileDescriptor = mUsbManager.openAccessory(accessory);
		
		MCPADKWriter.getInstance().setUsbFileDescriptor(mFileDescriptor);
		MCPADKListener.getInstance().setUsbFileDescriptor(mFileDescriptor);
		Thread t = new Thread(MCPADKListener.getInstance());
		t.start();
		enableControls(true);
		sendDeviceMessage();
		checkConnectionType();
	}

	private void closeAccessory() {
		enableControls(false);
		MCPADKWriter.getInstance().setUsbFileDescriptor(null);
		MCPADKListener.getInstance().setUsbFileDescriptor(null);
	}

	protected void enableControls(boolean enable) {
		//mBar.setEnabled(enable);
	}
	public void onButtonClick(View v)
	{
		if(mRollerblind==null)
		{
			MCPWriter w = new MCPWriter("ADK");
			w.send(new CallMessage(0,"getDevices",null));
		}
		else
		{
			this.mRollerblind.setPosition(500);
		}
	}

	public void onDeviceAdded(final Device d) {
		/*final TextView t = (TextView) findViewById(R.id.textViewMessage);
		t.post(new Runnable()
		{
			public void run() {
				t.setText(d.getName());
			}
		});*/
		if(d.getClass()==RollerBlind.class||d.getType()=="RollerBlind")
		{
					mRollerblind = (RollerBlind) d;
			
		}
		if(d.getClass()==SensorDevice.class||d.getType()=="SensorDevice")
		{
			Log.d("onDeviceAdded","sensordevice added");
			this.mSensorDevice = (SensorDevice) d;
			Thread t = new Thread(){
				@Override
				public void run() {
					while(true)
					{
						try {
							sleep(2000);
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						if(mSensorDevice!=null)
						{
							mSensorDevice.brightnessRCS();
							mSensorDevice.temperatureRCS();
						}
					}
				};
			};
			t.start();
		}
	}

	public void onResultMessageRecieved(final ResultMessage msg) {
		/*final TextView t = (TextView) findViewById(R.id.textViewMessage);
		t.post(new Runnable()
		{
			public void run() {
				t.setText(msg.getResult());
			}
		});*/
		final String erg =msg.getResult().substring(0, msg.getResult().length() - 1);
		
		mTextViewLum.post(new Runnable() {
			
			public void run() {
				if(msg.getDeviceId() == mSensorDevice.getDeviceId())
					if(msg.getResult().split("=")[0].equals("brightness"))
						mTextViewLum.setText(erg.split("=")[1]+ " lum");
			}
		});
		mTextViewTemperature.post(new Runnable() {
			
			public void run() {
				if(msg.getDeviceId() == mSensorDevice.getDeviceId())
					if(msg.getResult().split("=")[0].equals("temperature"))
					{
						mTextViewTemperature.setText(erg.split("=")[1]+ " C");
					}
			}
		});
		
	}

	public void onProgressChanged(VerticalSeekBar seekBar, int progress,
			boolean fromUser) {
		// TODO Auto-generated method stub
		
	}

	public void onStartTrackingTouch(VerticalSeekBar seekBar) {
		// TODO Auto-generated method stub
		
	}

	public void onStopTrackingTouch(VerticalSeekBar seekBar) {
		if(mRollerblind!=null)
		{
			int progress = mBar.getProgress();
			progress = Math.abs(1000-progress);
			//MCPWriter wr = new MCPWriter("ADK");
			MCPADKWriter.getInstance().send(new CallMessage(2 ,"setPosition",Arrays.asList(progress +"")));
		}
	}
	public void checkConnectionType()
	{
		if(mAccessory!=null)
		{
			DeviceManager.getInstance().changeConnectionType("ADK");
		}
		else
		{
			/*Runtime runtime = Runtime.getRuntime();
			Process proc;
			try {
				proc = runtime.exec("ping 192.168.1.2 -c 1");
				proc.waitFor();
				int exit = proc.exitValue();
				if (exit == 0) { // normal exit
					DeviceManager.getInstance().changeConnectionType("192.168.1.2");
					this.enableControls(true);
				} else { 
					this.enableControls(false);
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} // other servers, for example
 catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}*/
			DeviceManager.getInstance().changeConnectionType("192.168.1.2");
		}
	}
	public void sendDeviceMessage()
	{
		if(mAccessory!=null)
		{
			MCPWriter wr = new MCPWriter("ADK");
			wr.send(new CallMessage(0 ,"getDevices", null));
		}
		else
		{
			/*Runtime runtime = Runtime.getRuntime();
			Process proc;
			try {
				proc = runtime.exec("ping 192.168.1.2 -c 1");
				proc.waitFor();
				int exit = proc.exitValue();
				if (exit == 0) { // normal exit
					DeviceManager.getInstance().changeConnectionType("192.168.1.2");
					this.enableControls(true);
				} else { 
					this.enableControls(false);
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} // other servers, for example
 catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}*/

			MCPWriter wr = new MCPWriter("192.168.1.2");
			wr.send(new CallMessage(0 ,"getDevices", null));
			
		}
	} 
	public void setConditionButtonClicked(View v)
	{
		if(mBrightnessCondition.getText()==null||mBrightnessCondition.getText().toString()==""||mRollerblind==null)return;
		try
		{
		mRollerblind.setBrightness(Integer.parseInt(mBrightnessCondition.getText().toString()));
		mRollerblind.setCondition();
		}
		catch(Exception ex)
		{
		   Log.d("Exception",ex.getMessage());
		}
	}
}
