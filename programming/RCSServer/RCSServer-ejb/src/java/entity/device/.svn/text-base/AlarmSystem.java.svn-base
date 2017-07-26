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
public class AlarmSystem extends Device implements Serializable {

    private int alarm;
    private String state, subscription;

    public AlarmSystem(int deviceId, String name, String ip, DeviceType deviceType, String currentState) {
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
            if (super.getCurrentState("subscription") != null) {
                this.subscription = super.getCurrentState("subscription");
            } else {
                this.subscription = "unsubscribed";
            }
            if (super.getCurrentState("alarm") != null) {
                this.alarm = Integer.parseInt(super.getCurrentState("alarm"));
            } else {
                this.alarm = 0;
            }
        } catch (Exception ex) {
            System.err.println(super.getDeviceId() + " - " + super.getName() + ": " + ex.toString());
        }
    }

    public void turnOn() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "turnOn", null));

        this.state = "on";
        super.addCurrentState("state=" + state);
        
        subscribe();
    }

    public void turnOff() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "turnOff", null));

        this.state = "off";
        super.addCurrentState("state=" + state);
    }

    public void subscribe() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "subscribe", null));

        subscription = "subscribed";
        super.addCurrentState("subscription=" + subscription);
    }

    public void unsubscribe() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "unsubscribe", null));

        subscription = "unsubscribed";
        super.addCurrentState("subscription=" + subscription);
    }

    public void alarmOff() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "setAlarm", Arrays.asList("0")));

        this.alarm = 0;
        super.addCurrentState("alarm=" + alarm);
    }

    public String getSubscribtion() {
        return subscription;
    }

    public String getState() {
        return state;
    }
}