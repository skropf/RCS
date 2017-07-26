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
public class Fan extends Device implements Serializable {

    private String state;
    private int temperature;

    public Fan(int deviceId, String name, String ip, DeviceType deviceType, String currentState) {
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
            if (super.getCurrentState("temperature") != null) {
                this.temperature = Integer.parseInt(super.getCurrentState("temperature"));
            } else {
                this.temperature = -1;
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

    public void setTemperature(int temperature) {
        this.temperature = temperature;
    }

    public int getTemperature() {
        return temperature;
    }

    public void setCondition() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "setTemperatureCondition", Arrays.asList("" + temperature)));

        super.addCurrentState("temperature=" + temperature);
    }

    public void removeCondition() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "removeCondition", null));

        temperature = -1;
        super.addCurrentState("temperature=" + temperature);
    }

    public String getState() {
        return state;
    }
}