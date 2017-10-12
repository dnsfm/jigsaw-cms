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

<html>
<head>
    <title><spring:message code="probe.jsp.title.threads"/></title>
</head>

<c:set var="navTabThreads" value="active" scope="request"/>

<body>

<script type="text/javascript" language="javascript" src="<c:url value="/system/js/prototype.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/scriptaculous.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/func.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/behaviour.js"/>"></script>

<div>
    <ul class="options">
        <li id="abbreviations"><a href=""><spring:message code="probe.jsp.generic.abbreviations"/></a></li>
    </ul>

    <div class="blockContainer">

        <div id="help" class="helpMessage" style="display: none;">
            <div class="ajax_activity"></div>
        </div>

        <display:table name="threads" id="th" class="genericTbl" cellspacing="0" requestURI="" defaultsort="4"
                       defaultorder="ascending">
            <display:column class="leftMostIcon" title="&nbsp;">
                <a class="imglink"
                   onclick="return confirm('<spring:message code="probe.jsp.threads.killmsg" arguments="${th.name}"/>')"
                   href="<c:url value="/system/probe/adm/kill.htm"><c:param name="thread" value="${th.name}"/></c:url>">
                    <img class="lnk" src="${pageContext.request.contextPath}<spring:theme code="delete.png"/>"
                         alt="<spring:message code="probe.jsp.threads.stop.alt"/>"/>
                </a>
            </display:column>
            <display:column property="name" sortable="true" titleKey="probe.jsp.threads.col.name" maxLength="30" nowrap="true"/>
            <display:column property="priority" sortable="true" titleKey="probe.jsp.threads.col.priority"/>
            <display:column sortable="true" sortProperty="appName" titleKey="probe.jsp.threads.col.application" nowrap="true">
                ${th.appName}&nbsp;
            </display:column>

            <display:column sortable="true" sortProperty="classLoader" titleKey="probe.jsp.threads.col.classLoader" nowrap="true">
            <span class="expandable" onclick='toggleAndReloadPanel("dd${th_rowNum}","<c:url value="/cldetails.ajax?thread=${th.name}"/>")'>
                <js:out value="${th.classLoader}" maxLength="40" ellipsisRight="false"/>&nbsp;
            </span>

                <div id="dd${th_rowNum}" class="urlinfo" style="display: none;">
                    <spring:message code="probe.jsp.threads.info.loading"/></div>
            </display:column>

            <display:column property="groupName" sortable="true" titleKey="probe.jsp.threads.col.groupName" maxLength="15" nowrap="true"/>
            <display:column property="threadClass" sortable="true" titleKey="probe.jsp.threads.col.threadClass" maxLength="30" nowrap="true"/>
            <display:column sortable="true" sortProperty="runnableClassName" titleKey="probe.jsp.threads.col.runnableClass" maxLength="30" nowrap="true">
                ${th.runnableClassName}&nbsp;
            </display:column>
            <display:column property="daemon" sortable="true" titleKey="probe.jsp.threads.col.daemon"/>
            <display:column property="interrupted" sortable="true" titleKey="probe.jsp.threads.col.interrupted"/>
        </display:table>
    </div>
</div>

<script type="text/javascript">
    setupHelpToggle('<c:url value="threads.help.ajax"/>');
</script>

</body>
</html>