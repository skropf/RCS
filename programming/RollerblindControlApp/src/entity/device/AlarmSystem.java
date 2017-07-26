package entity.device;

import entity.Device;
import entity.DeviceType;
import java.io.Serializable;
import java.util.Arrays;
import java.util.List;
import mcp.CallMessage;
import mcp.administration.MCPWriter;

/**
 *
 * @author skropf
 */
public class AlarmSystem extends Device implements Serializable {

    private String state, subscription;
    private List<String> sensorList, activeSensorList, inActiveSensorList;
    private List<String> actorList, activeActorList, inActiveActorList;

    public AlarmSystem(int deviceId, String name, String ip, String deviceType, String currentState) {
        super(deviceId, name, ip, "AlarmSystem", currentState);
        this.updateCurrentState();
    }

    private void updateCurrentState() {
        this.state = super.getCurrentState("state");
        this.subscription = super.getCurrentState("subscription");
        this.sensorList = Arrays.asList(super.getCurrentState("sensorList").split(","));
        this.activeSensorList = Arrays.asList(super.getCurrentState("activeSensorList").split(","));
        this.inActiveSensorList = Arrays.asList(super.getCurrentState("inActiveSensorList").split(","));
        this.actorList = Arrays.asList(super.getCurrentState("actorList").split(","));
        this.activeActorList = Arrays.asList(super.getCurrentState("activeActorList").split(","));
        this.inActiveActorList = Arrays.asList(super.getCurrentState("inActiveActorList").split(","));
    }

    public void turnOn() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "turnOn", null));

        this.state = "on";
        super.addCurrentState("state=" + state);
    }

    public void turnOff() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "turnOff", null));

        this.state = "off";
        super.addCurrentState("state=" + state);
    }

    public void useSensor(String sensor, boolean active) {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "useSensor", Arrays.asList(sensor, Boolean.toString(active))));

        if (active) {
            inActiveSensorList.remove(sensor);
            activeSensorList.add(sensor);
        } else {
            activeSensorList.remove(sensor);
            inActiveSensorList.add(sensor);
        }
        String bufferInActive = "";
        for (int i = 0; i < inActiveSensorList.size(); i++) {
            if (i + 1 != inActiveSensorList.size()) {
                bufferInActive += inActiveSensorList.get(i) + ",";
            } else {
                bufferInActive += inActiveSensorList.get(i);
            }
        }
        String bufferActive = "";
        for (int i = 0; i < activeSensorList.size(); i++) {
            if (i + 1 != activeSensorList.size()) {
                bufferActive += activeSensorList.get(i) + ",";
            } else {
                bufferActive += activeSensorList.get(i);
            }
        }

        super.addCurrentState("inActiveSensorList=" + bufferInActive);
        super.addCurrentState("activeSensorList=" + bufferActive);
    }

    public List<String> getSensorList() {
        return sensorList;
    }

    public List<String> getSensorList(boolean active) {
        if (active) {
            return activeSensorList;
        } else {
            return inActiveSensorList;
        }
    }

    public void useActor(String actor, boolean active) {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "useActor", Arrays.asList(actor, Boolean.toString(active))));

        if (active) {
            inActiveActorList.remove(actor);
            activeActorList.add(actor);
        } else {
            activeActorList.remove(actor);
            inActiveActorList.add(actor);
        }

        String bufferInActive = "";
        for (int i = 0; i < inActiveActorList.size(); i++) {
            if (i + 1 != inActiveActorList.size()) {
                bufferInActive += inActiveActorList.get(i) + ",";
            } else {
                bufferInActive += inActiveActorList.get(i);
            }
        }
        String bufferActive = "";
        for (int i = 0; i < activeActorList.size(); i++) {
            if (i + 1 != activeActorList.size()) {
                bufferActive += activeActorList.get(i) + ",";
            } else {
                bufferActive += activeActorList.get(i);
            }
        }

        super.addCurrentState("inActiveActorList=" + bufferInActive);
        super.addCurrentState("activeActorList=" + bufferActive);
    }

    public List<String> getActorList() {
        return actorList;
    }

    public List<String> getActorList(boolean active) {
        if (active) {
            return activeActorList;
        } else {
            return inActiveActorList;
        }
    }

    public void calibrate() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "calibrate", null));
    }

    public void subscribe() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "subscribe", null));

        subscription = "subscribed";
        super.addCurrentState("subscription=" + subscription);
    }

    public void unsubscribe() {
        new MCPWriter(super.getConnection().substring(super.getConnection().indexOf("(") + 1, super.getConnection().indexOf(")"))).send(
                new CallMessage(super.getDeviceId(), "unsubscribe", null));

        subscription = "unsubscribed";
        super.addCurrentState("subscription=" + subscription);
    }

    public String getSubscribtion() {
        return subscription;
    }

    public String getState() {
        return state;
    }
}