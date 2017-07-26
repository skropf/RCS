/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package schedule;

import entity.Profile;
import entity.Task;
import java.sql.Timestamp;
import java.text.ParseException;
import java.util.Calendar;
import java.util.List;
import javax.ejb.EJB;
import javax.ejb.Schedule;
import javax.ejb.Singleton;
import mcp.administration.MCPSocketWriter;
import session.ProfileFacade;

/**
 *
 * @author skropf
 */
@Singleton
public class ProfileScheduler {

    @EJB
    private ProfileFacade profileFacade;

    @Schedule(hour = "*", minute = "*/1", persistent = true)
    private void scheduleActiveProfiles() throws ParseException, InterruptedException {
        List<Profile> profileList = profileFacade.findActiveProfiles();

        if (profileList != null && !profileList.isEmpty()) {
            for (Profile profile : profileList) {
                Timestamp timestamp = new Timestamp(Calendar.getInstance().getTime().getTime());
                List<Task> taskList = profile.getTaskList();

                for (Task task : taskList) {
                    if (task.getDays()[timestamp.getDay()] == true
                            && task.getHourTime() == timestamp.getHours()
                            && task.getMinuteTime() == timestamp.getMinutes()) {

                        MCPSocketWriter writer = new MCPSocketWriter(task.getDestinationIp());
                        
                        writer.send(task.getTodo());
                    }
                }
            }
        }
    }
}