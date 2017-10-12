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

package org.jstripe.tomcat.probe.controllers.logs;

import org.apache.catalina.Context;
import org.jstripe.tomcat.probe.model.Application;
import org.jstripe.tomcat.probe.model.DisconnectedLogDestination;
import org.jstripe.tomcat.probe.tools.logging.jdk.Jdk14LoggerAccessor;
import org.jstripe.tomcat.probe.tools.logging.jdk.Jdk14ManagerAccessor;
import org.jstripe.tomcat.probe.tools.logging.log4j.Log4JLoggerAccessor;
import org.jstripe.tomcat.probe.tools.logging.log4j.Log4JManagerAccessor;
import org.jstripe.tomcat.probe.tools.logging.commons.CommonsLoggerAccessor;
import org.jstripe.tomcat.probe.tools.logging.catalina.CatalinaLoggerAccessor;
import org.jstripe.tomcat.probe.tools.logging.DefaultAccessor;
import org.jstripe.tomcat.probe.tools.logging.LogDestination;
import org.jstripe.tomcat.probe.tools.logging.FileLogAccessor;
import org.jstripe.tomcat.probe.tools.Instruments;
import org.jstripe.tomcat.probe.tools.ApplicationUtils;
import org.jstripe.tomcat.probe.controllers.TomcatContainerController;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.bind.ServletRequestUtils;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.*;
import java.io.File;

@SuppressWarnings("deprecation")
public class ListLogsController extends TomcatContainerController {

    private String errorView;
    @SuppressWarnings("unchecked")
	private List stdoutFiles = new ArrayList();

    public String getErrorView() {
        return errorView;
    }

    public void setErrorView(String errorView) {
        this.errorView = errorView;
    }

    @SuppressWarnings("unchecked")
	public List getStdoutFiles() {
        return stdoutFiles;
    }

    @SuppressWarnings("unchecked")
	public void setStdoutFiles(List stdoutFiles) {
        this.stdoutFiles = stdoutFiles;
    }

