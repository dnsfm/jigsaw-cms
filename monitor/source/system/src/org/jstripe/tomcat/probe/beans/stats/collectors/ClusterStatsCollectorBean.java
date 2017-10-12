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

package org.jstripe.tomcat.probe.beans.stats.collectors;

import org.jstripe.tomcat.probe.beans.ClusterWrapperBean;
import org.jstripe.tomcat.probe.beans.ContainerWrapperBean;
import org.jstripe.tomcat.probe.model.jmx.Cluster;

public class ClusterStatsCollectorBean extends BaseStatsCollectorBean {
    private ContainerWrapperBean containerWrapper;
    private ClusterWrapperBean clusterWrapper;

    public ContainerWrapperBean getContainerWrapper() {
        return containerWrapper;
    }

    public void setContainerWrapper(ContainerWrapperBean containerWrapper) {
        this.containerWrapper = containerWrapper;
    }

    public ClusterWrapperBean getClusterWrapper() {
        return clusterWrapper;
    }

    public void setClusterWrapper(ClusterWrapperBean clusterWrapper) {
        this.clusterWrapper = clusterWrapper;
    }

    public void collect() throws Exception {
        // Job can be called before the servlet finished intialisation. Make sure
        // we dont get an NPE.
        if (containerWrapper.getTomcatContainer() != null) {
            Cluster cluster = clusterWrapper.getCluster(containerWrapper.getTomcatContainer().getHostName(), false);
            if (cluster != null) {
                buildDeltaStats("cluster.received", cluster.getTotalReceivedBytes());
                buildDeltaStats("cluster.sent", cluster.getSenderTotalBytes());
                buildDeltaStats("cluster.req.received", cluster.getNrOfMsgsReceived());
                buildDeltaStats("cluster.req.sent", cluster.getSenderNrOfRequests());
            }
        }
    }
}
