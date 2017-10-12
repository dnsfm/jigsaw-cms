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

package org.jstripe.tomcat.probe.controllers;

import org.springframework.web.servlet.ModelAndView;
import org.apache.catalina.Context;
import org.apache.catalina.util.ServerInfo;
import org.jstripe.tomcat.probe.tools.ApplicationUtils;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * Retrieves a list of web application filter mappings
 * <p/>
 * Author: Andy Shapoval
 */
public class ListAppFilterMapsController extends ContextHandlerController {
	
    @SuppressWarnings("unchecked")
	protected ModelAndView handleContext(String contextName, Context context,
                                         HttpServletRequest request, HttpServletResponse response) throws Exception {
        // Tomcat's class representing filter mapping was changed starting with Tomcat 6,
        // therefore ApplicationUtils.getApplicationFilterMaps() throws an exception on Tomcat 6
        // TODO Add support of Tomcat 6
        String serverVersion = ServerInfo.getServerInfo();
        if (serverVersion.startsWith("Apache Tomcat/5.")) {
            List filterMaps = ApplicationUtils.getApplicationFilterMaps(context);
            return new ModelAndView(getViewName(), "filterMaps", filterMaps);
        } else {
            return new ModelAndView("errors/serverversion", "serverVersion", serverVersion);
        }
    }
}
