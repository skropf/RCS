package entity.device;

import entity.Device;
import entity.DeviceType;
import java.io.Serializable;

import android.util.Log;
import mcp.CallMessage;
import mcp.administration.MCPWriter;

/**
 *
 * @author skropf
 */
public class PowerOutlet extends Device implements Serializable {

    private String state;
    
    public PowerOutlet(int deviceId, String name, String ip, String deviceType, String currentState) {
        super(deviceId, name, ip, "PowerOutlet", currentState);
        this.updateCurrentState();
    }
    
    private void updateCurrentState() {
    	try
    	{
        this.state = super.getCurrentState("state");
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
    
    public String getState() {
        return state;
    }
}
