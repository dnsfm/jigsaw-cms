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
<%@ page contentType="text/html;charset=UTF-8" language="java" session="false" %>
<%@ taglib uri='http://java.sun.com/jsp/jstl/core' prefix='c' %>
<%@ taglib uri="http://www.opensymphony.com/sitemesh/decorator" prefix="decorator" %>
<%@ taglib uri="http://www.opensymphony.com/sitemesh/page" prefix="page" %>
<%@ taglib uri="http://www.springframework.org/tags" prefix="spring" %>

<%--
    Main site decorator. Face of the Probe.

    Author: Vlad Ilyushchenko
--%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" lang="${lang}" xml:lang="${lang}">
<head>
    <title>Probe - <decorator:title default="Tomcat management"/></title>
    <LINK rel="shortcut icon" href="<c:url value="/system/css/favicon.gif"/>">
    <link rel="stylesheet" href="${pageContext.request.contextPath}<spring:theme code="tables.css"/>" type="text/css"/>
    <link rel="stylesheet" href="${pageContext.request.contextPath}<spring:theme code="main.css"/>" type="text/css"/>
    <link rel="stylesheet" href="${pageContext.request.contextPath}<spring:theme code="mainnav.css"/>" type="text/css"/>
    <link rel="stylesheet" href="${pageContext.request.contextPath}<spring:theme code="messages.css"/>" type="text/css"/>
    <link rel="stylesheet" href="<c:url value="/system/css/classic/tooltip.css"/>" type="text/css"/>
    <decorator:head/>
</head>

<body>

<div id="caption">
    <ul id="top">
        <li id="logo"><a href="<c:url value="/system/probe/index.htm"/>"><img src="<c:url value="/system/css/the-probe-logo.gif"/>"
                                                                 alt="LambdaProbe Logo"/></a></li>
        <li id="runtime">
            <spring:message code="probe.jsp.version" arguments="@VERSION@,<b>${hostname}</b>"/>,
            <span class="uptime"><spring:message code="probe.jsp.uptime"
                                                 arguments="${uptime_days},${uptime_hours},${uptime_mins}"/></span>
        <li id="title"><decorator:title default="Probe"/></li>
    </ul>
</div>

<div id="navcontainer">
    <ul id="tabnav">
        <li><a class="${navTabApps}" href="<c:url value="/system/probe/index.htm?size=${param.size}"/>"><spring:message
                code="probe.jsp.menu.applications"/></a></li>
        <li><a class="${navTabDatasources}" href="<c:url value="/system/probe/datasources.htm"/>"><spring:message
                code="probe.jsp.menu.datasources"/></a></li>
        <li><a class="<c:out value="${navTabDeploy}"/>" href="<c:url value="/system/probe/deploy.htm"/>"><spring:message
                code="probe.jsp.menu.deployment"/></a></li>
        <li><a class="<c:out value="${navTabLogs}"/>" href="<c:url value="/system/probe/logs/index.htm"/>"><spring:message
                code="probe.jsp.menu.logs"/></a></li>
        <li><a class="<c:out value="${navTabThreads}"/>" href="<c:url value="/system/probe/threads.htm"/>"><spring:message
                code="probe.jsp.menu.threads"/></a></li>
        <li><a class="<c:out value="${navTabCluster}"/>" href="<c:url value="/system/probe/cluster.htm"/>"><spring:message
                code="probe.jsp.menu.cluster"/></a></li>
        <li><a class="<c:out value="${navTabSystem}"/>" href="<c:url value="/system/probe/sysinfo.htm"/>"><spring:message
                code="probe.jsp.menu.sysinfo"/></a></li>
        <li><a class="<c:out value="${navTabStatus}"/>" href="<c:url value="/system/probe/status.htm"/>"><spring:message
                code="probe.jsp.menu.status"/></a></li>
        <li><a class="<c:out value="${navTabCharts}"/>" href="<c:url value="/system/probe/charts.htm"/>"><spring:message
                code="probe.jsp.menu.charts"/></a></li>
        <li><a class="<c:out value="${navTabQuickCheck}"/>" href="<c:url value="/system/probe/adm/quickcheck.htm"/>">
            <spring:message code="probe.jsp.menu.quickcheck"/></a></li>
    </ul>
</div>

<c:choose>
    <c:when test="${! empty use_decorator}">
        <page:applyDecorator name="${use_decorator}">
            <decorator:body/>
        </page:applyDecorator>
    </c:when>
    <c:otherwise>
        <div id="mainBody">
            <decorator:body/>
        </div>
    </c:otherwise>
</c:choose>

<div id="footer">
    <ul>
        <li><a href="<c:url value="/system/probe/index.htm"/>"><spring:message code="probe.jsp.menu.applications"/></a></li>
        <li><a href="<c:url value="/system/probe/datasources.htm"/>"><spring:message code="probe.jsp.menu.datasources"/></a></li>
        <li><a href="<c:url value="/system/probe/deploy.htm"/>"><spring:message code="probe.jsp.menu.deployment"/></a></li>
        <li><a href="<c:url value="/system/probe/logs/index.htm"/>"><spring:message code="probe.jsp.menu.logs"/></a></li>
        <li><a href="<c:url value="/system/probe/threads.htm"/>"><spring:message code="probe.jsp.menu.threads"/></a></li>
        <li><a href="<c:url value="/system/probe/cluster.htm"/>"><spring:message code="probe.jsp.menu.cluster"/></a></li>
        <li><a href="<c:url value="/system/probe/sysinfo.htm"/>"><spring:message code="probe.jsp.menu.sysinfo"/></a></li>
        <li><a href="<c:url value="/system/probe/status.htm"/>"><spring:message code="probe.jsp.menu.status"/></a></li>
        <li><a href="<c:url value="/system/probe/charts.htm"/>"><spring:message code="probe.jsp.menu.charts"/></a></li>
        <li class="last"><a href="<c:url value="/system/probe/adm/quickcheck.htm"/>"><spring:message
                code="probe.jsp.menu.quickcheck"/></a></li>
    </ul>
    <spring:message code="probe.jsp.copyright"/>
    <div style="margin: 20px 0 0 0;">
    </div>
</div>

</body>
</html>