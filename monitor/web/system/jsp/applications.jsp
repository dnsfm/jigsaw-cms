<%@ page contentType="text/html;charset=UTF-8" language="java" session="false" %>
<%@ taglib uri='http://java.sun.com/jsp/jstl/core' prefix='c' %>
<%@ taglib uri="http://www.springframework.org/tags" prefix="spring" %>
<%@ taglib uri="http://displaytag.sf.net" prefix="display" %>
<%@ taglib uri="http://www.jstripe.com/tags" prefix="js" %>

<%--
    Probe "home" page. Displays list of web applications.
    It is assumed that command by the name "apps" is created by the controller.

    Author: Vlad Ilyushchenko
--%>

<html>

<head>
    <title><spring:message code="probe.jsp.title.applications"/></title>
</head>

<body>

<c:set var="navTabApps" value="active" scope="request"/>

<script type="text/javascript" language="javascript" src="<c:url value="/system/js/prototype.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/scriptaculous.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/effects.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/func.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/behaviour.js"/>"></script>

<script type="text/javascript">
    function handleContextReload(idx, context) {
        var img = $('ri_'+idx);
        var status = $('rs_'+idx);
        reload_url = '<c:url value="/system/probe/app/reload.ajax"/>?webapp='+context;
        img.src='${pageContext.request.contextPath}system/<spring:theme code="animated_reset.gif"/>';
        status.innerHTML="wait...";
        new Ajax.Updater(status,
                         '<c:url value="/system/probe/app/reload.ajax"/>?webapp='+context,
                         {method:'get',asynchronous:true}).onComplete = function() {
            img.src='${pageContext.request.contextPath}system/<spring:theme code="reset.gif"/>';
        };
        return false;
    }

    function toggleContext(idx, url, context) {
        status = $('rs_'+idx);
        status.innerHTML = '<img border="0" src="${pageContext.request.contextPath}system/<spring:theme code="progerssbar_editnplace.gif"/>"/>'
        new Ajax.Updater(status, url+'?webapp='+context, {method:'get',asynchronous:true});
        return false;
    }

</script>

<ul class="options">
    <c:choose>
        <c:when test="${param.size}">
            <li id="size" ><a href="?<js:toggle param="size"/>"><spring:message code="probe.jsp.applications.hidesize"/></a></li>
        </c:when>
        <c:otherwise>
            <li id="size" ><a href="?<js:toggle param="size"/>"><spring:message code="probe.jsp.applications.showsize"/></a></li>
        </c:otherwise>
    </c:choose>
    <li id="abbreviations"><a href=""><spring:message code="probe.jsp.generic.abbreviations"/></a></li>
</ul>

