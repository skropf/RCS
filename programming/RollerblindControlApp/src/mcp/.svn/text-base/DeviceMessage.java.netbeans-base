package mcp;

import entity.DeviceType;
import java.io.Serializable;
import util.MessageTypeEnum;

/**
 *
 * @author skropf
 */
public class DeviceMessage extends Message implements Serializable {
    
    private int deviceId;
    private DeviceType deviceType;
    private String name;
    private String currentState;
    
    public DeviceMessage(int deviceId, DeviceType type, String name, String currentState) {
        super(GlobalMessageID.getInstance().getId(), MessageTypeEnum.DEVICEMESSAGE);
        this.deviceId = deviceId;
        this.deviceType = type;
        this.name = name;
        this.currentState = currentState;
    }

    public int getDeviceId() {
        return deviceId;
    }

    public void setDeviceId(int deviceId) {
        this.deviceId = deviceId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public DeviceType getDeviceType() {
        return deviceType;
    }

    public void setDeviceType(DeviceType deviceType) {
        this.deviceType = deviceType;
    }

    public String getCurrentState() {
        return currentState;
    }

    public void setCurrentState(String currentState) {
        this.currentState = currentState;
    }
    
    //#MsgID:MsgType=0:DevID:type:name:currentState;
    @Override
    public String toString() {
        return super.toString() +
                ":" + deviceId +
                ":" + deviceType.getDeviceType() +
                ":" + name + 
                ":" + currentState + ";";
    }
}