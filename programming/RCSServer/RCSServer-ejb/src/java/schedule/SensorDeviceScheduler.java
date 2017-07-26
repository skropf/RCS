/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package schedule;

import entity.Device;
import entity.DeviceType;
import entity.device.SensorDevice;
import java.util.List;
import javax.ejb.EJB;
import javax.ejb.LocalBean;
import javax.ejb.Schedule;
import javax.ejb.Singleton;
import session.DeviceFacade;
import session.DeviceTypeFacade;

/**
 *
 * @author skropf
 */
@Singleton
@LocalBean
public class SensorDeviceScheduler {

    @EJB
    private DeviceFacade deviceFacade;
    @EJB
    private DeviceTypeFacade deviceTypeFacade;

    @Schedule(hour = "*", minute = "*", second = "*/10", persistent = false)
    private void sensorDeviceScheduler() {
        DeviceType dt = deviceTypeFacade.findbyType("SensorDevice");
        List<Device> deviceList = deviceFacade.findbyType(dt);
        
        SensorDevice sensorDevice;
        for (Device device : deviceList) {
            sensorDevice = new SensorDevice(device.getDeviceId(), device.getName(), device.getIp(), device.getType(), device.getCurrentState());
            sensorDevice.brightnessRCS();
            sensorDevice.temperatureRCS();
        }
    }
}
