/**
 * Licensed under the GPL License. You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://probe.jstripe.com/d/license.shtml
 *
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
package org.jstripe.tomcat.probe.beans;

import org.apache.catalina.Wrapper;
import org.apache.catalina.util.ServerInfo;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.jstripe.tomcat.probe.TomcatContainer;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;

/**
 * This class wires support for Tomcat "privileged" context functionality into Spring.
 * If application context is privileged Tomcat would always call servlet.setWrapper method on each request.
 * ContainerWrapperBean wires the passed wrapper to the relevant Tomcat container adaptor class, which in turn helps
 * the Probe to interpret the wrapper. Container adaptors are required because internal wrapper structure is quite
 * different between Tomcat 5.5.x and Tomcat 5.0.x
 *
 * Author: Vlad Ilyushchenko
 *
 */
public class ContainerWrapperBean {

    private Log logger = LogFactory.getLog(getClass());

    private TomcatContainer tomcatContainer = null;

    /**
     * List of class names to adapt particular Tomcat implementation to TomcatContainer interface
     */
    private List<Object> adaptorClasses = new ArrayList<Object>();

    private ResourceResolver resourceResolver;

    private boolean forceFirstAdaptor = false;

    @SuppressWarnings("unchecked")
	private Map resourceResolvers;

    public boolean isForceFirstAdaptor() {
        return forceFirstAdaptor;
    }

    public void setForceFirstAdaptor(boolean forceFirstAdaptor) {
        this.forceFirstAdaptor = forceFirstAdaptor;
    }

    public void setWrapper(Wrapper wrapper) {
        if (tomcatContainer == null) {
            String serverInfo = ServerInfo.getServerInfo();
            logger.debug("Server info: "+serverInfo);
            for (int i = 0; i < adaptorClasses.size(); i++) {
                String className = (String) adaptorClasses.get(i);
                try {
                    Object o = Class.forName(className).newInstance();
                    logger.debug("Testing container adaptor: "+className);
                    if (o instanceof TomcatContainer) {
                        if (forceFirstAdaptor || ((TomcatContainer)o).canBoundTo(serverInfo)) {
                            logger.info("Using "+className);
                            tomcatContainer = (TomcatContainer) o;
                            tomcatContainer.setWrapper(wrapper);
                            break;
                        } else {
                            logger.debug("Cannot bind "+className+" to "+serverInfo);
                        }
                    } else {
                        logger.error(className + " does not implement " + TomcatContainer.class.getName());
                    }
                } catch (Throwable e) {
                    logger.info("Failed to load " + className);
                    //
                    // make sure we always re-throw ThreadDeath
                    //
                    if (e instanceof ThreadDeath) throw (ThreadDeath)e;
                }
            }

            if (tomcatContainer == null) logger.fatal("No suitable container adaptor found!");
        }
    }

    public TomcatContainer getTomcatContainer() {
        return tomcatContainer;
    }

    public List<Object> getAdaptorClasses() {
        return adaptorClasses;
    }

    public void setAdaptorClasses(List<Object> adaptorClasses) {
        this.adaptorClasses = adaptorClasses;
    }

    public ResourceResolver getResourceResolver() {
        if (resourceResolver == null) {
            if (System.getProperty("jboss.server.name") != null) {
                resourceResolver = (ResourceResolver) resourceResolvers.get("jboss");
                logger.info("Using JBOSS resource resolver");
            } else {
                resourceResolver = (ResourceResolver) resourceResolvers.get("default");
                logger.info("Using DEFAULT resource resolver");
            }
        }
        return resourceResolver;
    }

    @SuppressWarnings("unchecked")
	public Map getResourceResolvers() {
        return resourceResolvers;
    }

    @SuppressWarnings("unchecked")
	public void setResourceResolvers(Map resourceResolvers) {
        this.resourceResolvers = resourceResolvers;
    }
}
