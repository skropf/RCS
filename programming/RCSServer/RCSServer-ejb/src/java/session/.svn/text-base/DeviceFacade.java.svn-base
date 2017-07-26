/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package session;

import entity.Device;
import entity.DeviceType;
import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.NoResultException;
import javax.persistence.PersistenceContext;

/**
 *
 * @author skropf
 */
@Stateless
public class DeviceFacade extends AbstractFacade<Device> {

    @PersistenceContext(unitName = "RCSServer-ejbPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public DeviceFacade() {
        super(Device.class);
    }

    public Device findbyDeviceId(int deviceId) {
        try {
            return em.createNamedQuery("Device.findbyDeviceId", Device.class)
                    .setParameter("deviceId", deviceId)
                    .getSingleResult();
        } catch (NoResultException ex) {
            return null;
        }

    }

    public Device findbyName(String name) {
        try {
            return (Device) em.createNamedQuery("Device.findbyName")
                    .setParameter("name", name)
                    .getSingleResult();
        } catch (NoResultException ex) {
            return null;
        }
    }
    
    public List<Device> findbyType(DeviceType type) {
        return em.createNamedQuery("Device.findbyType", Device.class)
                    .setParameter("type", type)
                    .getResultList();
    }
    
    public List<Device> findAllExceptSensorDevice() {
        List<Device> list = em.createNamedQuery("Device.findAllExceptSensorDevice", Device.class)
                .getResultList();
        
        for (int i = list.size() - 1; i >= 0; i--) {
            if (list.get(i).getType().getDeviceType().equals("SensorDevice")) list.remove(list.get(i));
        }
        return list;
    }
}