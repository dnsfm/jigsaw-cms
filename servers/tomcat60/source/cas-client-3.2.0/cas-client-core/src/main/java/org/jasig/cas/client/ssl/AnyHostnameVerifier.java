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
  @author Marvin Addison
  @version $Revision: 22086 $ $Date: 2010-10-24 23:59:14 -0400 (Sun, 24 Oct 2010) $
  @since 3.1.10
*/
package org.jasig.cas.client.ssl;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.SSLSession;

/**
 * Hostname verifier that performs no host name verification for an SSL peer
 * such that all hosts are allowed.
 *
 * @author Middleware
 * @version $Revision: 22086 $
 *
 */
public class AnyHostnameVerifier implements HostnameVerifier {

    /** {@inheritDoc} */
    public boolean verify(final String hostname, final SSLSession session) {
        return true;
    }

}