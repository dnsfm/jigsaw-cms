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
import org.springframework.web.servlet.mvc.ParameterizableViewController;
import org.jstripe.tomcat.probe.beans.JvmMemoryInfoAccessorBean;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MemoryStatsController extends ParameterizableViewController {
    private JvmMemoryInfoAccessorBean jvmMemoryInfoAccessorBean;

    public JvmMemoryInfoAccessorBean getJvmMemoryInfoAccessorBean() {
        return jvmMemoryInfoAccessorBean;
    }

    public void setJvmMemoryInfoAccessorBean(JvmMemoryInfoAccessorBean jvmMemoryInfoAccessorBean) {
        this.jvmMemoryInfoAccessorBean = jvmMemoryInfoAccessorBean;
    }

    protected ModelAndView handleRequestInternal(HttpServletRequest request, HttpServletResponse response) throws Exception {
        return new ModelAndView(getViewName(), "pools", jvmMemoryInfoAccessorBean.getPools());
    }
}
