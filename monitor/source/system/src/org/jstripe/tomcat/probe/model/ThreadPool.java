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

import java.util.List;
import java.util.ArrayList;

/**
 * POJO representing pool of request processor threads or "connector" in other terms.
 *
 * Author: Vlad Ilyushchenko
 */
public class ThreadPool {

    private String name;
    private int maxThreads;
    private int minSpareThreads;
    private int maxSpareThreads;
    private int currentThreadCount;
    private int currentThreadsBusy;
    private long maxTime;
    private long processingTime;
    private int requestCount;
    private int errorCount;
    private long bytesReceived;
    private long bytesSent;
    private List<RequestProcessor> requestProcessors = new ArrayList<RequestProcessor>();

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getMaxThreads() {
        return maxThreads;
    }

    public void setMaxThreads(int maxThreads) {
        this.maxThreads = maxThreads;
    }

    public int getMinSpareThreads() {
        return minSpareThreads;
    }

    public void setMinSpareThreads(int minSpareThreads) {
        this.minSpareThreads = minSpareThreads;
    }

    public int getMaxSpareThreads() {
        return maxSpareThreads;
    }

    public void setMaxSpareThreads(int maxSpareThreads) {
        this.maxSpareThreads = maxSpareThreads;
    }

    public int getCurrentThreadCount() {
        return currentThreadCount;
    }

    public void setCurrentThreadCount(int currentThreadCount) {
        this.currentThreadCount = currentThreadCount;
    }

    public int getCurrentThreadsBusy() {
        return currentThreadsBusy;
    }

    public void setCurrentThreadsBusy(int currentThreadsBusy) {
        this.currentThreadsBusy = currentThreadsBusy;
    }

    public long getMaxTime() {
        return maxTime;
    }

    public void setMaxTime(long maxTime) {
        this.maxTime = maxTime;
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

    public long getBytesReceived() {
        return bytesReceived;
    }

    public void setBytesReceived(long bytesReceived) {
        this.bytesReceived = bytesReceived;
    }

    public long getBytesSent() {
        return bytesSent;
    }

    public void setBytesSent(long bytesSent) {
        this.bytesSent = bytesSent;
    }

    public int getErrorCount() {
        return errorCount;
    }

    public void setErrorCount(int errorCount) {
        this.errorCount = errorCount;
    }

    public List<RequestProcessor> getRequestProcessors() {
        return requestProcessors;
    }

    public void setRequestProcessors(List<RequestProcessor> requestProcessors) {
        this.requestProcessors = requestProcessors;
    }

    public void addRequestProcessor(RequestProcessor rp) {
        requestProcessors.add(rp);
    }
}
