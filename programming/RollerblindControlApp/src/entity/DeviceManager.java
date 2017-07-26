package entity;

import java.util.Dictionary;
import java.util.HashMap;
import java.util.Map.Entry;

public class DeviceManager {
	private DeviceManager(){}
	private DeviceAddedListener listener;
	public void addListener(DeviceAddedListener listener)
	{
		this.listener = listener;
	}
	private static DeviceManager instance = new DeviceManager();
	public static DeviceManager getInstance()
	{
		return instance;
	}
	public HashMap<Integer,Device> deviceDict = new HashMap<Integer,Device>();
	public void add(Device d)
	{
		deviceDict.put(d.getDeviceId(), d);
		if(listener!=null)listener.onDeviceAdded(d);
	}
	public void changeConnectionType(String con)
	{
		for(Entry<Integer,Device> entry : deviceDict.entrySet())
		{
			entry.getValue().setConnection(con);
		}
	}
	public Device get(int id)
	{
		return deviceDict.get(id);
	}
}
