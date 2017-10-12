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
package org.jstripe.tomcat.probe.controllers;

import org.apache.catalina.Context;
import org.jstripe.tomcat.probe.model.Application;
import org.jstripe.tomcat.probe.tools.ApplicationUtils;
import org.springframework.web.bind.ServletRequestUtils;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.ArrayList;
import java.util.List;

/**
 * Creates the list of web application installed in the same "host" as the Probe.
 *
 * Author: Vlad Ilyushchenko, Andy Shapoval
 */
@SuppressWarnings("deprecation")
public class ListWebappsController extends TomcatContainerController {

    protected ModelAndView handleRequestInternal(HttpServletRequest request, HttpServletResponse response) throws Exception {

        String privelegedRole = getServletContext().getInitParameter("attribute.value.role");
        boolean calcSize = ServletRequestUtils.getBooleanParameter(request, "size", false) && request.isUserInRole(privelegedRole);

        List<?> apps = getContainerWrapper().getTomcatContainer().findContexts();
        List<Application> applications = new ArrayList<Application>(apps.size());
        boolean showResources = getContainerWrapper().getResourceResolver().supportsPrivateResources();
        for (int i = 0; i < apps.size(); i++) {
            Context appContext = (Context) apps.get(i);
            //
            // check if this is not the ROOT webapp
            //
            if (appContext.getName() != null) {
                applications.add(ApplicationUtils.getApplication(appContext, getContainerWrapper().getResourceResolver(), calcSize));
            }
        }
        if (! applications.isEmpty() && ! showResources) {
            request.setAttribute("no_resources", Boolean.TRUE);
        }
        return new ModelAndView(getViewName(), "apps", applications);
    }
}
