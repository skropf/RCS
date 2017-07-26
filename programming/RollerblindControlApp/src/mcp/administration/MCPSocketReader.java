package mcp.administration;

import java.io.BufferedReader;

import entity.MessageInterpreter;
import mcp.GlobalMessageID;


public class MCPSocketReader extends Thread {

    private BufferedReader reader;
    private String line;
    private String clientIp;
    MessageInterpreter mInterpreter;

    public MCPSocketReader(String clientIp, BufferedReader reader) {
        this.clientIp = clientIp;
        this.reader = reader;
        mInterpreter = MessageInterpreter.getInstance();
    }

    @Override
    public void run() {
        try {
            line = reader.readLine();
            
            while (line != null && reader != null) {
                GlobalMessageID.getInstance().setId(Long.parseLong((line.substring(1)).split(":")[0]));
                
                
                mInterpreter.interprete(line, this.clientIp);
                
                line = reader.readLine();
            }
            if (reader != null) reader.close();
        } catch (Exception ex) {
            System.err.println(ex.toString());
        }
    }
}