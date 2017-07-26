package entity.device;

import entity.Device;
import entity.DeviceType;
import java.io.Serializable;
import java.util.Arrays;

import android.util.Log;
import mcp.CallMessage;
import mcp.administration.MCPWriter;

/**
 *
 * @author skropf
 */
public class Fan extends Device implements Serializable {
    
    private String state;
    private int humidity;
    
    public Fan(int deviceId, String name, String ip, String deviceType, String currentState) {
        super(deviceId, name, ip, "Fan", currentState);
        this.updateCurrentState();
    }
    
    private void updateCurrentState() {
    	try
    	{
        this.state = super.getCurrentState("state");
        this.humidity = Integer.parseInt(super.getCurrentState("temperature"));
    	}
    	catch(Exception ex)
    	{
    		Log.e("Exception",ex.getMessage());
    	}
    }
    
    public void turnOn() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "turnOn", null));
        
        state = "on";
        super.addCurrentState("state=" + state);
    }
    
    public void turnOff() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "turnOff", null));
        
        state = "off";
        super.addCurrentState("state=" + state);
    }
    
    public void setHumidity(int humidity) {
        this.humidity = humidity;
    }
    
    public int getHumidity() {
        return humidity;
    }
    
    public void setCondition() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "setHumidityCondition", Arrays.asList(""+humidity)));
        
        super.addCurrentState("humidity=" + humidity);
    }
    
    public void removeCondition() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "removeCondition", null));
        
        humidity = -1;
        super.addCurrentState("humidity=" + humidity);
    }
    
    public String getState() {
        return state;
    }
}