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

import org.apache.catalina.Context;
import org.jstripe.tomcat.probe.tools.ApplicationUtils;
import org.jstripe.tomcat.probe.model.ServletInfo;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;
import java.util.Iterator;
import java.util.Collections;

/**
 * Retrieves a list of web application servlets
 * <p/>
 * Author: Andy Shapoval
 */
public class ListAppServletsController extends ContextHandlerController {
    @SuppressWarnings("unchecked")
	protected ModelAndView handleContext(String contextName, Context context,
                                         HttpServletRequest request, HttpServletResponse response) throws Exception {
        List appServlets = ApplicationUtils.getApplicationServlets(context);
        for (Iterator i = appServlets.iterator(); i.hasNext();) {
            ServletInfo svlt = (ServletInfo) i.next();
            Collections.sort(svlt.getMappings());
        }
        return new ModelAndView(getViewName(), "appServlets", appServlets);
    }
}
