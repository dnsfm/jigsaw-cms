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

package org.jstripe.tomcat.probe.model;

import java.util.List;
import java.util.ArrayList;

/**
 * A model class representing a servlet
 * <p/>
 * Author: Andy Shapoval
 */
public class ServletInfo {
    private String servletName;
    private String servletClass;
    private String jspFile;
    private boolean available;
    private int loadOnStartup;
    private String runAs;
    private int errorCount;
    private long loadTime;
    private long maxTime;
    private long minTime;
    private long processingTime;
    private int requestCount;
    private boolean singleThreaded;
    private int allocationCount;
    private int maxInstances;
    private List<Object> mappings = new ArrayList<Object>();

    public String getServletName() {
        return servletName;
    }

    public void setServletName(String servletName) {
        this.servletName = servletName;
    }

    public String getServletClass() {
        return servletClass;
    }

    public void setServletClass(String servletClass) {
        this.servletClass = servletClass;
    }

    public String getJspFile() {
        return jspFile;
    }

    public void setJspFile(String jspFile) {
        this.jspFile = jspFile;
    }

    public boolean isAvailable() {
        return available;
    }

    public void setAvailable(boolean available) {
        this.available = available;
    }

    public int getLoadOnStartup() {
        return loadOnStartup;
    }

    public void setLoadOnStartup(int loadOnStartup) {
        this.loadOnStartup = loadOnStartup;
    }

    public String getRunAs() {
        return runAs;
    }

    public void setRunAs(String runAs) {
        this.runAs = runAs;
    }

    public int getErrorCount() {
        return errorCount;
    }

    public void setErrorCount(int errorCount) {
        this.errorCount = errorCount;
    }

    public long getLoadTime() {
        return loadTime;
    }

    public void setLoadTime(long loadTime) {
        this.loadTime = loadTime;
    }

    public long getMaxTime() {
        return maxTime;
    }

    public void setMaxTime(long maxTime) {
        this.maxTime = maxTime;
    }

    public long getMinTime() {
        return minTime;
    }

    public void setMinTime(long minTime) {
        this.minTime = minTime;
    }

    public long getProcessingTime() {
        return processingTime;
    }

    public void setProcessingTime(long processingTime) {
        this.processingTime = processingTime;
    }

    public int getRequestCount() {
        return requestCount;
    }

    public void setRequestCount(int requestCount) {
        this.requestCount = requestCount;
    }

    public boolean isSingleThreaded() {
        return singleThreaded;
    }

    public void setSingleThreaded(boolean singleThreaded) {
        this.singleThreaded = singleThreaded;
    }

    public int getAllocationCount() {
        return allocationCount;
    }

    public void setAllocationCount(int allocationCount) {
        this.allocationCount = allocationCount;
    }

    public int getMaxInstances() {
        return maxInstances;
    }

    public void setMaxInstances(int maxInstances) {
        this.maxInstances = maxInstances;
    }

    @SuppressWarnings("unchecked")
	public List getMappings() {
        return mappings;
    }

    public void setMappings(List<Object> mappings) {
        this.mappings = mappings;
    }
}
