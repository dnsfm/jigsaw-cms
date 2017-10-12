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

<html>
<head><title>${param.cn}</title></head>

<c:url value="/system/probe/chart.png" var="imgurl" scope="request">
    <c:param name="l" value="true"/>
    <c:param name="p" value="${param.p}"/>
    <c:param name="sp" value="${param.sp}"/>
    <c:choose>
        <c:when test="${param.p == 'traffic'}">
            <c:param name="s1c" value="#95FE8B"/>
            <c:param name="s1o" value="#009406"/>
            <c:param name="s2c" value="#FDFB8B"/>
            <c:param name="s2o" value="#D9CB00"/>
            <c:param name="s1l" value="sent"/>
            <c:param name="s2l" value="received"/>
        </c:when>
        <c:otherwise>
            <c:param name="s1l" value="requests"/>
            <c:param name="s2l" value="errors"/>
        </c:otherwise>
    </c:choose>
</c:url>

<c:set var="navTabCharts" value="active" scope="request"/>

<script type="text/javascript" language="javascript" src="<c:url value="/system/js/prototype.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/scriptaculous.js"/>"></script>
<script type="text/javascript" language="javascript" src="<c:url value="/system/js/func.js"/>"></script>

<body>

<ul class="options">
    <li id="back"><a href="<c:url value="charts.htm"/>"><spring:message code="probe.jsp.zoomedchart.back"/></a></li>
</ul>

<div class="blockContainer">
    <div class="shadow">
        <div class="info">
            <p><spring:message code="probe.jsp.zoomedchart.information"/></p>
        </div>
    </div>

    <div id="sliderContainer">
        <div id="track">
            <div id="handle"><img src="${pageContext.request.contextPath}<spring:theme code="slider.gif"/>" alt=""/></div>
        </div>
    </div>

    <div>
        <img id="img" class="scale-image" src="${imgurl}&xz=800&yz=350" alt=""/>
    </div>

    <script type="text/javascript" language="JavaScript">

        // "animate" our slider
        var slider = new Control.Slider('handle', 'track', {axis:'horizontal', alignX: -5, increment: 2, sliderValue: 0});

        // resize the image as the slider moves. The image quality would deteriorate, but it
        // would not be final anyway. Once slider is released the image is re-requested from the server, where
        // it is rebuilt from vector format
        slider.options.onSlide = function(value) {
            scaleImage(value, 800, 1600);
        }

        // this is where the slider is released and the image is reloaded
        // we use current style settings to work our the required image dimensions
        slider.options.onChange = function(value) {
            // chop off "px" and round up float values
            width = Math.round(Element.getStyle("img", "width").replace("px", ""));
            height = Math.round(width / 2.29);
            // reload the images
            document.images.img.src = '<c:out value="${imgurl}" escapeXml="false"/>&xz=' + width + '&yz=' + height;
            // reset the image auto-updater
            // to make sure the auto-updater knows the changed image dimensions
            if (updater) updater.stop();
            updater = new Ajax.ImgUpdater("img", 15);
        }

        // start image auto-updater
        updater = new Ajax.ImgUpdater("img", 15);

    </script>
</div>
</body>
</html>