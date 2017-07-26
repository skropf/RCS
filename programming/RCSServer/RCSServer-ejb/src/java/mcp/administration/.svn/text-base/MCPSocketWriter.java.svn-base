package mcp.administration;

import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import mcp.Message;

/**
 *
 * @author skropf
 */
public class MCPSocketWriter extends Thread {

    private String ip;
    private Message message;

    public MCPSocketWriter(String ip) {
        this.ip = ip;
    }

    public void send(Message message) {
        this.message = message;
        this.start();
    }
    
    @Override
    public void run() {
        try {
            Socket socket = new Socket(InetAddress.getByName(ip), 13316);
            PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
            Thread.sleep(20);
            writer.println(message.toString());
            writer.close();
            socket.close();
            System.err.println("MCPSocketWriter.send [sent]: '" + message.toString() + "'");
        } catch (Exception ex) {
            System.out.println("MCPSocketWriter.send: " + ex.toString());
        }
    }
}