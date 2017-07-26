/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import entity.Profile;
import entity.Task;
import java.io.Serializable;
import java.util.List;
import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;
import org.primefaces.model.DualListModel;
import session.ProfileFacade;
import session.TaskFacade;

/**
 *
 * @author skropf
 */
@ManagedBean
@SessionScoped
public class ProfileController implements Serializable {

    @EJB
    private ProfileFacade profileFacade;
    @EJB
    private TaskFacade taskFacade;
    private List<Profile> profileList;
    private List<Task> selectedTasks, tasks;
    private Profile selectedProfile = new Profile();
    private Task selectedTask;
    private DualListModel<Task> dualListModel;

    public ProfileController() {
    }

    @PostConstruct
    public void init() {
        profileList = profileFacade.findAll();
        dualListModel = new DualListModel<Task>();
    }

    public Profile getSelectedProfile() {
        return selectedProfile;
    }

    public void setSelectedProfile(Profile selectedProfile) {
        if (selectedProfile != null) {
            this.selectedProfile = selectedProfile;
            
            selectedTasks = selectedProfile.getTaskList();
            tasks = taskFacade.findAll();

            for (Task stask : selectedTasks) {
                for (int i = tasks.size() - 1; i >= 0; i--) {
                    if (stask.getId() == tasks.get(i).getId()) {
                        tasks.remove(tasks.get(i));
                    }
                }
            }
            dualListModel = new DualListModel<Task>(selectedTasks, tasks);
        }
    }

    public List<Profile> getProfileList() {
        return profileList;
    }

    public List<Task> getSelectedTasks() {
        return selectedTasks;
    }

    public List<Task> getTasks() {
        return tasks;
    }

    public DualListModel<Task> getDualListModel() {
        return dualListModel;
    }

    public void setDualListModel(DualListModel<Task> dualListModel) {
        this.dualListModel = dualListModel;
    }

    public void createProfile() {
        if (selectedProfile.getName() != null && !selectedProfile.getName().equals("")) {
            Profile profile = new Profile(selectedProfile.getName(), selectedProfile.isActive());
            profileFacade.create(profile);

            profileList = profileFacade.findAll();

            selectedProfile = new Profile();

            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Success!", "The profile was created."));
        } else {
            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Failed!", "The profile can't be created. Please fill in a name."));
        }
    }

    public void editProfile() {
        if (selectedProfile.getId() != null) {
            profileFacade.edit(selectedProfile);

            profileList = profileFacade.findAll();

            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Success!", "The profile was editted."));
        } else {
            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Failed!", "The profile you want to edit doesn't exist."));
        }
    }
    
    public void addTasksToProfile() {
        if (selectedProfile.getId() != null) {
            selectedProfile.setTaskList(dualListModel.getSource());
            
            profileFacade.edit(selectedProfile);
            
            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Success!", "The profile was saved."));
        } else {
            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Failed!", "No profile selected."));
        }
    }

    public void deleteProfile() {
        if (selectedProfile != null && selectedProfile.getId() != null) {
            selectedProfile.getTaskList().clear();
            profileFacade.edit(selectedProfile);
            profileFacade.remove(selectedProfile);

            profileList = profileFacade.findAll();

            selectedProfile = new Profile();

            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Success!", "The profile was deleted."));
        } else {
            FacesContext context = FacesContext.getCurrentInstance();
            context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Failed!", "No profile selected."));
        }
    }
}