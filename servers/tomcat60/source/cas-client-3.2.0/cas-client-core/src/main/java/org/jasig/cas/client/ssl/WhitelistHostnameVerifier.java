/**
 * Licensed to Jasig under one or more contributor license
 * agreements. See the NOTICE file distributed with this work
 * for additional information regarding copyright ownership.
 * Jasig licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a
 * copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
  $Id: WhitelistHostnameVerifier.java 22086 2010-10-25 03:59:14Z battags $

  Copyright (C) 2008-2009 Virginia Tech.
  All rights reserved.

  SEE LICENSE FOR MORE INFORMATION

  Author:  Middleware
  Email:   middleware@vt.edu
  Version: $Revision: 22086 $
  Updated: $Date: 2010-10-24 23:59:14 -0400 (Sun, 24 Oct 2010) $
*/
package org.jasig.cas.client.ssl;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.SSLSession;

/**
 * Verifies a SSL peer host name based on an explicit whitelist of allowed hosts.
 *
 * @author Middleware
 * @version $Revision: 22086 $
 *
 */
public class WhitelistHostnameVerifier implements HostnameVerifier {
    /** Allowed hosts */
    private String[] allowedHosts;


    /**
     * Creates a new instance using the given array of allowed hosts.
     * 
     * @param allowed Array of allowed hosts.
     */
    public WhitelistHostnameVerifier(final String[] allowed) {
        this.allowedHosts = allowed;
    }


    /**
     * Creates a new instance using the given list of allowed hosts.
     * 
     * @param allowedList Comma-separated list of allowed hosts.
     */
    public WhitelistHostnameVerifier(final String allowedList) {
        this.allowedHosts = allowedList.split(",\\s*");
    }

    /** {@inheritDoc} */
    public boolean verify(final String hostname, final SSLSession session) {

        for (final String allowedHost : this.allowedHosts) {
            if (hostname.equalsIgnoreCase(allowedHost)) {
                return true;
            }
        }
        return false;
    }

}
