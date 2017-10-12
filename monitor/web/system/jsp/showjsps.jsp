<%--
 * Licensed under the GPL License. You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://probe.jstripe.com/d/license.shtml
 *
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 --%>

<%@ taglib uri='http://java.sun.com/jsp/jstl/core' prefix='c' %>
<%@ taglib uri='http://java.sun.com/jsp/jstl/fmt' prefix='fmt' %>
<%@ taglib uri="http://www.springframework.org/tags" prefix="spring" %>
<%@ taglib uri="http://displaytag.sf.net" prefix="display" %>
<%@ taglib uri="/WEB-INF/jstripe.tld" prefix="js" %>


<%@ page contentType="text/html;charset=UTF-8" language="java" session="false" %>
<html>
<head><title><spring:message code="probe.jsp.title.jsps" arguments="${param.webapp}"/></title></head>

<script type="text/javascript" language="javascript" src="<c:url value="/system/js/prototype.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/effects.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/func.js"/>"></script>

<c:set var="navTabApps" value="active" scope="request"/>
<c:set var="use_decorator" value="application" scope="request"/>
<c:set var="appTabJSPs" value="active" scope="request"/>

<body>
<c:choose>
    <c:when test="${ empty summary.items}">
        <div class="infoMessage">
            <p>
                <spring:message code="probe.jsp.jsps.notfound"/>
            </p>
        </div>
    </c:when>
    <c:otherwise>
        <form action="<c:url value="/system/probe/app/recompile.htm"><c:param name="webapp" value="${param.webapp}"/></c:url>"
              method="post" name="jspform" id="jspform">

            <ul class="options">
                <li id="toggle"><a href="#" onclick="return inverse(jspform);"><spring:message code="probe.jsp.jsps.opt.toggleall"/></a></li>
                <li id="compile"><a href="#" onclick="jspform.submit();"><spring:message code="probe.jsp.jsps.opt.compile"/></a></li>
                <li id="compileall"><a href="<c:url value="/system/probe/app/jsp.htm"><c:param name="compile" value="true"/><c:param name="webapp" value="${param.webapp}"/></c:url>"><spring:message code="probe.jsp.jsps.opt.compileall"/></a></li>
                <li id="delete_r"><a href="<c:url value="/system/probe/adm/discard.htm"><c:param name="webapp" value="${param.webapp}"/></c:url>"><spring:message code="probe.jsp.jsps.opt.discardscratch"/></a></li>
            </ul>

            <div class="embeddedBlockContainer">
                <display:table name="summary.items" id="item" class="genericTbl" cellspacing="0" requestURI="" defaultsort="1"
                               defaultorder="descending">
                    <display:column titleKey="probe.jsp.jsps.col.name" sort="true" class="leftmost" sortProperty="name" width="auto">
                        <input type="checkbox" name="${item.name}"/>&nbsp;
                        <a href="<c:url value="/system/probe/app/viewsource.htm?webapp=${param.webapp}&source=${item.name}"/>">${item.name}</a>
                    </display:column>
                    <display:column titleKey="probe.jsp.jsps.col.size" sort="true" sortProperty="size" width="30px">
                        <js:volume value="${item.size}"/>
                    </display:column>
                    <display:column titleKey="probe.jsp.jsps.col.lastmodified" sort="true" sortProperty="lastModified" width="140px">
                        ${item.timestamp}
                    </display:column>
                    <display:column titleKey="probe.jsp.jsps.col.status" sort="true" sortProperty="state" width="60px">
                        <c:choose>
                            <c:when test="${item.state == 1}"><spring:message code="probe.jsp.jsps.status.outdated"/></c:when>
                            <c:when test="${item.state == 2}"><spring:message code="probe.jsp.jsps.status.compiled"/></c:when>
                            <c:otherwise><span class="fail"><spring:message code="probe.jsp.jsps.status.failed"/></span></c:otherwise>
                        </c:choose>
                    </display:column>
                    <display:column titleKey="probe.jsp.jsps.col.message" sort="true" width="auto">
                        <c:out value="${item.exception.message}" escapeXml="false"/>&nbsp;
                    </display:column>
                </display:table>
            </div>
        </form>
    </c:otherwise>
</c:choose>
</body>
</html>