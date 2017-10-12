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

package org.jstripe.tomcat.probe.controllers.cluster;

import org.jstripe.tomcat.probe.beans.ClusterWrapperBean;
import org.jstripe.tomcat.probe.controllers.TomcatContainerController;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ClusterStatsController extends TomcatContainerController {
    private ClusterWrapperBean clusterWrapper;
    private boolean loadMembers = true;

    public ClusterWrapperBean getClusterWrapper() {
        return clusterWrapper;
    }

    public void setClusterWrapper(ClusterWrapperBean clusterWrapper) {
        this.clusterWrapper = clusterWrapper;
    }

    public boolean isLoadMembers() {
        return loadMembers;
    }

    public void setLoadMembers(boolean loadMembers) {
        this.loadMembers = loadMembers;
    }

    protected ModelAndView handleRequestInternal(HttpServletRequest request, HttpServletResponse response) throws Exception {
        return new ModelAndView(getViewName(), "cluster",
                clusterWrapper.getCluster(getContainerWrapper().getTomcatContainer().getHostName(), loadMembers));
    }
}
