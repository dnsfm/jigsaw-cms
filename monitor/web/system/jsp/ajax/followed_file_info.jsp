<%--
  ~ Licensed under the GPL License. You may not use this file except in compliance with the License.
  ~ You may obtain a copy of the License at
  ~
  ~   http://probe.jstripe.com/d/license.shtml
  ~
  ~  THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
  ~  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  ~  WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
  --%>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri='http://java.sun.com/jsp/jstl/core' prefix='c' %>
<%@ taglib uri="http://www.springframework.org/tags" prefix="spring" %>
<%@ taglib uri="/WEB-INF/jstripe.tld" prefix="js" %>

<p>
    <spring:message code="probe.jsp.followed_file_info.fileName"/>&nbsp;<span class="value">${followed_file.fileName}</span>
    <spring:message code="probe.jsp.followed_file_info.size"/>&nbsp;<span class="value"><js:volume value="${followed_file.size}"/></span>
    <spring:message code="probe.jsp.followed_file_info.lastModified"/>&nbsp;<span class="value">${followed_file.lastModified}</span>
</p>
