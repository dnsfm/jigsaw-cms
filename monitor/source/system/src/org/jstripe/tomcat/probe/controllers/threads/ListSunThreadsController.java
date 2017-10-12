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

package org.jstripe.tomcat.probe.controllers.threads;

import org.apache.commons.modeler.Registry;
import org.jstripe.tomcat.probe.model.SunThread;
import org.jstripe.tomcat.probe.model.ThreadStackElement;
import org.jstripe.tomcat.probe.tools.JmxTools;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.ParameterizableViewController;

import javax.management.MBeanServer;
import javax.management.ObjectName;
import javax.management.openmbean.CompositeData;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.ArrayList;
import java.util.List;

public class ListSunThreadsController extends ParameterizableViewController {

    protected ModelAndView handleRequestInternal(HttpServletRequest request, HttpServletResponse response) throws Exception {

        List<SunThread> threads = null;
        int executionStackDepth = 1;

        MBeanServer mBeanServer = new Registry().getMBeanServer();
        ObjectName threadingOName = new ObjectName("java.lang:type=Threading");

        long deadlockedIds[] = (long[]) mBeanServer.invoke(threadingOName, "findMonitorDeadlockedThreads", null, null);
        long allIds[] = (long[]) mBeanServer.getAttribute(threadingOName, "AllThreadIds");

        if (allIds != null) {
            threads = new ArrayList<SunThread>(allIds.length);

            for (int i = 0; i < allIds.length; i++) {
                CompositeData cd = (CompositeData) mBeanServer.invoke(threadingOName, "getThreadInfo",
                        new Object[]{new Long(allIds[i]), new Integer(executionStackDepth)}, new String[]{"long", "int"});

                if (cd != null) {
                    SunThread st = new SunThread();
                    st.setId(JmxTools.getLongAttr(cd, "threadId"));
                    st.setName(JmxTools.getStringAttr(cd, "threadName"));
                    st.setState(JmxTools.getStringAttr(cd, "threadState"));
                    st.setSuspended(JmxTools.getBooleanAttr(cd, "suspended"));
                    st.setInNative(JmxTools.getBooleanAttr(cd, "inNative"));
                    st.setLockName(JmxTools.getStringAttr(cd, "lockName"));
                    st.setLockOwnerName(JmxTools.getStringAttr(cd, "lockOwnerName"));
                    st.setWaitedCount(JmxTools.getLongAttr(cd, "waitedCount"));
                    st.setBlockedCount(JmxTools.getLongAttr(cd, "blockedCount"));
                    st.setDeadlocked(contains(deadlockedIds, st.getId()));

                    CompositeData[] stack = (CompositeData[]) cd.get("stackTrace");
                    if (stack.length > 0) {
                        CompositeData cd2 = stack[0];
                        ThreadStackElement tse = new ThreadStackElement();
                        tse.setClassName(JmxTools.getStringAttr(cd2, "className"));
                        tse.setFileName(JmxTools.getStringAttr(cd2, "fileName"));
                        tse.setMethodName(JmxTools.getStringAttr(cd2, "methodName"));
                        tse.setLineNumber(JmxTools.getIntAttr(cd2, "lineNumber", -1));
                        tse.setNativeMethod(JmxTools.getBooleanAttr(cd2, "nativeMethod"));
                        st.setExecutionPoint(tse);
                    }

                    threads.add(st);
                }
            }
        }
        return new ModelAndView(getViewName(), "threads", threads);
    }

    private static boolean contains(long[] array, long e) {
        if (array != null) {
            for (int i = 0; i < array.length; i++) {
                if (array[i] == e) return true;
            }
        }
        return false;
    }
}
