package mcp.administration;

import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;


import android.content.Context;
import android.hardware.usb.UsbAccessory;
import android.hardware.usb.UsbManager;
import android.os.ParcelFileDescriptor;
import android.util.Log;
import at.roomControlSystem.ContextHolder;
import mcp.Message;

public class MCPADKWriter implements IMCPWriter {

	static MCPADKWriter instance = new MCPADKWriter();
	private UsbAccessory acc;
	private UsbManager mUsbManager;
	private ParcelFileDescriptor mFileDescriptor;
	private FileOutputStream mOutputStream;
	private PrintWriter mPrintWriter;
	private MCPADKWriter()
	{
	}
	public static MCPADKWriter getInstance()
	{
		return instance;
	}
	public UsbAccessory getUsbAccessory() {
		return acc;
	}
	public void setUsbFileDescriptor(ParcelFileDescriptor desc) {
		this.mFileDescriptor = desc;
		if(desc==null)
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
	public FileOutputStream getFileOutputStream()
	{
		return mOutputStream;
	}
	public void setFileOutputStream(FileOutputStream s)
	{
		mOutputStream = s;
		mPrintWriter = new PrintWriter(mOutputStream);
	}
	private void openFileDescriptor() {
		if (mFileDescriptor != null) {
			FileDescriptor fd = mFileDescriptor.getFileDescriptor();
			mOutputStream = new FileOutputStream(fd);
			mPrintWriter = new PrintWriter(mOutputStream);
			
			
			Log.d("openAccessory", "accessory opened");
		} else {
			Log.d("openAccessory", "accessory open fail");
		}
	}
	public void send(Message message) {
		if(mPrintWriter!=null)
		{
		mPrintWriter.print(message.toString());
		mPrintWriter.flush();
		}
	}

}
