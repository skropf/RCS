/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import entity.Device;
import entity.Task;
import java.io.Serializable;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;
import mcp.CallMessage;
import session.DeviceFacade;
import session.TaskFacade;

/**
 *
 * @author skropf
 */
@ManagedBean
@SessionScoped
public class TaskController implements Serializable {

    @EJB
    private TaskFacade taskFacade;
    @EJB
    private DeviceFacade deviceFacade;
    private List<Device> devicesForTaskList;
    private List<Task> taskList;
    private Device selectedDevice;
    private Task selectedTask = new Task();
    private HashMap<String, String> methodMap;
    private String selectedMethod;
    private String selectedMethodInfo;
    private String parameter;
    private boolean isNotCorrectMethod = true;

    public TaskController() {
    }

    @PostConstruct
    public void init() {
        taskList = taskFacade.findAll();
        methodMap = new HashMap<String, String>();
        devicesForTaskList = deviceFacade.findAllExceptSensorDevice();
    }

    public List<Task> getTaskList() {
        return taskList;
    }

    public List<Device> getDevicesForTaskList() {
        return devicesForTaskList;
    }

    public void setSelectedTask(Task selectedTask) {
        if (selectedTask != null) {
            this.selectedTask = selectedTask;

            Device device = deviceFacade.find(selectedTask.getTodo().getDeviceId());
            this.selectedDevice = device;

            this.selectedMethod = selectedTask.getTodo().getMethodName();

            if (selectedTask.getTodo().getParameter() != null
                    && !selectedTask.getTodo().getParameter().isEmpty()) {
                this.parameter = selectedTask.getTodo().getParameter().get(0);
            }
        }
    }

    public Task getSelectedTask() {
        return selectedTask;
    }

    public Device getSelectedDevice() {
        return selectedDevice;
    }

    public void setSelectedDevice(Device selectedDevice) {
        this.selectedDevice = selectedDevice;

        methodMap = selectedDevice.getType().getMethods();
    }

    public List<Object> getMethods() {
        return Arrays.asList(methodMap.keySet().toArray());
    }

    public String getSelectedMethod() {
        return selectedMethod;
    }

    public void setSelectedMethod(String selectedMethod) {
        this.selectedMethod = selectedMethod;

        this.selectedMethodInfo = methodMap.get(selectedMethod);

        this.parameter = "";
        
        if (selectedMethod.equals("moveToPosition")
                && selectedMethod.equals("setBrightnessCondition")
                && selectedMethod.equals("setTemperatureCondition")) {
            isNotCorrectMethod = false;
        } else {
            isNotCorrectMethod = true;
        }
    }

    public String getSelectedMethodInfo() {
        return selectedMethodInfo;
    }

    public String getParameter() {
        return parameter;
    }

    public void setParameter(String parameter) {
        this.parameter = parameter;
    }

    public boolean isIsNotCorrectMethod() {
        return isNotCorrectMethod;
    }

    public void createTask() {
        if (selectedTask.getName() == null || selectedTask.getName().equals("")) {
            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Info:", "The task must have a name."));
        } else {
            selectedTask.setId(null);
            selectedTask.setDestinationIp(selectedDevice.getRealIp());
            if (parameter == null || parameter.equals("")) {
                selectedTask.setTodo(new CallMessage(selectedDevice.getDeviceId(), selectedMethod, null));
            } else {
                selectedTask.setTodo(new CallMessage(selectedDevice.getDeviceId(), selectedMethod, Arrays.asList(parameter)));
            }
            taskFacade.create(selectedTask);
            
            taskList = taskFacade.findAll();

            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Success!", "The task was created."));
        }
    }

    public void editTask() {
        taskFacade.edit(selectedTask);
        
        FacesContext context = FacesContext.getCurrentInstance();
        context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Success!", "The task was editted."));
    }

    public void deleteTask() {
        if (selectedTask.getId() == null) {
            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Info:", "No task selected."));
        } else {
            if (selectedTask.getProfileList() == null || selectedTask.getProfileList().isEmpty()) {
                taskFacade.remove(selectedTask);
                selectedTask = new Task();
                taskList = taskFacade.findAll();
            } else {
                FacesContext context = FacesContext.getCurrentInstance();
                context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_ERROR, "Failed!", "This task can't be deleted because it's used by a profile."));
            }
        }
    }
}