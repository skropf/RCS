/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package session;

import entity.Profile;
import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author skropf
 */
@Stateless
public class ProfileFacade extends AbstractFacade<Profile> {
    @PersistenceContext(unitName = "RCSServer-ejbPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public ProfileFacade() {
        super(Profile.class);
    }
    
    public List<Profile> findActiveProfiles() {
        return em.createNamedQuery("Profile.findActiveProfiles", Profile.class)
                .getResultList();
    }
}