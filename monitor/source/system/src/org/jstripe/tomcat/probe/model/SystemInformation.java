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
package org.jstripe.tomcat.probe.model;

import org.apache.catalina.util.ServerInfo;

import java.io.File;
import java.io.Serializable;
import java.util.Date;
import java.util.Set;
import java.util.Map;

/**
 * POJO representing system information for "system infromation" tab.
 *
 * Author: Vlad Ilyushchenko
 */
public class SystemInformation implements Serializable {

	private static final long serialVersionUID = -2338142236975497502L;
	
	private String appBase;
    private String configBase;
    
    @SuppressWarnings("unchecked")
	private Map systemProperties;

    public long getMaxMemory() {
        return Runtime.getRuntime().maxMemory();
    }

    public long getFreeMemory() {
        return Runtime.getRuntime().freeMemory();
    }

    public long getTotalMemory() {
        return Runtime.getRuntime().totalMemory();
    }

    public int getCpuCount() {
        return Runtime.getRuntime().availableProcessors();
    }

    public Date getDate() {
        return new Date();
    }

    public String getServerInfo() {
        return ServerInfo.getServerInfo();
    }

    public String getWorkingDir() {
        return new File("").getAbsolutePath();
    }

    public String getAppBase() {
        return appBase;
    }

    public void setAppBase(String appBase) {
        this.appBase = appBase;
    }

    public String getConfigBase() {
        return configBase;
    }

    public void setConfigBase(String configBase) {
        this.configBase = configBase;
    }

    @SuppressWarnings("unchecked")
	public Map getSystemProperties() {
        return systemProperties;
    }

    @SuppressWarnings("unchecked")
	public void setSystemProperties(Map systemProperties) {
        this.systemProperties = systemProperties;
    }

    @SuppressWarnings("unchecked")
	public Set getSystemPropertySet() {
        return systemProperties.entrySet();
    }
}
