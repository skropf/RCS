package entity;

import java.io.Serializable;
import java.util.Dictionary;
import java.util.Hashtable;
import java.util.LinkedList;
import java.util.List;


public class Device implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private int deviceId;
    
    private String name;
    private String ip;
    private String type;
    private String currentState;

    public Device() { }

    public Device(int deviceId, String name, String ip, String type, String currentState) {
        this.deviceId = deviceId;
        this.name = name;
        this.ip = ip;
        this.type = type;
        this.currentState = currentState;
    }
    
    public int getDeviceId() {
        return deviceId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getConnection() {
        return ip;
    }

    public void setConnection(String ip) {
        this.ip = ip;
    }

    public String getType() {
        return type;
    }

    public Dictionary<String, String> getCurrentStateAsDictionary() {
        Dictionary<String, String> state = new Hashtable<String, String>();
        
        String[] states = split(currentState, '|');
        String[] elements;
        for (String str : states) {
            elements = str.split("=");
            
            state.put(elements[0], elements[1]);
        }
        return state;
    }
    
    public String getCurrentState() {
        return currentState;
    }
    
    public String getCurrentState(String state) {
        return getCurrentStateAsDictionary().get(state);
    }
    
    public void setCurrentState(String currentState) {
        this.currentState = currentState;
    }

    public void addCurrentState(String state) {
        String[] elements = split(state, '=');
        
        int index = currentState.indexOf(elements[0]);
        
        if (index != -1) {
            String buffer;
            
            index += elements[0].length() + 1;
            
            buffer = currentState.substring(0, index);
            buffer += elements[1];
            
            int indexOfSplitter = currentState.indexOf("|", index);
            
            if (indexOfSplitter != -1) buffer += currentState.substring(indexOfSplitter, currentState.length());
            
            this.currentState = buffer;
            
        } else {
            currentState += "|" + state;
        }
    }
    
    private String[] split(String str, char c) {
        String[] result;
        List<String> list = new LinkedList<String>();
       
        int lasti = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == c) {
                list.add(str.substring(lasti, i));
                lasti = i + 1;
            }
        }
        list.add(str.substring(lasti, str.length()));
        
        result = new String[list.size()];
        for (int i = 0; i < result.length; i++) {
            result[i] = list.get(i);
        }
        return result;
    }
}
