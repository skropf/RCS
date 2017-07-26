package listener;

import entity.Activity;
import entity.Device;
import entity.Log;
import entity.MCPPlace;
import java.sql.Timestamp;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.persistence.PrePersist;
import mcp.*;
import session.DeviceFacade;
import session.DeviceTypeFacade;
import session.LogFacade;
import session.MCPPlaceFacade;
import util.ActivityStateEnum;
import util.LogStatusEnum;

/**
 *
 * @author skropf
 */
public class ActivityListener {

    private DeviceFacade deviceFacade;
    private DeviceTypeFacade deviceTypeFacade;
    private LogFacade logFacade;
    private MCPPlaceFacade mcpPlaceFacade;

    @PrePersist
    private void prePersistActivity(Activity activity) {

        if (!getFacades()) {
            activity.setEndTime(new Timestamp(new Date().getTime()));
            activity.setActivityState(ActivityStateEnum.ABORTED);
            activity.setInfo("Facades not found.");
            return;
        }

        Message message = getMessage(activity.getStringMessage());

        if (message != null) {
            Device device;
            switch (message.getMessageType().ordinal()) {
                case 0: //DeviceMessage
                    DeviceMessage deviceMessage = (DeviceMessage) message;

                    device = deviceFacade.findbyDeviceId(deviceMessage.getDeviceId());

                    if (device != null) {
                        device.setCurrentState(deviceMessage.getCurrentState());
                        device.setName(deviceMessage.getName());
                        device.setIp(activity.getIp());
                        deviceFacade.edit(device);
                    } else {
                        String ip;
                        MCPPlace mcpPlace = mcpPlaceFacade.findbyIP(activity.getIp());
                        if (mcpPlace != null) ip = mcpPlace.getPlace() + " (" + activity.getIp() + ")";
                        else ip = activity.getIp() + " (" + activity.getIp() + ")";
                        
                        device = new Device(deviceMessage.getDeviceId(), deviceMessage.getName(), ip, deviceMessage.getDeviceType(), deviceMessage.getCurrentState());
                        deviceFacade.create(device);
                    }

                    activity.setEndTime(new Timestamp(new Date().getTime()));
                    activity.setActivityState(ActivityStateEnum.FINISHED);
                    activity.setInfo("Device successfully added/editted!");
                    break;
                case 1: //CallMessage
                    activity.setEndTime(new Timestamp(new Date().getTime()));
                    activity.setActivityState(ActivityStateEnum.ABORTED);
                    activity.setInfo("RCSServer shouldn't get a CallMessage.");
                    break;
                case 2: //ResultMessage
                    ResultMessage resultMessage = (ResultMessage) message;

                    device = deviceFacade.findbyDeviceId(resultMessage.getDeviceId());

                    if (device != null && resultMessage.getResult().contains("=")) {
                        device.addCurrentState(resultMessage.getResult());
                        deviceFacade.edit(device);

                        activity.setInfo(device.getName() + ": State " + resultMessage.getResult() + " editted!");
                    }

                    activity.setEndTime(new Timestamp(new Date().getTime()));
                    activity.setActivityState(ActivityStateEnum.FINISHED);
                    
                    if (activity.getInfo() == null) activity.setInfo("Invalid result!");
                    break;
                case 3: //LogMessage
                    LogMessage logMessage = (LogMessage) message;
                    Log log = new Log(activity.getBeginTime(), logMessage.getDeviceId(), logMessage.getStatus(), logMessage.getLogText());
                    logFacade.create(log);

                    activity.setEndTime(new Timestamp(new Date().getTime()));
                    activity.setActivityState(ActivityStateEnum.FINISHED);
                    activity.setInfo("Logged/persisted successfully!");
                    break;
                default:
                    activity.setEndTime(new Timestamp(new Date().getTime()));
                    activity.setActivityState(ActivityStateEnum.ABORTED);
                    activity.setInfo("Got unknown message!");
                    break;
            }
            System.err.println("+++GOT " + message.getMessageType().name() + ": " + activity.getStringMessage());
        } else {
            activity.setEndTime(new Timestamp(new Date().getTime()));
            activity.setActivityState(ActivityStateEnum.ABORTED);
            activity.setInfo("Invalid message!");
        }
    }

    private boolean getFacades() {
        try {
            InitialContext ic = new InitialContext();
            deviceFacade = (DeviceFacade) ic.lookup("java:global/RCSServer/RCSServer-ejb/DeviceFacade");
            deviceTypeFacade = (DeviceTypeFacade) ic.lookup("java:global/RCSServer/RCSServer-ejb/DeviceTypeFacade");
            logFacade = (LogFacade) ic.lookup("java:global/RCSServer/RCSServer-ejb/LogFacade");
            mcpPlaceFacade = (MCPPlaceFacade) ic.lookup("java:global/RCSServer/RCSServer-ejb/MCPPlaceFacade");
        } catch (NamingException ex) {
            System.err.println("getFacades: " + ex.toString());
        }
        if (deviceFacade == null || deviceTypeFacade == null || logFacade == null) {
            return false;
        } else {
            return true;
        }
    }

    private Message getMessage(String stringMessage) {
        try {
            String help = stringMessage.substring(1, stringMessage.length() - 1);
            String[] received = help.split(":");

            switch (Integer.parseInt(received[1])) {
                case 0:
                    return new DeviceMessage(Integer.parseInt(received[2]), deviceTypeFacade.findbyType(received[3]), received[4], received[5]);
                case 1:
                    List<String> parameter = new LinkedList<String>();
                    for (int i = 4; i < received.length; i++) {
                        parameter.add(received[i]);
                    }
                    return new CallMessage(Integer.parseInt(received[2]), received[3], parameter);
                case 2:
                    return new ResultMessage(Integer.parseInt(received[2]), received[3]);
                case 3:
                    return new LogMessage(Integer.parseInt(received[2]), LogStatusEnum.values()[Integer.parseInt(received[3])], received[4]);
            }
        } catch (Exception ex) {
            System.err.println("Cast string to message: " + ex.toString());
        }
        return null;
    }
}