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

import net.sf.javainetlocator.InetAddressLocator;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.commons.modeler.Registry;
import org.jstripe.tomcat.probe.model.RequestProcessor;
import org.jstripe.tomcat.probe.model.ThreadPool;
import org.jstripe.tomcat.probe.model.jmx.ThreadPoolObjectName;
import org.jstripe.tomcat.probe.tools.JmxTools;

import javax.management.*;

import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * This class interfaces Tomcat JMX functionality to read connection status. The class
 * essentially provides and maintains the list of connection ThreadPools.
 * <p/>
 * Author: Vlad Ilyushchenko
 */
public class ContainerListenerBean implements NotificationListener {

    private Log logger = LogFactory.getLog(getClass());
    private List<ThreadPoolObjectName> poolNames = null;

    private boolean isInitialized() {
        return poolNames != null;
    }

    /**
     * Finds ThreadPoolObjectName by its string name.
     *
     * @return null if the input name is null or ThreadPoolObjectName is not found
     */
    private ThreadPoolObjectName findPool(String name) {
        if (name != null && isInitialized()) {
            for (Iterator<ThreadPoolObjectName> it = poolNames.iterator(); it.hasNext();) {
                ThreadPoolObjectName threadPoolObjectName = (ThreadPoolObjectName) it.next();
                if (name.equals(threadPoolObjectName.getThreadPoolName().getKeyProperty("name"))) {
                    return threadPoolObjectName;
                }
            }
        }
        return null;
    }

    /**
     * Handles creation and deletion of new "worker" threads.
     */
    @SuppressWarnings("unchecked")
	public synchronized void handleNotification(Notification notification, Object object) {
        if (notification instanceof MBeanServerNotification) {
            ObjectName objectName = ((MBeanServerNotification) notification).getMBeanName();

            if (notification.getType().equals(MBeanServerNotification.REGISTRATION_NOTIFICATION)) {

                if ("RequestProcessor".equals(objectName.getKeyProperty("type"))) {
                    ThreadPoolObjectName threadPoolObjectName = findPool(objectName.getKeyProperty("worker"));
                    if (threadPoolObjectName != null) threadPoolObjectName.getRequestProcessorNames().add(objectName);
                }

            } else if (notification.getType().equals(MBeanServerNotification.UNREGISTRATION_NOTIFICATION)) {

                if ("RequestProcessor".equals(objectName.getKeyProperty("type"))) {
                    ThreadPoolObjectName threadPoolObjectName = findPool(objectName.getKeyProperty("worker"));
                    if (threadPoolObjectName != null)
                        threadPoolObjectName.getRequestProcessorNames().remove(objectName);
                }
            }
        }
    }

    /**
     * Load ObjectNames for the relevant MBeans so they can be queried at a later stage without searching MBean server
     * over and over again.
     *
     * @throws Exception
     */
    @SuppressWarnings("unchecked")
	private synchronized void initialize() throws Exception {

        MBeanServer server = new Registry().getMBeanServer();
        Set set = server.queryMBeans(new ObjectName("*:type=ThreadPool,*"), null);
        poolNames = new ArrayList<ThreadPoolObjectName>(set.size());
        for (Iterator it = set.iterator(); it.hasNext();) {

            ThreadPoolObjectName threadPoolObjectName = new ThreadPoolObjectName();
            ObjectName threadPoolName = ((ObjectInstance) it.next()).getObjectName();

            String name = threadPoolName.getKeyProperty("name");

            threadPoolObjectName.setThreadPoolName(threadPoolName);
            ObjectName grpName = server.getObjectInstance(
                    new ObjectName(threadPoolName.getDomain() + ":type=GlobalRequestProcessor,name=" + name)).getObjectName();
            threadPoolObjectName.setGlobalRequestProcessorName(grpName);

            //
            // unfortunately exact workers could not be found at the time of testing
            // so we filter out the relevant workers within the loop
            //
            Set workers = server.queryMBeans(new ObjectName(threadPoolName.getDomain() + ":type=RequestProcessor,*"), null);

            for (Iterator wrkIt = workers.iterator(); wrkIt.hasNext();) {
                ObjectName wrkName = ((ObjectInstance) wrkIt.next()).getObjectName();
                if (name.equals(wrkName.getKeyProperty("worker"))) {
                    threadPoolObjectName.getRequestProcessorNames().add(wrkName);
                }
            }

            poolNames.add(threadPoolObjectName);
        }

        // Register with MBean server
        server.addNotificationListener(new ObjectName("JMImplementation:type=MBeanServerDelegate"), this, null, null);

    }