    @SuppressWarnings("unchecked")
	protected ModelAndView handleRequestInternal(HttpServletRequest request, HttpServletResponse response) throws Exception {

        if (Instruments.isInitilized()) {
            List<DefaultAccessor> allAppenders = new ArrayList<DefaultAccessor>();

            //
            // interrogate classloader hierarchy
            //
            ClassLoader cl2 = Thread.currentThread().getContextClassLoader().getParent();
            while (cl2 != null) {
                interrogateClassLoader(cl2, null, allAppenders);
                cl2 = cl2.getParent();
            }

            //
            // check for known stdout files, such as "catalina.out"
            //
            interrogateStdOutFiles(allAppenders);

            //
            // interrogate webapp classloaders and avilable loggers
            //
            List<?> contexts = getContainerWrapper().getTomcatContainer().findContexts();
            for (int i = 0; i < contexts.size(); i++) {

                Context ctx = (Context) contexts.get(i);
                Application application = ApplicationUtils.getApplication(ctx);

                ClassLoader cl = ctx.getLoader().getClassLoader();

                try {
                    Object contextLogger = getContainerWrapper().getTomcatContainer().getLogger(ctx);
                    if (contextLogger != null) {
                        if (contextLogger.getClass().getName().startsWith("org.apache.commons.logging")) {
                            CommonsLoggerAccessor commonsAccessor = new CommonsLoggerAccessor();
                            commonsAccessor.setTarget(contextLogger);
                            commonsAccessor.setApplication(application);
                            allAppenders.addAll(commonsAccessor.getDestinations());
                        } else if (contextLogger.getClass().getName().startsWith("org.apache.catalina.logger")) {
                            CatalinaLoggerAccessor catalinaAccessor = new CatalinaLoggerAccessor();
                            catalinaAccessor.setApplication(application);
                            catalinaAccessor.setTarget(contextLogger);
                            catalinaAccessor.setLogClass("catalina");
                            allAppenders.add(catalinaAccessor);
                        }
                    }
                } catch (Throwable e) {
                    logger.error("Could not interrogate context logger for " + ctx.getName() + ". Enable debug logging to see the trace stack");
                    logger.debug(e);
                }

                if (application.isAvailable()) {
                    ClassLoader thisCl = Thread.currentThread().getContextClassLoader();
                    Thread.currentThread().setContextClassLoader(cl);
                    try {
                        interrogateClassLoader(cl, application, allAppenders);
                    } catch (Exception e) {
                        logger.error("Could not interrogate classloader loggers for " + ctx.getName() + ". Enable debug logging to see the trace stack");
                        logger.debug(e);
                    } finally {
                        Thread.currentThread().setContextClassLoader(thisCl);
                    }
                }
            }

            //
            // this list has to guarantee the order in which elements are added
            //
            List uniqueList = new LinkedList();

            Comparator cmp = new Comparator() {
                public int compare(Object o1, Object o2) {
                    File f1 = ((LogDestination) o1).getFile();
                    File f2 = ((LogDestination) o2).getFile();
                    String name1 = f1 == null ? "" : f1.getAbsolutePath();
                    String name2 = f2 == null ? "" : f2.getAbsolutePath();
                    return name1.compareTo(name2);
                }
            };

            boolean  showAll = ServletRequestUtils.getBooleanParameter(request, "apps", false);

            if (showAll) {
                cmp = new Comparator() {
                    public int compare(Object o1, Object o2) {
                        LogDestination d1 = (LogDestination) o1;
                        LogDestination d2 = (LogDestination) o2;

                        String appName1 = d1.getApplication() != null ? d1.getApplication().getName() : "";
                        String appName2 = d2.getApplication() != null ? d2.getApplication().getName() : "";

                        String logClass1 = d1.getLogClass();
                        String logClass2 = d1.getLogClass();

                        String name1 = appName1 + logClass1 + (d1.getFile() == null ? "" : d1.getFile().getAbsolutePath());
                        String name2 = appName2 + logClass2 + (d2.getFile() == null ? "" : d2.getFile().getAbsolutePath());
                        return name1.compareTo(name2);
                    }
                };
            }

            Collections.sort(allAppenders, cmp);
            for (int i = 0; i < allAppenders.size(); i++) {
                LogDestination dest = (LogDestination) allAppenders.get(i);
                if (Collections.binarySearch(uniqueList, dest, cmp) < 0) {
                    if (showAll || dest.getFile() == null || dest.getFile().exists()) {
                        uniqueList.add(new DisconnectedLogDestination(dest));
                    }
                }
            }

            request.getSession(true).setAttribute("logs", uniqueList);
            return new ModelAndView(getViewName());
        } else {
            return new ModelAndView(errorView);
        }
    }

    private void interrogateClassLoader(ClassLoader cl, Application application, List<DefaultAccessor> appenders) throws Exception {

        Jdk14LoggerAccessor jdk14accessor = Jdk14ManagerAccessor.getRootLogger(cl);
        if (jdk14accessor != null) {
            jdk14accessor.setApplication(application);
            appenders.addAll(jdk14accessor.getHandlers());
        }

        // check for Log4J loggers
        Log4JLoggerAccessor log4JAccessor = Log4JManagerAccessor.getRootLogger(cl);
        if (log4JAccessor != null) {
            log4JAccessor.setApplication(application);
            appenders.addAll(log4JAccessor.getAppenders());
        }
    }

    private void interrogateStdOutFiles(List<DefaultAccessor> appenders) {
        for (Iterator<?> it = stdoutFiles.iterator(); it.hasNext(); ) {
            String fileName = (String) it.next();
            File stdout = new File(System.getProperty("catalina.base"), "logs/" + fileName);
            if (stdout.exists()) {
                FileLogAccessor fla = new FileLogAccessor();
                fla.setFile(stdout);
                appenders.add(fla);
            }
        }

    }
}
