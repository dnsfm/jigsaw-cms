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

import org.springframework.web.servlet.mvc.AbstractController;
import org.springframework.web.servlet.ModelAndView;
import org.jstripe.tomcat.probe.Utils;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.InputStream;
import java.util.List;
import java.util.Iterator;

public class HelpController extends AbstractController {

    private String contentBase;

    public String getContentBase() {
        return contentBase;
    }

    public void setContentBase(String contentBase) {
        this.contentBase = contentBase;
    }

    protected ModelAndView handleRequestInternal(HttpServletRequest request, HttpServletResponse response) throws Exception {
        boolean responseSent = false;
        String requestFileName = new File(request.getRequestURI()).getName();
        if (requestFileName != null) {
            String htmlName = requestFileName.substring(0, requestFileName.indexOf("."));
            List<String> names = Utils.getNamesForLocale(htmlName, request.getLocale());

            names.add(htmlName);

            for (Iterator<String> it = names.iterator(); it.hasNext();) {
                String name = (String) it.next();
                InputStream is = getServletContext().getResourceAsStream(new File(getContentBase(), name + ".html").getPath().replace("\\", "/"));
                if (is != null) {
                    try {
                        response.setCharacterEncoding("UTF-8");
                        response.getWriter().print(Utils.readStream(is, "UTF-8"));
                        responseSent = true;
                        break;
                    } finally {
                        is.close();
                    }
                }
            }

            if (!responseSent) {
                logger.info("Could not find help file for \""+htmlName+"\", locale: "+request.getLocale());
                response.sendError(404);
            }
        }
        return null;
    }
}
