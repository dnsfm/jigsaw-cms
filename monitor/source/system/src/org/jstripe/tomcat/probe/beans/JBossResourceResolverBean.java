/*
 * Licensed under the GPL License. You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://probe.jstripe.com/d/license.shtml
 *
 *  THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 *  WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

package org.jstripe.tomcat.probe.beans;

import org.apache.catalina.Context;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.jstripe.tomcat.probe.model.ApplicationResource;
import org.jstripe.tomcat.probe.model.DataSourceInfo;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.management.MBeanServer;
import javax.management.MBeanServerFactory;
import javax.management.MalformedObjectNameException;
import javax.management.ObjectName;
import javax.naming.NamingException;
import javax.sql.DataSource;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * An Adaptor to convert information retrieved from JBoss JMX beans into internal resource model.
 *
 * Author: Vlad Ilyushchenko
 */
public class JBossResourceResolverBean implements ResourceResolver {

    protected Log logger = LogFactory.getLog(getClass());

    protected MBeanServer getJBossMBeanServer() {
        for (Iterator<?> it = MBeanServerFactory.findMBeanServer(null).iterator(); it.hasNext();) {
            MBeanServer server = (MBeanServer) it.next();
            if ("jboss".equals(server.getDefaultDomain())) {
                return server;
            }
        }
        return null;
    }

    public boolean supportsPrivateResources() {
        return false;
    }

    public List<ApplicationResource> getApplicationResources() throws NamingException {

        List<ApplicationResource> resources = new ArrayList<ApplicationResource>();

        MBeanServer server = getJBossMBeanServer();
        if (server != null) {
            try {
                Set<?> dsNames = server.queryNames(new ObjectName("jboss.jca:service=ManagedConnectionPool,*"), null);
                for (Iterator<?> it = dsNames.iterator(); it.hasNext();) {
                    ObjectName managedConnectionPoolOName = (ObjectName) it.next();

                    ApplicationResource resource = new ApplicationResource();
                    resource.setName(managedConnectionPoolOName.getKeyProperty("name"));
                    resource.setType("jboss");
                    String criteria = (String) server.getAttribute(managedConnectionPoolOName, "Criteria");
                    if ("ByApplication".equals(criteria)) {
                        resource.setAuth("Application");
                    } else if ("ByContainerAndApplication".equals(criteria)) {
                        resource.setAuth("Both");
                    } else {
                        resource.setAuth("Container");
                    }
                    DataSourceInfo dsInfo = new DataSourceInfo();
                    dsInfo.setMaxConnections(((Integer) server.getAttribute(managedConnectionPoolOName, "MaxSize")).intValue());
                    dsInfo.setEstablishedConnections(((Integer) server.getAttribute(managedConnectionPoolOName, "ConnectionCount")).intValue());
                    dsInfo.setBusyConnections(((Long) server.getAttribute(managedConnectionPoolOName, "InUseConnectionCount")).intValue());


                    ObjectName connectionFactoryOName = new ObjectName("jboss.jca:service=ManagedConnectionFactory,name=" + resource.getName());
                    Element elm = (Element) server.getAttribute(connectionFactoryOName, "ManagedConnectionFactoryProperties");

                    if (elm != null) {
                        NodeList nl = elm.getChildNodes();
                        for (int i = 0; i < nl.getLength(); i++) {
                            Node n = nl.item(i);
                            Node na = n.getAttributes().getNamedItem("name");
                            if (na != null) {
                                if ("ConnectionURL".equals(na.getNodeValue())) {
                                    dsInfo.setJdbcURL(n.getFirstChild().getNodeValue());
                                }

                                if ("UserName".equals(na.getNodeValue())) {
                                    dsInfo.setUsername(n.getFirstChild().getNodeValue());
                                }

                                //
                                // JMS datasource
                                //
                                if ("JmsProviderAdapterJNDI".equals(na.getNodeValue())) {
                                    dsInfo.setJdbcURL(n.getFirstChild().getNodeValue());
                                    resource.setType("jms");
                                }
                            }
                        }
                    }

                    dsInfo.setResettable(true);

                    resource.setDataSourceInfo(dsInfo);
                    resources.add(resource);
                }
            } catch (Exception e) {
                //
                logger.fatal("There was an error querying JBoss JMX server:", e);
            }
        }
        return resources;
    }

    public List<Object> getApplicationResources(Context context) throws NamingException {
        return new ArrayList<Object>();
    }

    public boolean resetResource(Context context, String resourceName) throws NamingException {
        try {
            ObjectName poolOName = new ObjectName("jboss.jca:service=ManagedConnectionPool,name="+resourceName);
            MBeanServer server = getJBossMBeanServer();
            if (server != null) {
                try {
                    server.invoke(poolOName, "stop", null, null);
                    server.invoke(poolOName, "start", null, null);
                } catch (Exception e) {
                    logger.error("Could not reset resource \""+resourceName+"\"", e);
                    return false;
                }
            }
        } catch (MalformedObjectNameException e) {
            throw new NamingException("Resource name: \""+resourceName + "\" makes a malformed ObjectName");
        }
        return false;
    }

    public DataSource lookupDataSource(Context context, String resourceName) throws NamingException {
        throw new UnsupportedOperationException("This feature has not been implemented for JBoss server yet.");
    }
}
