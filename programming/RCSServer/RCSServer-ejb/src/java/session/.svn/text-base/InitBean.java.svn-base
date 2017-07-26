package session;

import entity.Device;
import entity.MCPPlace;
import entity.Task;
import java.util.Arrays;
import java.util.List;
import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.ejb.Startup;
import mcp.CallMessage;
import mcp.administration.MCPSocketListener;
import mcp.administration.MCPSocketWriter;

/**
 *
 * @author skropf
 */
@Singleton
@Startup
public class InitBean {

    @EJB
    private TaskFacade tf;
    @EJB
    private DeviceFacade df;
    @EJB
    private DeviceTypeFacade dtf;
    @EJB
    private MCPPlaceFacade mcppf;

    @PostConstruct
    private void init() {
        //start MCP Server
        MCPSocketListener.getInstance().start();

        //send messages to places for activating/deactivating logging
        List<MCPPlace> mcpPlaceList = mcppf.findAll();
        MCPSocketWriter writer;
        for (MCPPlace mcpPlace : mcpPlaceList) {
            if (mcpPlace.isLoggingActivated()) {
                writer = new MCPSocketWriter(mcpPlace.getIp());
                writer.send(new CallMessage(0, "logging", Arrays.asList("1")));
            } else {
                writer = new MCPSocketWriter(mcpPlace.getIp());
                writer.send(new CallMessage(0, "logging", Arrays.asList("0")));
            }
        }

        //retrieve devices from all MCPPlaces
        for (MCPPlace mcpp : mcpPlaceList) {
            writer = new MCPSocketWriter(mcpp.getIp());
            writer.send(new CallMessage(0, "getDevices", null));
        }

        try {
            Thread.sleep(1000);
        } catch (Exception ex) {
            System.err.println("InitBean: " + ex.toString());
        }

        //look through devices if ip can be replaced with place
        List<Device> deviceList = df.findAll();
        MCPPlace mcpPlace;
        String rawIp;
        for (Device device : deviceList) {
            rawIp = device.getIp().split(" ")[0];
            mcpPlace = mcppf.findbyIP(rawIp);

            if (mcpPlace != null) {
                device.setIp(mcpPlace.getPlace() + " (" + rawIp + ")");
                df.edit(device);
            }
        }

        /*
         *
         * DeviceType dt; HashMap<String, String> map = new HashMap<String,
         * String>();
         *
         * map.put("turnOn", "Turns the alarm system on, activates it and you'll
         * get subscribed."); map.put("turnOff", "Turns the alarm system off.");
         * map.put("subscribe", "Means that you get an alarm if it's
         * triggered."); map.put("unsubscribe", "You won't get an alarm if the
         * alarm system is triggered."); map.put("alarmOff", "Turns the alarm
         * off.");
         *
         * dt = new DeviceType("AlarmSystem", map); dtf.create(dt);
         *
         *
         * map = new HashMap<String, String>(); map.put("turnOn", "Turns the fan
         * on."); map.put("turnOff", "Turns the fan off.");
         * map.put("setTemperatureCondition", "Turns the fan on if the specified
         * temperature is exceeded.");
         *
         * dt = new DeviceType("Fan", map); dtf.create(dt);
         *
         *
         * map = new HashMap<String, String>(); map.put("turnOn", "Turns the
         * heater on."); map.put("turnOff", "Turns the heater off.");
         * map.put("setTemperatureCondition", "Turns the heater on if the
         * temperature is below the specified temperature.");
         *
         * dt = new DeviceType("Heater", map); dtf.create(dt);
         *
         *
         * map = new HashMap<String, String>(); map.put("turnOn", "Turns the
         * light on."); map.put("turnOff", "Turns the light off.");
         * map.put("setBrightnessCondition", "Turns the light on if the
         * brightness is below the specified brightness.");
         *
         * dt = new DeviceType("Light", map); dtf.create(dt);
         *
         *
         * map = new HashMap<String, String>(); map.put("turnOn", "Turns the
         * power outlet on."); map.put("turnOff", "Turns the power outlet
         * off.");
         *
         * dt = new DeviceType("PowerOutlet", map); dtf.create(dt);
         *
         *
         * map = new HashMap<String, String>(); map.put("moveToPosition", "Moves
         * the roller blind to the specified position. (position lies between 0
         * and 1000 [0=top - 1000=bottom]).");
         *
         * dt = new DeviceType("RollerBlind", map); dtf.create(dt);
         *
         *
         * dt = new DeviceType("SensorDevice", null); dtf.create(dt);
         */

        /*
        Task task;
        CallMessage callMessage;
        boolean[] days;

        days = new boolean[]{false, true, true, true, true, true, false};

        

        callMessage = new CallMessage(2, "moveToPosition", Arrays.asList("0"));
        task = new Task("Move rollerblind up", 8, 0, days, "192.168.1.2", callMessage);
        tf.create(task);
        
        callMessage = new CallMessage(3, "turnOff", null);
        task = new Task("Turn off lights", 8, 0, days, "192.168.1.2", callMessage);
        tf.create(task);

        callMessage = new CallMessage(4, "turnOff", null);
        task = new Task("Turn off power.", 8, 0, days, "192.168.1.2", callMessage);
        tf.create(task);
        
        callMessage = new CallMessage(6, "removeCondition", null);
        task = new Task("Remove temperature condition fan", 8, 0, days, "192.168.1.2", callMessage);
        tf.create(task);

        callMessage = new CallMessage(6, "setTemperatureCondition", Arrays.asList("27"));
        task = new Task("Set temperature condition fan", 17, 0, days, "192.168.1.2", callMessage);
        tf.create(task);
        
        callMessage = new CallMessage(2, "moveToPosition", Arrays.asList("1000"));
        task = new Task("Move rollerblind down", 20, 0, days, "192.168.1.2", callMessage);
        tf.create(task);
        */
    }
}