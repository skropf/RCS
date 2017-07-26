/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import java.sql.Timestamp;
import javax.persistence.*;
import listener.ActivityListener;
import util.ActivityStateEnum;

/**
 *
 * @author skropf
 */
@Entity
@EntityListeners(ActivityListener.class)
public class Activity implements Serializable {

    private static final long serialVersionUID = 1L;
    
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    
    private String ip;
    private Timestamp beginTime, endTime;
    private ActivityStateEnum activityState;
    private String stringMessage;
    private String info;

    public Activity() {
    }

    public Activity(String ip, Timestamp beginTime, ActivityStateEnum actionState, String stringMessage) {
        this.ip = ip;
        this.beginTime = beginTime;
        this.activityState = actionState;
        this.stringMessage = stringMessage;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public ActivityStateEnum getActivityState() {
        return activityState;
    }

    public void setActivityState(ActivityStateEnum activityState) {
        this.activityState = activityState;
    }

    public Timestamp getBeginTime() {
        return beginTime;
    }

    public void setBeginTime(Timestamp beginTime) {
        this.beginTime = beginTime;
    }

    public Timestamp getEndTime() {
        return endTime;
    }

    public void setEndTime(Timestamp endTime) {
        this.endTime = endTime;
    }

    public String getStringMessage() {
        return stringMessage;
    }

    public void setStringMessage(String stringMessage) {
        this.stringMessage = stringMessage;
    }

    public String getInfo() {
        return info;
    }

    public void setInfo(String info) {
        this.info = info;
    }
}