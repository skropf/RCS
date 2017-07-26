/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import java.sql.Timestamp;
import javax.persistence.*;
import util.LogStatusEnum;

/**
 *
 * @author skropf
 */
@Entity
@NamedQueries({
    @NamedQuery(name="Log.findAll", query="SELECT l FROM Log l ORDER BY l.id DESC")
})
public class Log implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    
    private Timestamp time;
    private int deviceId;
    private LogStatusEnum status;
    private String logText;

    public Log() {
    }

    public Log(Timestamp time, int deviceId, LogStatusEnum status, String logText) {
        this.time = time;
        this.deviceId = deviceId;
        this.status = status;
        this.logText = logText;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Timestamp getTime() {
        return time;
    }

    public void setTime(Timestamp time) {
        this.time = time;
    }

    public int getDeviceId() {
        return deviceId;
    }

    public void setDeviceId(int deviceId) {
        this.deviceId = deviceId;
    }

    public String getLogText() {
        return logText;
    }

    public void setLogText(String logText) {
        this.logText = logText;
    }

    public LogStatusEnum getStatus() {
        return status;
    }

    public void setStatus(LogStatusEnum status) {
        this.status = status;
    }
    
    @Override
    public String toString() {
        return logText;
    }
}