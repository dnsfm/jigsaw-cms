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
import org.jstripe.tomcat.probe.Utils;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;

/**
 * Downloads a deployment descriptor (web.xml) or a context descriptor (context.xml) of a web application
 * <p/>
 * Author: Andy Shapoval
 */
public class DownloadXMLConfController extends ContextHandlerController {
    public static final String TARGET_WEB_XML = "web.xml";
    public static final String TARGET_CONTEXT_XML = "context.xml";

    /**
     * Type of a configuration file to be downloaded
     */
    private String downloadTarget;

    public String getDownloadTarget() {
        return downloadTarget;
    }

    public void setDownloadTarget(String downloadTarget) {
        this.downloadTarget = downloadTarget;
    }

    protected ModelAndView handleContext(String contextName, Context context, HttpServletRequest request,
                                         HttpServletResponse response) throws Exception {
        if (downloadTarget == null) {
            throw new RuntimeException("Download target is not set for " + getClass().getName());
        }

        String xmlPath;

        if (TARGET_WEB_XML.equals(downloadTarget)) {
            ServletContext sctx = context.getServletContext();
            xmlPath = sctx.getRealPath("/WEB-INF/web.xml");
        } else if (TARGET_CONTEXT_XML.equals(downloadTarget)) {
            xmlPath = context.getConfigFile();
        } else {
            throw new RuntimeException("Unknown download target " + getDownloadTarget());
        }

        if (xmlPath != null) {
            File xmlFile = new File(xmlPath);
            if (xmlFile.exists()) {
                Utils.sendFile(request, response, xmlFile);
            } else {
                logger.debug("File " + xmlPath + " of " + contextName + " application does not exists.");
            }
        } else {
            logger.debug("Cannot determine path to " + getDownloadTarget() + " file of "  + contextName + " application.");
        }

        return null;
    }
}
