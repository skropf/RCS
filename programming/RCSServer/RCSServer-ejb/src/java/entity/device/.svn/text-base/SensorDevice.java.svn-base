/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entity.device;

import entity.Device;
import entity.DeviceType;
import mcp.CallMessage;
import mcp.administration.MCPSocketWriter;

/**
 *
 * @author skropf
 */
public class SensorDevice extends Device {

    private double temperature;
    private int brightness;

    public SensorDevice() {
        this.temperature = -1;
        this.brightness = -1;
    }

    public SensorDevice(int deviceId, String name, String ip, DeviceType deviceType, String currentState) {
        super(deviceId, name, ip, deviceType, currentState);
        this.updateCurrentState();
    }

    private void updateCurrentState() {
        try {
            if (super.getCurrentState("temperature") != null) {
                this.temperature = Double.parseDouble(super.getCurrentState("temperature"));
            } else {
                this.temperature = -1;
            }
            if (super.getCurrentState("brightness") != null) {
                this.brightness = Integer.parseInt(super.getCurrentState("brightness"));
            } else {
                this.brightness = -1;
            }
        } catch (Exception ex) {
            System.err.println(super.getDeviceId() + " - " + super.getName() + ": " + ex.toString());
        }
    }

    public int getBrightness() {
        return brightness;
    }

    public double getTemperature() {
        return temperature;
    }

    public void brightnessRCS() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "getBrightness", null));
    }

    public void temperatureRCS() {
        MCPSocketWriter writer = new MCPSocketWriter(super.getRealIp());
        writer.send(new CallMessage(super.getDeviceId(), "getTemperature", null));
    }
}