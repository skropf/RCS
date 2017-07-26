package mcp;

import java.io.Serializable;
import util.MessageTypeEnum;

/**
 *
 * @author skropf
 */
public abstract class Message implements Serializable {
    
    private long id;
    private MessageTypeEnum messageType;
    
    public Message(long id, MessageTypeEnum messageType) {
        this.id = id;
        this.messageType = messageType;
    }
    
    public long getId() {
        return id;
    }

    public MessageTypeEnum getMessageType() {
        return messageType;
    }
    
    @Override
    public String toString() {
        return "#"+ id + ":" + messageType.ordinal();
    }
    
}