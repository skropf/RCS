package mcp;

import java.io.Serializable;
import util.LogStatusEnum;
import util.MessageTypeEnum;

/**
 *
 * @author skropf
 */
public class LogMessage extends Message implements Serializable {
    
    private LogStatusEnum status;
    private String logText;

    public LogMessage(LogStatusEnum status, String logText) {
        super(GlobalMessageID.getInstance().getId(), MessageTypeEnum.LOGMESSAGE);
        this.status = status;
        this.logText = logText;
    }

    public String getLogText() {
        return logText;
    }

    public LogStatusEnum getStatus() {
        return status;
    }
    
    //#MsgID/LogID:MsgType=3:status:logText;
    @Override
    public String toString() {
        return super.toString() +
                ":" + status +
                ":" + logText + ";";
    }
}