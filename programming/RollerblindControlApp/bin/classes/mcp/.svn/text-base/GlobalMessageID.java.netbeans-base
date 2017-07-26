package mcp;

/**
 *
 * @author skropf
 */
public class GlobalMessageID {
    private long id = 0;
    private final static GlobalMessageID INSTANCE = new GlobalMessageID();
    
    private GlobalMessageID() {
    }
    
    public static GlobalMessageID getInstance() {
        return INSTANCE;
    }
    
    public long getId() {
        return ++id;
    }

    public void setId(long id) {
        this.id = id;
    }
}