/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import entity.MCPPlace;
import java.io.Serializable;
import java.util.Arrays;
import java.util.List;
import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.faces.application.FacesMessage;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;
import mcp.CallMessage;
import mcp.administration.MCPSocketWriter;
import session.DeviceTypeFacade;
import session.MCPPlaceFacade;

/**
 *
 * @author skropf
 */
@ManagedBean
@SessionScoped
public class SettingsController implements Serializable {

    @EJB
    private MCPPlaceFacade mcpPlaceFacade;
    private List<MCPPlace> mcpPlaceList;

    /**
     * Creates a new instance of SettingsController
     */
    public SettingsController() {
    }
    @EJB
    private DeviceTypeFacade dtf;

    @PostConstruct
    public void init() {
        mcpPlaceList = mcpPlaceFacade.findAll();
    }

    public List<MCPPlace> getMCPPlaceList() {
        return mcpPlaceList;
    }

    public void setMCPPlaceList(List<MCPPlace> mcpPlaceList) {
        this.mcpPlaceList = mcpPlaceList;
    }

    public void addMCPPlace() {
        this.mcpPlaceList.add(new MCPPlace());
    }

    public void removeMCPPlace(int id) {
        for (MCPPlace mcpPlace : mcpPlaceList) {
            if (mcpPlace.getId() != null && mcpPlace.getId() == id) {
                mcpPlaceList.remove(mcpPlace);
                FacesContext context = FacesContext.getCurrentInstance();
                context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Success!", "The data was successfully deleted!"));
                break;
            }
        }
    }

    public void saveList() {
        MCPSocketWriter writer;
        for (MCPPlace mcpPlace : mcpPlaceList) {
            if (mcpPlace.getId() != null) {
                mcpPlaceFacade.edit(mcpPlace);
            } else {
                mcpPlaceFacade.create(mcpPlace);
            }

            if (mcpPlace.isLoggingActivated()) {
                writer = new MCPSocketWriter(mcpPlace.getIp());
                writer.send(new CallMessage(0, "logging", Arrays.asList("1")));
            } else {
                writer = new MCPSocketWriter(mcpPlace.getIp());
                writer.send(new CallMessage(0, "logging", Arrays.asList("0")));
            }
        }
        FacesContext context = FacesContext.getCurrentInstance();
        context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Success!", "The data was successfully saved!"));
    }

    public void retrieveDevices() {
        MCPSocketWriter writer;
        for (MCPPlace mcpPlace : mcpPlaceList) {
            writer = new MCPSocketWriter(mcpPlace.getIp());
            writer.send(new CallMessage(0, "getDevices", null));
        }
        FacesContext context = FacesContext.getCurrentInstance();
        context.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Info!", "The messages were sent!"));
    }
}