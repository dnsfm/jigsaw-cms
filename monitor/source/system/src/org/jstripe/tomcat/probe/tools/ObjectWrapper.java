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

package org.jstripe.tomcat.probe.tools;

import java.util.*;

class ObjectWrapper {
    private Object o;

    public ObjectWrapper(Object o) {
        this.o = o;
    }

    public boolean equals(Object o1) {
        if (o == null && o1 == null) {
            return true;
        } else if (o == null) {
            return false;
        } else {
            ObjectWrapper ow = (ObjectWrapper) o1;
            // I know, this condition may seem strange, but if "equals" is left out 
            // sizeOf() may run into an infinite loop on some objects
            return ow.o == o || o.equals(ow.o);
        }
    }

    public static void main(String[] args) {
        Map<String, Object> session = new HashMap<String, Object>();
        session.put("test1", "test message");
        
        List<String> bikes = new ArrayList<String>();
        bikes.add("specialized");
        bikes.add("kona");
        bikes.add("GT");
        session.put("bikes", bikes);

        Map<String, List<String>> bikeParts = new TreeMap<String, List<String>>();
        bikeParts.put("bike1", bikes);
        session.put("parts", bikeParts);

        System.out.println(Instruments.sizeOf(session));

    }
}
