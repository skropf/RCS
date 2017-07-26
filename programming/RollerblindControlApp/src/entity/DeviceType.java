/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;


public class DeviceType implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private Long id;
    
    private String deviceType;

    public DeviceType() {
    }

    public DeviceType(String deviceType) {
        this.deviceType = deviceType;
    }
    
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }
    
    public String getDeviceType() {
        return deviceType;
    }

    public void setDeviceType(String deviceType) {
        this.deviceType = deviceType;
    }
}
