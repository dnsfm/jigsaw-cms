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

package org.jstripe.tomcat.probe.tools.logging.catalina;

import org.jstripe.tomcat.probe.tools.logging.DefaultAccessor;
import org.jstripe.tomcat.probe.tools.logging.LogDestination;
import org.jstripe.tomcat.probe.tools.Instruments;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;

public class CatalinaLoggerAccessor extends DefaultAccessor implements LogDestination {

    public String getName() {
        return null;
    }

    public String getType() {
        return getTarget().getClass().getName();
    }

    public String getConversionPattern() {
        return null;
    }

    public File getFile() {
        String dir = (String) invokeMethod(getTarget(), "getDirectory", null, null);
        String prefix = (String) invokeMethod(getTarget(), "getPrefix", null, null);
        String suffix = (String) invokeMethod(getTarget(), "getSuffix", null, null);
        boolean timestamp = ((Boolean)Instruments.getField(getTarget(), "timestamp")).booleanValue();
        String date = timestamp ? new SimpleDateFormat("yyyy-MM-dd").format(new Date()) : "";

        File log = date != null && dir != null && prefix != null && suffix != null ? new File(dir, prefix + date + suffix) : null;
        if (log != null && !log.isAbsolute()) {
            return new File(new File(System.getProperty("catalina.base")), log.getPath());
        } else {
            return log;
        }
    }
}
