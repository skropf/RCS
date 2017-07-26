package entity.device;

import entity.Device;
import entity.DeviceType;
import java.io.Serializable;
import mcp.CallMessage;
import mcp.administration.MCPSocketWriter;

/**
 *
 * @author skropf
 */
public class PowerOutlet extends Device implements Serializable {

    private String state;

    public PowerOutlet(int deviceId, String name, String ip, DeviceType deviceType, String currentState) {
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

    public String getState() {
        return state;
    }
}