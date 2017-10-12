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

import org.jstripe.tomcat.probe.Utils;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;

public class DownloadLogController extends LogHandlerController {

    protected ModelAndView handleLogFile(HttpServletRequest request, HttpServletResponse response, File file) throws Exception {
        logger.info("Sending "+file + " to "+request.getRemoteAddr() + "("+request.getRemoteUser()+")");
        Utils.sendFile(request, response, file);
        return null;
    }
}
