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

package org.jstripe.tomcat.probe.controllers.wrapper;

import org.springframework.web.servlet.mvc.ParameterizableViewController;
import org.springframework.web.servlet.ModelAndView;
import org.tanukisoftware.wrapper.WrapperManager;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class StopJvmController extends ParameterizableViewController {
    private int stopExitCode = 1;

    public int getStopExitCode() {
        return stopExitCode;
    }

    public void setStopExitCode(int stopExitCode) {
        this.stopExitCode = stopExitCode;
    }

    protected ModelAndView handleRequestInternal(HttpServletRequest request, HttpServletResponse response) throws Exception {
        boolean done = false;
        try {
            Class.forName("org.tanukisoftware.wrapper.WrapperManager");
            logger.info("JVM is STOPPED by "+request.getRemoteAddr());
            WrapperManager.stop(stopExitCode);
            done = true;
        } catch (ClassNotFoundException e) {
            logger.info("WrapperManager not found. Do you have wrapper.jar in the classpath?");
        }
        return new ModelAndView(getViewName(), "done", Boolean.valueOf(done));
    }
}
