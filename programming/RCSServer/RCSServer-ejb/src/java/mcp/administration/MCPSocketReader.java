package mcp.administration;

import entity.Activity;
import java.io.BufferedReader;
import java.sql.Timestamp;
import java.util.Date;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import mcp.GlobalMessageID;
import session.ActivityFacade;
import util.ActivityStateEnum;

/**
 *
 * @author skropf
 */
public class MCPSocketReader extends Thread {

    private ActivityFacade activityFacade;
    private BufferedReader reader;
    private String line;
    private String clientIp;
    
    private Activity activity;

    public MCPSocketReader(String clientIp, BufferedReader reader) {
        this.clientIp = clientIp;
        this.reader = reader;

        getFacade();
    }

    @Override
    public void run() {
        try {
            line = reader.readLine();
            
            while (line != null && reader != null) {
                GlobalMessageID.getInstance().setId(Long.parseLong((line.substring(1)).split(":")[0]));
                
                activity = new Activity(clientIp, new Timestamp(new Date().getTime()), ActivityStateEnum.IN_PROGRESS, line);
                activityFacade.create(activity);
                
                line = reader.readLine();
            }
            if (reader != null) reader.close();
        } catch (Exception ex) {
            System.err.println(ex.toString());
        }
    }
    
    private void getFacade() {
        try {
            InitialContext ic = new InitialContext();
            activityFacade = (ActivityFacade) ic.lookup("java:global/RCSServer/RCSServer-ejb/ActivityFacade");
        } catch (NamingException e) {
            System.err.println(e.toString());
        }
        if (activityFacade == null) System.err.println("+++activityFacade == null");
        
    }
}