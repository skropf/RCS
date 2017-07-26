package controller;

import entity.Device;
import entity.DeviceType;
import entity.device.*;
import java.io.Serializable;
import java.lang.reflect.Constructor;
import java.util.LinkedList;
import java.util.List;
import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.model.SelectItem;
import session.DeviceFacade;
import session.DeviceTypeFacade;

/**
 *
 * @author skropf
 */
@ManagedBean
@SessionScoped
public class DeviceController implements Serializable {

    @EJB
    private DeviceFacade deviceFacade;
    @EJB
    private DeviceTypeFacade deviceTypeFacade;
    private List<Device> deviceList;
    private List<SelectItem> deviceTypeList;
    private List<SelectItem> deviceIpList;
    private Device selectedDevice;
    private SensorDevice sensorDevice = new SensorDevice();

    public DeviceController() {
    }

    @PostConstruct
    public void init() {
        deviceList = deviceFacade.findAllExceptSensorDevice();

        deviceIpList = new LinkedList<SelectItem>();
        deviceTypeList = new LinkedList<SelectItem>();

        deviceIpList.add(new SelectItem("", "Select"));
        deviceTypeList.add(new SelectItem("", "Select"));

        List<String> buffer = new LinkedList<String>();
        for (Device device : deviceList) {
            if (!buffer.contains(device.getIp())) {
                buffer.add(device.getIp());
            }
        }
        for (String ip : buffer) {
            deviceIpList.add(new SelectItem(ip, ip));
        }
        buffer.clear();
        for (Device device : deviceList) {
            if (!buffer.contains(device.getType().getDeviceType())) {
                buffer.add(device.getType().getDeviceType());
            }
        }
        for (String type : buffer) {
            deviceTypeList.add(new SelectItem(type, type));
        }
        
        
        DeviceType dt = deviceTypeFacade.findbyType("SensorDevice");
        List<Device> list = deviceFacade.findbyType(dt);
        Device device;
        if (!list.isEmpty()) {
            device = list.get(0);
            sensorDevice = new SensorDevice(device.getDeviceId(), device.getName(), device.getIp(), device.getType(), device.getCurrentState());
        }
    }

    public Device getSelectedDevice() {
        return selectedDevice;
    }

    public void setSelectedDevice(Device selectedDevice) {
        try {
            if (selectedDevice != null) {
                this.selectedDevice = selectedDevice;

                System.err.println(selectedDevice.getDeviceId() + ": " + selectedDevice.getType().getDeviceType());

                Class cls = Class.forName("entity.device." + this.selectedDevice.getType().getDeviceType());
                Constructor constructor = cls.getConstructor(new Class[]{int.class, String.class, String.class, DeviceType.class, String.class});

                this.selectedDevice = (Device) constructor.newInstance(selectedDevice.getDeviceId(), selectedDevice.getName(), selectedDevice.getIp(), selectedDevice.getType(), selectedDevice.getCurrentState());

            }
        } catch (Exception ex) {
            System.err.println("DeviceController: " + ex.toString());
        }
    }

    public void persistCurrentState(Device currentDevice) {
        Device device = deviceFacade.findbyDeviceId(currentDevice.getDeviceId());
        device.setCurrentState(currentDevice.getCurrentState());
        deviceFacade.edit(device);
        deviceList = deviceFacade.findAllExceptSensorDevice();
    }

    public List<Device> getDeviceList() {
        return deviceList;
    }

    // <editor-fold defaultstate="collapsed" desc="Filterlists">
    public List<SelectItem> getDeviceIpList() {
        return deviceIpList;
    }

