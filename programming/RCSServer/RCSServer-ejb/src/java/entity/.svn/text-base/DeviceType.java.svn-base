/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import javax.persistence.*;

/**
 *
 * @author skropf
 */
@Entity
@NamedQueries({
    @NamedQuery(name="DeviceType.findbyType", query="SELECT dt FROM DeviceType dt WHERE dt.deviceType = :deviceType")
})
public class DeviceType implements Serializable {
    private static final long serialVersionUID = 1L;
    
    @Id
    @GeneratedValue(strategy= GenerationType.AUTO)
    private Long id;
    
    private String deviceType;
    private HashMap<String, String> methods;

    public DeviceType() {
    }
    
    public DeviceType(String deviceType) {
        this.deviceType = deviceType;
    }

    public DeviceType(String deviceType, HashMap<String, String> methods) {
        this.deviceType = deviceType;
        this.methods = methods;
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

    public HashMap<String, String> getMethods() {
        return methods;
    }
}