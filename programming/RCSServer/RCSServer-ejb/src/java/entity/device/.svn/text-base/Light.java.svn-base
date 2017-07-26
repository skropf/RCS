package entity.device;

import entity.Device;
import entity.DeviceType;
import java.io.Serializable;
import java.util.Arrays;
import mcp.CallMessage;
import mcp.administration.MCPSocketWriter;

/**
 *
 * @author skropf
 */
public class Light extends Device implements Serializable {

    private String state;
    private int brightness;

    public Light(int deviceId, String name, String ip, DeviceType deviceType, String currentState) {
        super(deviceId, name, ip, deviceType, currentState);
        this.updateCurrentState();
    }

    private void updateCurrentState() {
        try {
            if (super.getCurrentState("state") != null) {
                this.state = super.getCurrentState("state");
            } else {
                this.state = "off";
            }
            if (super.getCurrentState("brightness") != null) {
                this.brightness = Integer.parseInt(super.getCurrentState("brightness"));
            } else {
                this.brightness = -1;
            }
        } catch (Exception ex) {
            System.err.println(super.getDeviceId() + " - " + super.getName() + ": " + ex.toString());
        }
    }

    public void turnOn() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "turnOn", null));

        state = "on";
        super.addCurrentState("state=" + state);
    }

    public void turnOff() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "turnOff", null));

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
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "setBrightnessCondition", Arrays.asList("" + brightness)));

        super.addCurrentState("brightness=" + brightness);
    }

    public void removeCondition() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "removeCondition", null));

        brightness = -1;
        super.addCurrentState("brightness=" + brightness);
    }

    public String getState() {
        return state;
    }
}