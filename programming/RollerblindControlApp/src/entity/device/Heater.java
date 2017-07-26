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
public class Heater extends Device implements Serializable {

    private String state;
    private int temperature;
    
    public Heater(int deviceId, String name, String ip, String deviceType, String currentState) {
        super(deviceId, name, ip, "Heater", currentState);
        this.updateCurrentState();
    }
    
    private void updateCurrentState() {
    	try
    	{
        this.state = super.getCurrentState("state");
        this.temperature = Integer.parseInt(super.getCurrentState("temperature"));
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
    
    public void setTemperature(int temperature) {
        this.temperature = temperature;
    }
    
    public int getTemperature() {
        return temperature;
    }
    
    public void setCondition() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "setTemperatureCondition", Arrays.asList(""+temperature)));
        
        super.addCurrentState("temperature=" + temperature);
    }
    
    public void removeCondition() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "removeCondition", null));
        
        temperature = -1;
        super.addCurrentState("temperature=" + temperature);
    }
    
    public String getState() {
        return state;
    }
}
