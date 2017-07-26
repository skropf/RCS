package mcp;

import java.io.Serializable;
import java.util.List;
import util.MessageTypeEnum;

/**
 *
 * @author skropf
 */
public class CallMessage extends Message implements Serializable {
    
    private String methodName;
    private int deviceId = 0;
    private List<String> parameter;
    
    public CallMessage(int deviceID, String methodName, List<String> parameter) {
        super(GlobalMessageID.getInstance().getId(), MessageTypeEnum.CALLMESSAGE);
        this.methodName = methodName;
        this.deviceId = deviceID;
        this.parameter = parameter;
    }

    public int getDeviceId() {
        return deviceId;
    }

    public String getMethodName() {
        return methodName;
    }

    public List<String> getParameter() {
        return parameter;
    }
    
    //#MsgID:MsgType=1:devID:methodName;
    //#MsgID:MsgType=1:devID:methodName:parameter;
    //#MsgID:MsgType=1:devID:methodName:parameter;
    @Override
    public String toString() {
        String sendString = super.toString();
        
        sendString += ":" + deviceId + ":" + methodName;
        if (parameter != null) {
            for (String str : parameter) {
            sendString += ":" + str;
            }
        }
        return sendString + ";";
    }
}