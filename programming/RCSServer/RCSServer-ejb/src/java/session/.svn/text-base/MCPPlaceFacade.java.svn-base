/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package session;

import entity.MCPPlace;
import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author skropf
 */
@Stateless
public class MCPPlaceFacade extends AbstractFacade<MCPPlace> {
    @PersistenceContext(unitName = "RCSServer-ejbPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public MCPPlaceFacade() {
        super(MCPPlace.class);
    }
    
    public MCPPlace findbyIP(String ip) {
        List<MCPPlace> list = em.createNamedQuery("MCPPlace.findbyIP", MCPPlace.class)
                .setParameter("ip", ip)
                .getResultList();
        
        return list.isEmpty() ? null : list.get(0);
    }
}
