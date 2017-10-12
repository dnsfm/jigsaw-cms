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

import org.apache.commons.beanutils.MethodUtils;

import java.lang.reflect.Method;

public class Log4JManagerAccessor {

    @SuppressWarnings("unchecked")
	public static Log4JLoggerAccessor getRootLogger(ClassLoader cl) {
        try {
            Class clazz = cl.loadClass("org.apache.log4j.LogManager");
            Method m = MethodUtils.getAccessibleMethod(clazz, "getRootLogger", new Class[]{});

            Log4JLoggerAccessor accessor = new Log4JLoggerAccessor();
            accessor.setTarget(m.invoke((Object)null, (Object)null));
            return accessor;

        } catch (Exception e) {
            return null;
        }
    }
}
