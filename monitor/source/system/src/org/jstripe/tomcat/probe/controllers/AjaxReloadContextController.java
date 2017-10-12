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
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Reloads application context.
 * <p/>
 * Author: Vlad Ilyushchenko
 */
public class AjaxReloadContextController extends ContextHandlerController {

    protected ModelAndView handleContext(String contextName, Context context,
                                             HttpServletRequest request, HttpServletResponse response) throws Exception {
        if (!request.getContextPath().equals(contextName) && context != null) {
            try {
                logger.info(request.getRemoteAddr() + " requested RELOAD of "+contextName);
                context.reload();
            } catch (Throwable e) {
                logger.error(e);
            }
        }
        return new ModelAndView(getViewName(), "available",
                Boolean.valueOf(context == null ? false : context.getAvailable()));
    }

}
