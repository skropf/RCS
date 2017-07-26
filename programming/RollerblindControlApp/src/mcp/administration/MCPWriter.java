package mcp.administration;

import mcp.Message;


public class MCPWriter {

    IMCPWriter mcpWriter;

    public MCPWriter()
    {
    }
    public MCPWriter(String con) {
        if(con.equals("ADK"))
        {
        	mcpWriter = MCPADKWriter.getInstance();
        }
        else
        {
        	mcpWriter = new MCPSocketWriter(con);
        }
    }

    public void send(Message message) {
        mcpWriter.send(message);
    }
}