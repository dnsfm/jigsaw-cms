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

package org.jstripe.tomcat.probe.tools.logging.jdk;

import org.apache.commons.beanutils.MethodUtils;

public class Jdk14ManagerAccessor {
    @SuppressWarnings("unchecked")
	public static Jdk14LoggerAccessor getRootLogger(ClassLoader cl) {
        try {
            Class clazz = cl.loadClass("java.util.logging.LogManager");
            Object manager = MethodUtils.getAccessibleMethod(clazz, "getLogManager", new Class[]{}).invoke((Object)null, (Object)null);
            Jdk14LoggerAccessor accessor = new Jdk14LoggerAccessor();
            accessor.setTarget(manager);
            return accessor;
        } catch (Exception e) {
            return null;
        }
    }
}
