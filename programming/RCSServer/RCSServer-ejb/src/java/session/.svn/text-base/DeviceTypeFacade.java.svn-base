/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package session;

import entity.DeviceType;
import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author skropf
 */
@Stateless
public class DeviceTypeFacade extends AbstractFacade<DeviceType> {
    @PersistenceContext(unitName = "RCSServer-ejbPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public DeviceTypeFacade() {
        super(DeviceType.class);
    }
    
    public DeviceType findbyType(String deviceType) {
        List<DeviceType> list =  em.createNamedQuery("DeviceType.findbyType", DeviceType.class)
                .setParameter("deviceType", deviceType).getResultList();
        return list == null ? null : list.get(0);
    }
}