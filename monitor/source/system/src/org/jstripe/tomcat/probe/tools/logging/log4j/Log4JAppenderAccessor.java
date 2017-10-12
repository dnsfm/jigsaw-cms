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

package org.jstripe.tomcat.probe.tools.logging.log4j;

import org.jstripe.tomcat.probe.tools.logging.DefaultAccessor;
import org.jstripe.tomcat.probe.tools.logging.LogDestination;

import java.io.File;

public class Log4JAppenderAccessor extends DefaultAccessor implements LogDestination {
    private Log4JLoggerAccessor loggerAccessor;

    public Log4JLoggerAccessor getLoggerAccessor() {
        return loggerAccessor;
    }

    public void setLoggerAccessor(Log4JLoggerAccessor loggerAccessor) {
        this.loggerAccessor = loggerAccessor;
    }

    public String getType() {
        return getTarget().getClass().getName();
    }

    public String getName() {
        return (String) getProperty(getTarget(), "name", null);
    }

    public String getConversionPattern() {
        Object layout = getProperty(getTarget(), "layout", null);
        if (layout != null && "org.apache.log4j.PatternLayout".equals(layout.getClass().getName())) {
            return (String) getProperty(layout, "conversionPattern", null);
        } else {
            return null;
        }
    }

    public File getFile() {
        String fileName = (String) getProperty(getTarget(), "file", null);
        return fileName != null ? new File(fileName) : getStdoutFile();
    }
    
}
