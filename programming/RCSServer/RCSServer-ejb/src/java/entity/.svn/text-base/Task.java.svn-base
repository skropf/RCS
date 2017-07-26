package entity;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;
import javax.persistence.*;
import mcp.CallMessage;

/**
 *
 * @author skropf
 */
@Entity
@NamedQueries({
    @NamedQuery(name = "Task.findbyName", query = "SELECT t FROM Task t WHERE t.name = :name")
})
public class Task implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String name;
    private boolean[] days;
    private int hourTime;
    private int minuteTime;
    @ManyToMany(mappedBy = "taskList")
    private List<Profile> profileList;
    private String destinationIp;
    private CallMessage todo;

    public Task() {
        this.name = "";
        this.days = new boolean[7];
        this.profileList = new LinkedList<Profile>();
        this.destinationIp = "";
    }

    public Task(String name, Integer hourTime, int minuteTime, boolean[] days, String destinationIp, CallMessage todo) {
        this.name = name;
        this.hourTime = hourTime;
        this.minuteTime = minuteTime;
        this.days = days;
        this.destinationIp = destinationIp;
        this.todo = todo;
        profileList = new LinkedList<Profile>();
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public boolean getMonday() {
        return days[1];
    }
    
    public void setMonday(boolean monday) {
        days[1] = monday;
    }
    
    public boolean getTuesday() {
        return days[2];
    }
    
    public void setTuesday(boolean tuesday) {
        days[2] = tuesday;
    }
    
    public boolean getWednesday() {
        return days[3];
    }
    
    public void setWednesday(boolean wednesday) {
        days[3] = wednesday;
    }
    
    public boolean getThursday() {
        return days[4];
    }
    
    public void setThursday(boolean thursday) {
        days[4] = thursday;
    }
    
    public boolean getFriday() {
        return days[5];
    }
    
    public void setFriday(boolean friday) {
        days[5] = friday;
    }
    
    public boolean getSaturday() {
        return days[6];
    }
    
    public void setSaturday(boolean saturday) {
        days[6] = saturday;
    }
    
    public boolean getSunday() {
        return days[0];
    }
    
    public void setSunday(boolean sunday) {
        days[0] = sunday;
    }
    
    public boolean[] getDays() {
        return days;
    }

    public int getHourTime() {
        return hourTime;
    }

    public void setHourTime(int hourTime) {
        this.hourTime = hourTime;
    }

    public int getMinuteTime() {
        return minuteTime;
    }

    public void setMinuteTime(int minuteTime) {
        this.minuteTime = minuteTime;
    }
    
    public void addProfile(Profile profile) {
        this.profileList.add(profile);
    }
    
    public void removeProfile(Profile profile) {
        if (profileList.contains(profile)) profileList.remove(profile);
    }

    public List<Profile> getProfileList() {
        return profileList;
    }

    public void setProfileList(List<Profile> profileList) {
        this.profileList = profileList;
    }

    public String getDestinationIp() {
        return destinationIp;
    }

    public void setDestinationIp(String destinationIp) {
        this.destinationIp = destinationIp;
    }

    public CallMessage getTodo() {
        return todo;
    }

    public void setTodo(CallMessage todo) {
        this.todo = todo;
    }

    @Override
    public String toString() {
        return this.name + " - " + String.format("%02d:%02d", this.hourTime, this.minuteTime);
    }
}