package mcp;

import java.io.Serializable;
import util.MessageTypeEnum;

/**
 *
 * @author skropf
 */
public class ResultMessage extends Message implements Serializable {
    
    private int deviceId;
    private String result;

    public ResultMessage(int deviceId, String result) {
        super(GlobalMessageID.getInstance().getId(), MessageTypeEnum.RESULTMESSAGE);
        this.deviceId = deviceId;
        this.result = result;
    }

    public int getDeviceId() {
        return deviceId;
    }

    public String getResult() {
        return result;
    }
    
    //#MsgID:MsgType=2:deviceID:result;
    @Override
    public String toString() {
        return super.toString() +
                ":" + this.deviceId +
                ":" + this.result + ";";
    }
}