package entity;

import java.lang.reflect.Constructor;
import java.util.LinkedList;
import java.util.List;

import android.util.Log;

import mcp.CallMessage;
import mcp.DeviceMessage;
import mcp.Message;
import mcp.ResultMessage;

public class MessageInterpreter {
	static MessageInterpreter instance = new MessageInterpreter();
	public static MessageInterpreter getInstance()
	{
		return instance;
	}
	private MessageInterpreter(){}
	private ResultMessageListener resultListener;
	public void addResultMessageListener(ResultMessageListener r)
	{
		this.resultListener = r;
	}
	public void interprete(String msg,String connection)
	{
		Message message = getMessage(msg);

        if (message != null) {
            Device device;
            switch (message.getMessageType().ordinal()) {
                case 0: //DeviceMessage
                    DeviceMessage deviceMessage = (DeviceMessage) message;

                    device = DeviceManager.getInstance().get(deviceMessage.getDeviceId());

                    if (device != null) {
                        device.setCurrentState(deviceMessage.getCurrentState());
                        device.setName(deviceMessage.getName());
                    } else {
                    	try {
							Class<?> cls = Class.forName("entity.device." + deviceMessage.getDeviceType());
							Constructor<?> c = cls.getConstructor(new Class[] { int.class, String.class, String.class, String.class, String.class });
							
							deviceMessage.setCurrentState(deviceMessage.getCurrentState().substring(0, deviceMessage.getCurrentState().length() - 1));
							Log.e("Construct",deviceMessage.getDeviceId() + "  " + deviceMessage.getName() + "  " + deviceMessage.getDeviceType() + "  " + deviceMessage.getCurrentState());
							device = (Device) c.newInstance(deviceMessage.getDeviceId(), deviceMessage.getName(), connection, deviceMessage.getDeviceType(), deviceMessage.getCurrentState());
							//device = new Device(deviceMessage.getDeviceId(), deviceMessage.getName(), connection, deviceMessage.getDeviceType(), deviceMessage.getCurrentState());
	                        DeviceManager.getInstance().add(device);
						} catch (ClassNotFoundException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
                    	catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
                        
                    }
                    break;
                case 2: //ResultMessage
                    ResultMessage resultMessage = (ResultMessage) message;

                    device = DeviceManager.getInstance().get(resultMessage.getDeviceId());

                    if (device != null && resultMessage.getResult().contains("=")) {
                        device.addCurrentState(resultMessage.getResult());
                        }
                    if(this.resultListener!=null)resultListener.onResultMessageRecieved(resultMessage);
                    break;
                /*case 3: //LogMessage
                    LogMessage logMessage = (LogMessage) message;
                    Log log = new Log(logMessage.getStatus(), logMessage.getLogText());
                    logFacade.create(log);

                    activity.setEndTime(new Timestamp(new Date().getTime()));
                    activity.setActivityState(ActivityStateEnum.FINISHED);
                    activity.setInfo("Logged/persisted successfully!");
                    break;
                default:
                    activity.setEndTime(new Timestamp(new Date().getTime()));
                    activity.setActivityState(ActivityStateEnum.ABORTED);
                    activity.setInfo("Got unknown message!");
                    break;*/
            }
        }
	}
        
        private Message getMessage(String stringMessage) {
            try {
                String help = stringMessage.substring(1, stringMessage.length() - 1);
                String[] received = help.split(":");

                switch (Integer.parseInt(received[1])) {
                    case 0:
                        return new DeviceMessage(Integer.parseInt(received[2]), received[3], received[4], received[5]);
                    case 1:
                        List<String> parameter = new LinkedList<String>();
                        for (int i = 4; i < received.length; i++) {
                            parameter.add(received[i]);
                        }
                        return new CallMessage(Integer.parseInt(received[2]), received[3], parameter);
                    case 2:
                        return new ResultMessage(Integer.parseInt(received[2]), received[3]);
                    //case 3:
                    //    return new LogMessage(LogStatusEnum.values()[Integer.parseInt(received[2])], received[3]);
                }
            } catch (Exception ex) {
            }
            return null;
        }

}
