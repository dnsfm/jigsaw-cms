<%@ page contentType="text/html; charset=UTF-8" %><%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%><%@taglib uri="/WEB-INF/fulong-site.tld" prefix="site"%><%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<bean:define id="type" name="preferences" property="value(type)" type="java.lang.String"/>
<bean:define id="target" name="preferences" property="value(newWindows)" type="java.lang.String"/>
<logic:notEqual value="item" name="type">
<a id='<%=request.getAttribute("javax.portlet.id")%>' target="<%=target%>" title="<bean:write name="value" ignore="true"/>"  href="<site:nodeURL name="node" type="<%=type%>"/>">
	<bean:write name="value" ignore="true"/>
</a>
</logic:notEqual>
<logic:equal value="item" name="type">
	<span id='<%=request.getAttribute("javax.portlet.id")%>'><bean:write name="value" ignore="true"/></span>
</logic:equal>