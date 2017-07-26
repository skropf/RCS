package entity;

import java.io.Serializable;
import javax.persistence.*;

/**
 *
 * @author skropf
 */
@Entity
@NamedQueries({
    @NamedQuery(name="MCPPlace.findbyIP", query="SELECT m FROM MCPPlace m WHERE m.ip = :ip")
})
public class MCPPlace implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String place;
    private String ip;
    private boolean loggingActivated;

    public MCPPlace() {
    }

    public MCPPlace(String place, String ip, boolean loggingActivated) {
        this.place = place;
        this.ip = ip;
        this.loggingActivated = loggingActivated;
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

    public String getPlace() {
        return place;
    }

    public void setPlace(String place) {
        this.place = place;
    }

    public boolean isLoggingActivated() {
        return loggingActivated;
    }

    public void setLoggingActivated(boolean loggingActivated) {
        this.loggingActivated = loggingActivated;
    }
}