<div class="blockContainer">

    <div id="help" class="helpMessage" style="display: none;">
        <div class="ajax_activity"></div>
    </div>

    <c:if test="${! empty errorMessage}">
        <div class="errorMessage">
            <p>
                ${errorMessage}
            </p>
        </div>
    </c:if>

    <c:if test="${! empty successMessage}">
        <div id="successMessage">
            ${successMessage}
        </div>
    </c:if>

    <display:table class="genericTbl" name="apps" id="app" cellspacing="0" requestURI="" defaultsort="1"
                   defaultorder="ascending" cellpadding="0">

        <display:column class="leftMostIcon" sort="" title="&nbsp;">
            <a class="imglink" href="<c:url value="/system/probe/adm/undeploy.htm"><c:param name="webapp" value="${app.name}"/></c:url>"
               onclick="return confirm('<spring:message code="probe.jsp.applications.undeploy.confirm" arguments="${app.name}"/>')">
                <img class="lnk" src="${pageContext.request.contextPath}<spring:theme code="remove.img"/>"
                    alt="<spring:message code="probe.jsp.applications.alt.undeploy"/>"
                    title="<spring:message code="probe.jsp.applications.title.undeploy" arguments="${app.name}"/>"/>
            </a>
        </display:column>

        <display:column sortable="true" sortProperty="name" titleKey="probe.jsp.applications.col.name">
            <a href="<c:url value="/system/probe/appsummary.htm"><c:param name="webapp" value="${app.name}"/><c:param name="size" value="${param.size}"/></c:url>">${app.name}</a> 
        </display:column>

        <display:column sortable="true" titleKey="probe.jsp.applications.col.status" sortProperty="available">
                <c:choose>
                    <c:when test="${app.available}">
                        <a onclick="return toggleContext('${app_rowNum}', '<c:url value="/system/probe/app/toggle.ajax"/>', '${app.name}');"
                           class="okValue" href="<c:url value="/system/probe/app/stop.htm"/>?webapp=${app.name}"
                           title="<spring:message code="probe.jsp.applications.title.status.up" arguments="${app.name}"/>">
                            <div id="rs_${app_rowNum}">
                                <spring:message code="probe.jsp.applications.status.up"/>
                            </div>
                        </a>
                    </c:when>
                    <c:otherwise>
                        <a onclick="return toggleContext('${app_rowNum}', '<c:url value="/system/probe/app/toggle.ajax"/>', '${app.name}');"
                           class="errorValue" href="<c:url value="/system/probe/app/start.htm"/>?webapp=${app.name}"
                           title="<spring:message code="probe.jsp.applications.status.down.title" arguments="${app.name}"/>">
                            <div id="rs_${app_rowNum}">
                                <spring:message code="probe.jsp.applications.status.down"/>
                            </div>
                        </a>
                    </c:otherwise>
                </c:choose>
        </display:column>

        <display:column title="&nbsp;">
            <a onclick="return handleContextReload('${app_rowNum}', '${app.name}');"
               class="imglink"
               href="<c:url value="/system/probe/app/reload.htm"/>?webapp=${app.name}">
                <img id='ri_${app_rowNum}'
                     border="0" src="${pageContext.request.contextPath}<spring:theme code="reset.gif"/>"
                     alt="<spring:message code="probe.jsp.applications.alt.reload"/>"
                     title="<spring:message code="probe.jsp.applications.title.reload" arguments="${app.name}"/>"/>
            </a>
        </display:column>

        <display:column titleKey="probe.jsp.applications.col.description">
            ${app.displayName}&nbsp;
        </display:column>

        <display:column sortable="true" titleKey="probe.jsp.applications.col.requestCount" sortProperty="requestCount">
            <a href="<c:url value="/system/probe/appservlets.htm?webapp=${app.name}"/>">${app.requestCount}</a>
        </display:column>

        <display:column sortable="true" sortProperty="sessionCount"
                        titleKey="probe.jsp.applications.col.sessionCount">
            <a href="<c:url value="/system/probe/sessions.htm"><c:param name="webapp" value="${app.name}"/><c:param name="size" value="${param.size}"/></c:url>">
                ${app.sessionCount}
            </a>
        </display:column>

        <display:column property="sessionAttributeCount" sortable="true"
                        titleKey="probe.jsp.applications.col.sessionAttributeCount"/>

        <c:if test="${param.size}">
            <display:column sortProperty="size" sortable="true"
                            titleKey="probe.jsp.applications.col.size" class="highlighted">
                <js:volume value="${app.size}"/>
            </display:column>
        </c:if>

        <display:column sortable="true" sortProperty="contextAttributeCount"
                        titleKey="probe.jsp.applications.col.contextAttributeCount">
            <a href="<c:url value="/system/probe/appattributes.htm"><c:param name="webapp" value="${app.name}"/></c:url>">
                ${app.contextAttributeCount}
            </a>
        </display:column>

        <display:column property="sessionTimeout" sortable="true" titleKey="probe.jsp.applications.col.sessionTimeout"/>

        <display:column titleKey="probe.jsp.applications.col.jsp">
            <a class="imglink" href="<c:url value="/system/probe/app/jsp.htm"><c:param name="webapp" value="${app.name}"/></c:url>">
                <img border="0" src="${pageContext.request.contextPath}<spring:theme code="magnifier.png"/>" alt="<spring:message code="probe.jsp.applications.jsp.view"/>">
            </a>
        </display:column>

        <c:if test="${!no_resources}">
            <display:column sortable="true" sortProperty="dataSourceUsageScore"
                            titleKey="probe.jsp.applications.col.jdbcUsage" class="score_wrapper">
                <div class="score_wrapper">
                    <js:score value="${app.dataSourceUsageScore}" fullBlocks="10" partialBlocks="5" showEmptyBlocks="true" showA="true" showB="true">
                        <a class="imglink" href="<c:url value="/system/probe/resources.htm?webapp=${app.name}"/>"><img border="0"
                                 src="<c:url value="/system/css/classic/gifs/rb_{0}.gif"/>" alt="+"
                                 title="<spring:message code="probe.jsp.applications.jdbcUsage.title" arguments="${app.dataSourceUsageScore}"/>"/></a>
                    </js:score>
                </div>
            </display:column>
        </c:if>

        <display:column titleKey="probe.jsp.applications.col.distributable" sortable="true"
                        sortProperty="distributable">
            <c:choose>
                <c:when test="${app.distributable}">
                    <span class="okValue"><spring:message code="probe.jsp.generic.yes"/></span>
                </c:when>
                <c:otherwise>
                    <span class="errorValue"><spring:message code="probe.jsp.generic.no"/></span>
                </c:otherwise>
            </c:choose>
        </display:column>

        <display:column titleKey="probe.jsp.applications.col.serializable" sortable="true" sortProperty="serializable">
            <c:choose>
                <c:when test="${app.serializable}">
                    <span class="okValue"><spring:message code="probe.jsp.applications.serializable.yes"/></span>
                </c:when>
                <c:otherwise>
                    <span class="errorValue"><spring:message code="probe.jsp.applications.serializable.no"/></span>
                </c:otherwise>
            </c:choose>
        </display:column>

    </display:table>

    <script type="text/javascript">
        setupHelpToggle('<c:url value="/system/probe/applications.help.ajax"/>');
    </script>
</div>
</body>
</html>