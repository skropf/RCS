package mcp.administration;

import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import mcp.Message;


public class MCPSocketWriter implements IMCPWriter
{

    private PrintWriter writer;

    public MCPSocketWriter(String ip) {
        try {
            Socket socket = new Socket(InetAddress.getByName(ip), 13316);
            this.writer = new PrintWriter(socket.getOutputStream(), true);
        } catch (Exception ex) {
            System.err.println("MCPSocketWriter: " + ex.toString());
        }
    }

    public void send(Message message) {
    	try
    	{
        writer.println(message.toString());
        writer.close();
    	}
    	catch(Exception ex)
    	{
    		System.out.println(ex.getStackTrace());
    	}
    }
}