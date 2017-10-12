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

import org.jstripe.tomcat.probe.tools.logging.LogDestination;
import org.springframework.web.bind.ServletRequestUtils;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.ParameterizableViewController;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.util.List;

@SuppressWarnings("deprecation")
public abstract class LogHandlerController extends ParameterizableViewController {
    protected ModelAndView handleRequestInternal(HttpServletRequest request, HttpServletResponse response) throws Exception {

        boolean logFound = false;

        ModelAndView modelAndView = null;

        if (request.getSession() != null) {
            List<?> logDestinations = (List<?>) request.getSession().getAttribute("logs");
            if (logDestinations != null) {
                int logIndex = ServletRequestUtils.getIntParameter(request, "id", -1);
                if (logIndex != -1 && logIndex >= 0 && logIndex <= logDestinations.size()) {
                    LogDestination dest = (LogDestination) logDestinations.get(logIndex - 1);
                    if (dest.getFile() != null && dest.getFile().exists()) {
                        modelAndView = handleLogFile(request, response, dest.getFile());
                        logFound = true;
                    } else {
                        logger.error(dest.getFile() + ": file not found");
                    }
                } else {
                    logger.error("List index " + logIndex + " is either missing or invalid");
                }
            } else {
                logger.error("There is no \"logs\" attribute in this session");
            }

        }
        if (!logFound) response.sendError(404);
        return modelAndView;
    }

    protected abstract ModelAndView handleLogFile(HttpServletRequest request, HttpServletResponse response, File file)
            throws Exception;
}
