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
<%@ page contentType="text/html;charset=UTF-8" language="java" session="false" %>
<%@ taglib uri='http://java.sun.com/jsp/jstl/core' prefix='c' %>
<%@ taglib uri="http://www.springframework.org/tags" prefix="spring" %>
<%@ taglib uri="http://displaytag.sf.net" prefix="display" %>
<%@ taglib uri="/WEB-INF/jstripe.tld" prefix="js" %>

<%--
    Displays a list of web application servlets

    Author: Andy Shapoval, Vlad Ilyushchenko
--%>

<html>

<head>
    <title>
        <spring:message code="probe.jsp.title.app.servlets" arguments="${param.webapp}"/>
    </title>
</head>

<%--
    Make Tab #1 visually "active".
--%>
<c:set var="navTabApps" value="active" scope="request"/>
<c:set var="use_decorator" value="application" scope="request"/>
<c:set var="appTabServlets" value="active" scope="request"/>

<body>

<link rel="stylesheet" href="${pageContext.request.contextPath}<spring:theme code="servlets.css"/>" type="text/css"/>

<ul class="options">
    <li id="viewAppServletMaps">
        <a href="<c:url value="/system/probe/appservletmaps.htm">
                    <c:param name="webapp" value="${param.webapp}"/>
                </c:url>"><spring:message code="probe.jsp.app.servlets.opt.maps"/></a>
    </li>
</ul>

<div class="embeddedBlockContainer">
    <c:choose>
        <c:when test="${! empty appServlets}">

            <h3><spring:message code="probe.jsp.app.servlets.h3.defs"/></h3>

            <display:table htmlId="servletTbl" name="appServlets" id="svlt"
                           class="genericTbl" cellspacing="0" cellpadding="0"
                           requestURI="" defaultsort="5" defaultorder="descending">
                <display:column sortProperty="servletName" sortable="true"
                                titleKey="probe.jsp.app.servlets.col.servletName" class="leftmost">
                    <div class="servletName"><js:out value="${svlt.servletName}" maxLength="40"/>
                        <c:if test="${! empty svlt.mappings}">
                            <span>
                                (<js:out maxLength="40"><c:forEach var="mp" items="${svlt.mappings}" varStatus="mpSt">${mp}<c:if test="${! mpSt.last}">,</c:if></c:forEach></js:out>)
                            </span>
                        </c:if>
                    </div>
                    <div class="servletClass"><js:out value="${svlt.servletClass}" maxLength="50"/></div>
                </display:column>
                <display:column sortProperty="available" sortable="true"
                                titleKey="probe.jsp.app.servlets.col.available">
                    <c:choose>
                        <c:when test="${svlt.available}">
                            <span class="okValue"><spring:message code="probe.jsp.generic.yes"/></span>
                        </c:when>
                        <c:otherwise>
                            <span class="errorValue"><spring:message code="probe.jsp.generic.no"/></span>
                        </c:otherwise>
                    </c:choose>
                </display:column>
                <display:column sortable="true" sortProperty="loadOnStartup"
                                titleKey="probe.jsp.app.servlets.col.loadOnStartup">
                    <c:choose>
                        <c:when test="${svlt.loadOnStartup == -1}">
                            <span class="errorValue"><spring:message code="probe.jsp.generic.no"/></span>
                        </c:when>
                        <c:otherwise>
                            ${svlt.loadOnStartup}
                        </c:otherwise>
                    </c:choose>

                </display:column>
                <display:column sortable="true" sortProperty="loadTime"
                                titleKey="probe.jsp.app.servlets.col.loadTime">
                    ${svlt.loadTime}
                </display:column>
                <display:column property="requestCount" sortable="true"
                                titleKey="probe.jsp.app.servlets.col.requestCount"/>
                <display:column sortable="true" sortProperty="processingTime"
                                titleKey="probe.jsp.app.servlets.col.processingTime">
                    <js:duration value="${svlt.processingTime}"/>
                </display:column>
                <display:column property="errorCount" sortable="true"
                                titleKey="probe.jsp.app.servlets.col.errorCount"/>
                <display:column sortable="true" sortProperty="minTime"
                                titleKey="probe.jsp.app.servlets.col.minTime">
                    ${svlt.minTime}
                </display:column>
                <display:column sortable="true" sortProperty="maxTime"
                                titleKey="probe.jsp.app.servlets.col.maxTime">
                    ${svlt.maxTime}
                </display:column>
                <display:column sortProperty="singleThreaded" sortable="true"
                                titleKey="probe.jsp.app.servlets.col.multiThreaded">
                    <c:choose>
                        <c:when test="${!svlt.singleThreaded}">
                            <span class="okValue"><spring:message code="probe.jsp.generic.yes"/></span>
                        </c:when>
                        <c:otherwise>
                            <span class="errorValue"><spring:message code="probe.jsp.generic.no"/></span>
                        </c:otherwise>
                    </c:choose>
                </display:column>
            </display:table>
        </c:when>
        <c:otherwise>
            <div class="infoMessage">
                <p>
                    <spring:message code="probe.jsp.app.servlets.empty"/>
                </p>
            </div>
        </c:otherwise>
    </c:choose>
</div>
</body>
</html>