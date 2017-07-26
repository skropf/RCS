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
public class RollerBlind extends Device implements Serializable {

    private int position;
    private int brightness;

    public RollerBlind(int deviceId, String name, String ip, DeviceType deviceType, String currentState) {
        super(deviceId, name, ip, deviceType, currentState);
        this.updateCurrentState();
    }

    private void updateCurrentState() {
        try {
            if (super.getCurrentState("position") != null) {
                this.position = Integer.parseInt(super.getCurrentState("position"));
            } else {
                this.position = 0;
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

    public void moveToPosition() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "setPosition", Arrays.asList("" + position)));

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
}