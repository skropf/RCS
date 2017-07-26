package mcp.administration;

import java.io.BufferedReader;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;


import entity.MessageInterpreter;
import android.content.Context;
import android.hardware.usb.UsbAccessory;
import android.hardware.usb.UsbManager;
import android.os.ParcelFileDescriptor;
import android.util.Log;
import at.roomControlSystem.ContextHolder;

public class MCPADKListener implements Runnable {

	static MCPADKListener instance = new MCPADKListener();
	private UsbAccessory acc;
	private UsbManager mUsbManager;
	private ParcelFileDescriptor mFileDescriptor;
	private FileInputStream mInputStream;
	private BufferedReader mReader;
	private MessageInterpreter mInterpreter;
	private MCPADKListener()
	{
		mInterpreter = MessageInterpreter.getInstance();
	}
	public static MCPADKListener getInstance()
	{
		return instance;
	}
	public ParcelFileDescriptor getUsbFileDescriptor() {
		return mFileDescriptor;
	}
	public void setUsbFileDescriptor(ParcelFileDescriptor desc) {
		this.mFileDescriptor = desc;
		if(mFileDescriptor==null)
		{
			closeAccessory();
			return;
		}
		openFileDescriptor();
	}
	private void closeAccessory() {

		try {
			if (mFileDescriptor != null) {
				mFileDescriptor.close();
			}
		} catch (IOException e) {
		} finally {
			mFileDescriptor = null;
		}
	}
	private void openFileDescriptor() {
		if (mFileDescriptor != null) {
			FileDescriptor fd = mFileDescriptor.getFileDescriptor();
			 mInputStream = new FileInputStream(fd);
			 mReader = new BufferedReader(new InputStreamReader(mInputStream));
			 Thread t = new Thread(this);
			 t.start();
			Log.d("openAccessory", "accessory opened");
		} else {
			Log.d("openAccessory", "accessory open fail");
		}
	}
	public FileInputStream getFileInputStream()
	{
		return mInputStream;
	}
	public void setFileInputStream(FileInputStream s)
	{
		mInputStream = s;
	}
	public void run() {
		String line;
		while(true)
		{
			try {
				Thread.sleep(20);
				byte[] buffer = new byte[16384];
				int ret = mInputStream.read(buffer);
				line = "";
				for(int i=0;i<ret;i++)
				{
					line += (char)buffer[i];
					Log.e("MCPADKListener", line);
				}
				if(line!=null)
				{
					Log.e("MCPADKListener","message received:  " + line);
					mInterpreter.interprete(line, "ADK");
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
	}

}
