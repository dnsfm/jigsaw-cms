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

import org.jstripe.tomcat.probe.Utils;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.ParameterizableViewController;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;

public class DecoratorController extends ParameterizableViewController {

    private String messagesBasename;

    public String getMessagesBasename() {
        return messagesBasename;
    }

    public void setMessagesBasename(String messagesBasename) {
        this.messagesBasename = messagesBasename;
    }

    @SuppressWarnings("unchecked")
	protected ModelAndView handleRequestInternal(HttpServletRequest request, HttpServletResponse response) throws Exception {
        try {
            request.setAttribute("hostname", InetAddress.getLocalHost().getHostName());
        } catch (UnknownHostException e) {
            request.setAttribute("hostname", "unknown");
        }

        Object uptimeStart = getServletContext().getAttribute("UPTIME_START");
        if (uptimeStart != null && uptimeStart instanceof Long) {
            long l = ((Long)uptimeStart).longValue();
            long uptime = System.currentTimeMillis() - l;
            long uptime_days = uptime / (1000 * 60 * 60 * 24);

            uptime = uptime % (1000 * 60 * 60 * 24);
            long uptime_hours = uptime / (1000 * 60 * 60);

            uptime = uptime % (1000 * 60 * 60);
            long uptime_mins = uptime / (1000 * 60);

            request.setAttribute("uptime_days", new Long(uptime_days));
            request.setAttribute("uptime_hours", new Long(uptime_hours));
            request.setAttribute("uptime_mins", new Long(uptime_mins));
        }

        //
        // Work out the language of the interface by matching resource files that we have
        // to the request locale.
        //
        List fileNames = getMessageFileNamesForLocale(request.getLocale());
        String lang = "en";
        for (Iterator it = fileNames.iterator(); it.hasNext(); ) {
            String f = (String) it.next();
            if (getServletContext().getResource(f+".properties") != null) {
                lang = f.substring(messagesBasename.length() + 1);
                break;
            }
        }

        request.setAttribute("lang", lang);

        return super.handleRequestInternal(request, response);
    }

    @SuppressWarnings("unchecked")
	private List getMessageFileNamesForLocale(Locale locale) {
        return Utils.getNamesForLocale(messagesBasename, locale);
    }
}
