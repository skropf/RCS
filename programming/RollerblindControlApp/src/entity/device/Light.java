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
public class Light extends Device implements Serializable {

    private String state;
    private int brightness;
    
    public Light(int deviceId, String name, String ip, String deviceType, String currentState) {
        super(deviceId, name, ip, "Light", currentState);
        this.updateCurrentState();
    }
    
    private void updateCurrentState() {
    	try
    	{
        this.state = super.getCurrentState("state");
        this.brightness = Integer.parseInt(super.getCurrentState("brightness"));
    	
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
    
    public void setBrightness(int brightness) {
        this.brightness = brightness;
    }
    
    public int getBrightness() {
        return brightness;
    }
    
    public void setCondition() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "setBrightnessCondition", Arrays.asList(""+brightness)));
        
        super.addCurrentState("brightness=" + brightness);
    }
    
    public void removeCondition() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "removeCondition", null));
        
        brightness = -1;
        super.addCurrentState("brightness=" + brightness);
    }
    
    public String getState() {
        return state;
    }
}
