/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import entity.Device;
import entity.Log;
import java.io.Serializable;
import java.util.List;
import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import session.DeviceFacade;
import session.LogFacade;

/**
 *
 * @author skropf
 */
@ManagedBean
@SessionScoped
public class LogController implements Serializable {

    @EJB private LogFacade logFacade;
    @EJB private DeviceFacade deviceFacade;
    
    private List<Log> logList;
    
    public LogController() {
    }
    
    @PostConstruct
    public void init() {
        logList = logFacade.findAll();
    }

    public String getLogs() {
        Device device;
        Log log;
        String logText = "";
        
        for (int i = 0; i < logList.size(); i++) {
            log = logList.get(i);
            logText += log.getTime() + " || ";
            device = deviceFacade.findbyDeviceId(log.getDeviceId());
            
            if (device != null) {
                logText += device.getName() + " || ";
            }
            
            switch (logList.get(i).getStatus()) {
                case NORMAL:
                    logText += "" + logList.get(i).toString() + "\n";
                    break;
                case WARNING:
                    logText += "" + logList.get(i).toString() + "\n";
                    break;
                case ERROR:
                    logText += "" + logList.get(i).toString() + "\n";
                    break;
            }
            
        }
        return logText;
    }
}