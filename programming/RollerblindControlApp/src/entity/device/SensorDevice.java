/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entity.device;

import android.util.Log;
import entity.Device;
import entity.DeviceType;
import mcp.CallMessage;
import mcp.administration.MCPWriter;

/**
 *
 * @author skropf
 */
public class SensorDevice extends Device {
    
    private double temperature;
    private int brightness;
    private int movement;
    
    
    public SensorDevice(int deviceId, String name, String ip, String deviceType, String currentState) {
        super(deviceId, name, ip, "SensorDevice", currentState);
        this.updateCurrentState();
    }
    
    private void updateCurrentState() {
    	try
    	{
        this.temperature = Double.parseDouble((super.getCurrentState("temperature")));
        this.brightness = Integer.parseInt(super.getCurrentState("brightness"));
    	}
    	catch(Exception ex)
    	{
    		Log.e("Exception",ex.getMessage());
    	}
    }

    public int getBrightness() {
        return brightness;
    }

    public int getMovement() {
        return movement;
    }

    public double getTemperature() {
        return temperature;
    }
    
    public void brightnessRCS() {
        new MCPWriter(super.getConnection()).send(
                new CallMessage(super.getDeviceId(), "getBrightness", null));
    }

    public void movementRCS() {
        new MCPWriter(super.getConnection()).send(
                new CallMessage(super.getDeviceId(), "getMovement", null));
    }

    public void temperatureRCS() {
        new MCPWriter(super.getConnection()).send(
                new CallMessage(super.getDeviceId(), "getTemperature", null));
    }
}
