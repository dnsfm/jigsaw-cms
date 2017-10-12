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

<%--
    Displays a list of servlet context attributes for a given application

    Author: Andy Shapoval
--%>

<html>

<head>
    <title>
        <spring:message code="probe.jsp.title.app.attributes" arguments="${param.webapp}"/>
    </title>
</head>

<%--
    Make Tab #1 visually "active".
--%>
<c:set var="navTabApps" value="active" scope="request"/>
<c:set var="use_decorator" value="application" scope="request"/>
<c:set var="appTabAttributes" value="active" scope="request"/>

<body>

<link rel="stylesheet" href="${pageContext.request.contextPath}<spring:theme code="scroller.css"/>" type="text/css"/>

<script type="text/javascript" language="javascript" src="<c:url value="/system/js/prototype.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/behaviour.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/scriptaculous.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/areascroller.js"/>"></script>

<div class="embeddedBlockContainer">
    <h3><spring:message code="probe.jsp.app.attributes.h3.attributes"/></h3>


    <c:choose>
        <c:when test="${empty appAttributes}">
            <div class="infoMessage">
                <p>
                    <spring:message code="probe.jsp.app.attributes.noattributes"/>
                </p>
            </div>
        </c:when>
        <c:otherwise>
            <table id="resultsTable" cellspacing="0" cellpadding="0">
                <tr>
                    <td id="left_scroller" class="scroller">&nbsp;</td>
                    <td id="separator" width="1%">&nbsp;</td>
                    <td>
                        <div id="appAttrTblContainer" class="scrollable_content">
                            <display:table htmlId="appAttrTbl" name="appAttributes" id="attribute"
                                           class="genericTbl" cellspacing="0" cellpadding="0"
                                           requestURI="" defaultsort="1">
                                <display:column title="&nbsp;" width="20px;" class="leftMostIcon">
                                    <a href="
                                        <c:url value="/system/probe/app/rmappattr.htm">
                                            <c:param name="webapp" value="${param.webapp}"/>
                                            <c:param name="attr" value="${attribute.name}"/>
                                        </c:url>
                                    " class="imglink">
                                        <img class="lnk"
                                             src="${pageContext.request.contextPath}<spring:theme code="remove.img"/>"
                                             alt="<spring:message code="probe.jsp.app.attributes.col.delete"/>"
                                             title="<spring:message code="probe.jsp.app.attributes.col.delete.title"/>"/>
                                    </a>
                                </display:column>
                                <display:column property="name" sortable="true" maxLength="70"
                                                titleKey="probe.jsp.app.attributes.col.name"/>
                                <display:column property="type" sortable="true" maxLength="60"
                                                titleKey="probe.jsp.app.attributes.col.type"/>
                                <display:column titleKey="probe.jsp.app.attributes.col.value">
                                    <c:choose>
                                        <c:when test="${displayValues}">
                                            <c:out value="${attribute.value}" escapeXml="true"/>
                                        </c:when>
                                        <c:otherwise>
                                            **************
                                        </c:otherwise>
                                    </c:choose>
                                </display:column>
                            </display:table>
                        </div>
                    </td>
                    <td id="right_scroller" class="scroller">&nbsp;</td>
                </tr>
            </table>
            <script type="text/javascript">
                setupScrollers('appAttrTblContainer');
            </script>
        </c:otherwise>
    </c:choose>
</div>
</body>
</html>