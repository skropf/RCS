/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;
import javax.persistence.*;

/**
 *
 * @author skropf
 */
@Entity
@NamedQueries({
    @NamedQuery(name="Profile.findActiveProfiles", query="SELECT p FROM Profile p WHERE p.active = 1")
})
public class Profile implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    
    private String name;
    
    private boolean active;
    
    @ManyToMany
    private List<Task> taskList;
    
    public Profile() {
        this.name = "";
        this.active = false;
        this.taskList = new LinkedList<Task>();
    }
    
    public Profile(String name, boolean active) {
        this.name = name;
        this.active = active;
        this.taskList = new LinkedList<Task>();
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

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }

    public List<Task> getTaskList() {
        return taskList;
    }

    public void setTaskList(List<Task> taskList) {
        this.taskList = taskList;
    }
    
    public void addTask(Task task) {
        this.taskList.add(task);
    }
}