    public List<SelectItem> getDeviceTypeList() {
        return deviceTypeList;
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Roller blind">
    public RollerBlind getCurrentRollerBlind() {
        return (RollerBlind) this.selectedDevice;
    }

    public void currentRollerBlindMoveToPosition() {
        ((RollerBlind) this.selectedDevice).moveToPosition();
        persistCurrentState(this.selectedDevice);
    }

    public void currentRollerBlindSetCondition() {
        ((RollerBlind) this.selectedDevice).setCondition();
        persistCurrentState(this.selectedDevice);
    }

    public void currentRollerBlindRemoveCondition() {
        ((RollerBlind) this.selectedDevice).removeCondition();
        persistCurrentState(this.selectedDevice);
    }
    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Light">

    public Light getCurrentLight() {
        return (Light) this.selectedDevice;
    }

    public void currentLightTurnOn() {
        ((Light) this.selectedDevice).turnOn();
        persistCurrentState(this.selectedDevice);
    }

    public void currentLightTurnOff() {
        ((Light) this.selectedDevice).turnOff();
        persistCurrentState(this.selectedDevice);
    }

    public void currentLightSetCondition() {
        ((Light) this.selectedDevice).setCondition();
        persistCurrentState(this.selectedDevice);
    }

    public void currentLightRemoveCondition() {
        ((Light) this.selectedDevice).removeCondition();
        persistCurrentState(this.selectedDevice);
    }
    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="PowerOutlet">

    public PowerOutlet getCurrentPowerOutlet() {
        return (PowerOutlet) this.selectedDevice;
    }

    public void currentPowerOutletTurnOn() {
        ((PowerOutlet) this.selectedDevice).turnOn();
        persistCurrentState(this.selectedDevice);
    }

    public void currentPowerOutletTurnOff() {
        ((PowerOutlet) this.selectedDevice).turnOff();
        persistCurrentState(this.selectedDevice);
    }
    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Fan">

    public Fan getCurrentFan() {
        return (Fan) this.selectedDevice;
    }

    public void currentFanTurnOn() {
        ((Fan) this.selectedDevice).turnOn();
        persistCurrentState(this.selectedDevice);
    }

    public void currentFanTurnOff() {
        ((Fan) this.selectedDevice).turnOff();
        persistCurrentState(this.selectedDevice);
    }

    public void currentFanSetCondition() {
        ((Fan) this.selectedDevice).setCondition();
        persistCurrentState(this.selectedDevice);
    }

    public void currentFanRemoveCondition() {
        ((Fan) this.selectedDevice).removeCondition();
        persistCurrentState(this.selectedDevice);
    }
    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Heater">

    public Heater getCurrentHeater() {
        return (Heater) this.selectedDevice;
    }

    public void currentHeaterTurnOn() {
        ((Heater) this.selectedDevice).turnOn();
        persistCurrentState(this.selectedDevice);
    }

    public void currentHeaterTurnOff() {
        ((Heater) this.selectedDevice).turnOff();
        persistCurrentState(this.selectedDevice);
    }

    public void currentHeaterSetCondition() {
        ((Heater) this.selectedDevice).setCondition();
        persistCurrentState(this.selectedDevice);
    }

    public void currentHeaterRemoveCondition() {
        ((Heater) this.selectedDevice).removeCondition();
        persistCurrentState(this.selectedDevice);
    }
    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="AlarmSystem">

    public AlarmSystem getCurrentAlarmSystem() {
        return (AlarmSystem) this.selectedDevice;
    }
    
    public void currentAlarmSystemTurnOn() {
        ((AlarmSystem) this.selectedDevice).turnOn();
        persistCurrentState(this.selectedDevice);
    }

    public void currentAlarmSystemTurnOff() {
        ((AlarmSystem) this.selectedDevice).turnOff();
        persistCurrentState(this.selectedDevice);
    }
    
    public void currentAlarmSystemSubscribe() {
        ((AlarmSystem) this.selectedDevice).subscribe();
        persistCurrentState(this.selectedDevice);
    }
    
    public void currentAlarmSystemUnsubscribe() {
        ((AlarmSystem) this.selectedDevice).unsubscribe();
        persistCurrentState(this.selectedDevice);
    }
    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="SensorDevice">

    public SensorDevice getSensorDevice() {
        return sensorDevice;
    }
    // </editor-fold>
}