package mcp.administration;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;


public class MCPSocketListener extends Thread {

    private static final MCPSocketListener INSTANCE = new MCPSocketListener();
    private ServerSocket serverSocket;
    private MCPSocketReader mcpSocketReader;

    public static MCPSocketListener getInstance() {
        return INSTANCE;
    }

    private MCPSocketListener() {
        try {  
            serverSocket = new ServerSocket(13316);
            serverSocket.setReuseAddress(true);
        } catch (Exception ex) {
            System.err.println(ex.toString());
        }
    }

    @Override
    public void run() {
        try {
            System.err.println("listening for incoming socket on port 13316");
            while (true) {
                Socket socket = serverSocket.accept();

                BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

                
                mcpSocketReader = new MCPSocketReader(socket.getInetAddress().getHostName() + " (" + socket.getInetAddress().getHostAddress() + ")", reader);
                mcpSocketReader.start();
            }
        } catch (Exception ex) {
            System.err.println("MCPServerListener (run): " + ex.toString());
        }
    }
}