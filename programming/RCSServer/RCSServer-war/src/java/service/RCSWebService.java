package service;

import entity.Device;
import javax.ejb.EJB;
import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebService;
import session.DeviceFacade;

/**
 *
 * @author skropf
 */
@WebService(serviceName = "RCSWebService")
public class RCSWebService {

    @EJB
    private DeviceFacade deviceFacade;

    /**
     * Web service operation
     */
    @WebMethod(operationName = "getDeviceByName")
    public Device getDeviceByName(@WebParam(name = "name") String name) {
        return deviceFacade.findbyName(name);
    }

    /**
     * Web service operation
     */
    @WebMethod(operationName = "getDeviceById")
    public Device getDeviceById(@WebParam(name = "deviceId") int deviceId) {
        return deviceFacade.findbyDeviceId(deviceId);
    }
}