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
package org.jstripe.tomcat.probe.model.jmx;

import javax.management.ObjectName;
import java.util.ArrayList;
import java.util.List;

/**
 * This bean represens a hierarchy of Tomcat's ObjectNames necessary to display real-time connection information
 * on "status" tab.
 *
 * Author: Vlad Ilyushchenko
 */
public class ThreadPoolObjectName  {

    private ObjectName threadPoolName;
    private ObjectName globalRequestProcessorName;
    @SuppressWarnings("unchecked")
	private List requestProcessorNames = new ArrayList();

    public ObjectName getThreadPoolName() {
        return threadPoolName;
    }

    public ObjectName getGlobalRequestProcessorName() {
        return globalRequestProcessorName;
    }

    @SuppressWarnings("unchecked")
	public List getRequestProcessorNames() {
        return requestProcessorNames;
    }

    public void setThreadPoolName(ObjectName threadPoolName) {
        this.threadPoolName = threadPoolName;
    }

    public void setGlobalRequestProcessorName(ObjectName globalRequestProcessorName) {
        this.globalRequestProcessorName = globalRequestProcessorName;
    }

    @SuppressWarnings("unchecked")
	public void setRequestProcessorNames(List requestProcessorNames) {
        this.requestProcessorNames = requestProcessorNames;
    }
}