    @SuppressWarnings("unchecked")
	public synchronized List<ThreadPool> getThreadPools(boolean includeRequestProcessors) throws Exception {

        if (!isInitialized()) initialize();

        List<ThreadPool> threadPools = new ArrayList<ThreadPool>(poolNames.size());

        MBeanServer server = new Registry().getMBeanServer();

        for (Iterator<ThreadPoolObjectName> it = poolNames.iterator(); it.hasNext();) {

            ThreadPoolObjectName threadPoolObjectName = (ThreadPoolObjectName) it.next();
            try {
                ObjectName poolName = threadPoolObjectName.getThreadPoolName();

                ThreadPool threadPool = new ThreadPool();
                threadPool.setName(poolName.getKeyProperty("name"));
                threadPool.setMaxThreads(JmxTools.getIntAttr(server, poolName, "maxThreads"));

                if (JmxTools.hasAttribute(server, poolName, "maxSpareThreads")) {
                    threadPool.setMaxSpareThreads(JmxTools.getIntAttr(server, poolName, "maxSpareThreads"));
                    threadPool.setMinSpareThreads(JmxTools.getIntAttr(server, poolName, "minSpareThreads"));
                }

                threadPool.setCurrentThreadsBusy(JmxTools.getIntAttr(server, poolName, "currentThreadsBusy"));
                threadPool.setCurrentThreadCount(JmxTools.getIntAttr(server, poolName, "currentThreadCount"));


                ObjectName grpName = threadPoolObjectName.getGlobalRequestProcessorName();

                threadPool.setMaxTime(JmxTools.getLongAttr(server, grpName, "maxTime"));
                threadPool.setProcessingTime(JmxTools.getLongAttr(server, grpName, "processingTime"));
                threadPool.setBytesReceived(JmxTools.getLongAttr(server, grpName, "bytesReceived"));
                threadPool.setBytesSent(JmxTools.getLongAttr(server, grpName, "bytesSent"));
                threadPool.setRequestCount(JmxTools.getIntAttr(server, grpName, "requestCount"));
                threadPool.setErrorCount(JmxTools.getIntAttr(server, grpName, "errorCount"));

                if (includeRequestProcessors) {
                    for (Iterator<ObjectName> wrkIt = threadPoolObjectName.getRequestProcessorNames().iterator(); wrkIt.hasNext();) {
                        ObjectName wrkName = (ObjectName) wrkIt.next();

                        try {
                            RequestProcessor rp = new RequestProcessor();
                            rp.setName(wrkName.getKeyProperty("name"));
                            rp.setStage(JmxTools.getIntAttr(server, wrkName, "stage"));
                            rp.setProcessingTime(JmxTools.getLongAttr(server, wrkName, "requestProcessingTime"));
                            rp.setBytesSent(JmxTools.getLongAttr(server, wrkName, "requestBytesSent"));
                            rp.setBytesReceived(JmxTools.getLongAttr(server, wrkName, "requestBytesReceived"));
                            rp.setRemoteAddr(JmxTools.getStringAttr(server, wrkName, "remoteAddr"));
                            rp.setRemoteAddrLocale(InetAddressLocator.getLocale(InetAddress.getByName(rp.getRemoteAddr()).getAddress()));
                            rp.setVirtualHost(JmxTools.getStringAttr(server, wrkName, "virtualHost"));
                            rp.setMethod(JmxTools.getStringAttr(server, wrkName, "method"));
                            rp.setCurrentUri(JmxTools.getStringAttr(server, wrkName, "currentUri"));
                            rp.setCurrentQueryString(JmxTools.getStringAttr(server, wrkName, "currentQueryString"));
                            rp.setProtocol(JmxTools.getStringAttr(server, wrkName, "protocol"));
                            threadPool.addRequestProcessor(rp);
                        } catch (InstanceNotFoundException e) {
                            logger.info("Failed to query RequestProcessor " + wrkName);
                            logger.debug(e);
                        }
                    }
                }

                threadPools.add(threadPool);
            } catch (InstanceNotFoundException e) {
                logger.error("Failed to query entire thread pool " + threadPoolObjectName);
                logger.debug(e);
            }
        }
        return threadPools;
    }

    public synchronized List<String> getThreadPoolNames() throws Exception {

        if (!isInitialized()) initialize();

        List<String> threadPoolNames = new ArrayList<String>(poolNames.size());

        for (Iterator<ThreadPoolObjectName> it = poolNames.iterator(); it.hasNext();) {

            ThreadPoolObjectName threadPoolObjectName = (ThreadPoolObjectName) it.next();
            ObjectName poolName = threadPoolObjectName.getThreadPoolName();
            threadPoolNames.add(poolName.getKeyProperty("name"));
        }
        return threadPoolNames;
    }
}

