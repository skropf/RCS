/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package converter;

import entity.Task;
import javax.faces.component.UIComponent;
import javax.faces.context.FacesContext;
import javax.faces.convert.Converter;
import javax.faces.convert.FacesConverter;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import session.TaskFacade;

/**
 *
 * @author skropf
 */
@FacesConverter(forClass=Task.class, value="TaskConverter")
public class TaskConverter implements Converter {

    TaskFacade taskFacade;
    
    @Override
    public Object getAsObject(FacesContext context, UIComponent component, String value) {
        try {
            InitialContext ic = new InitialContext();
            taskFacade = (TaskFacade) ic.lookup("java:global/RCSServer/RCSServer-ejb/TaskFacade");
        } catch (NamingException e) {
            System.err.println(e.toString());
        }
        String taskName = value.split("-")[0].trim();
        return taskFacade.findbyName(taskName);
    }

    @Override
    public String getAsString(FacesContext context, UIComponent component, Object value) {
        return ((Task)value).toString();
    }
}