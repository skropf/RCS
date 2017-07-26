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
public class RollerBlind extends Device implements Serializable {

    private int position;
    private int brightness;
    
    public RollerBlind(int deviceId, String name, String ip, String deviceType, String currentState) {
        super(deviceId, name, ip, "RollerBlind", currentState);
        this.updateCurrentState();
    }
    
    private void updateCurrentState() {
    	try
    	{
        this.position = Integer.parseInt(super.getCurrentState("position"));
        this.brightness = Integer.parseInt(super.getCurrentState("brightness"));
    	}
    	catch(Exception ex)
    	{
    		Log.e("Exception",ex.getMessage());
    	}
    }
    
    public void moveToPosition() {
        new MCPWriter(super.getConnection()).send(
                new CallMessage(super.getDeviceId(), "setPosition", Arrays.asList(""+position)));
        
        super.addCurrentState("position=" + position);
    }
    
    public void setPosition(int position) {
        this.position = position;
    }
    
    public int getPosition() {
        return position;
    }
    
    public void setBrightness(int brightness) {
        this.brightness = brightness;
    }
    
    public int getBrightness() {
        return brightness;
    }
    
    public void setCondition() {
        new MCPWriter(super.getConnection()).send(
                new CallMessage(super.getDeviceId(), "setBrightnessCondition", Arrays.asList(""+brightness)));
        
        super.addCurrentState("brightness=" + brightness);
    }
    
    public void removeCondition() {
        new MCPWriter(super.getConnection()).send(
                new CallMessage(super.getDeviceId(), "removeCondition", null));
        
        brightness = -1;
        super.addCurrentState("brightness=" + brightness);
    }
}
