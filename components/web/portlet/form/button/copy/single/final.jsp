<%@page contentType="text/html; charset=UTF-8"%><%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%><%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%><%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%><%@taglib uri="/WEB-INF/fulong-portal.tld" prefix="pt"%>
<pt:actionURL portletMode="final" var="formURL"><pt:param name="portlet_action_name">copyNode</pt:param><pt:param name="node"><bean:write name="node" property="ID"/></pt:param></pt:actionURL>
<script type="text/javascript" language="javascript">
var categories<bean:write name='javax.portlet.id'/> = new Array();
<logic:iterate id="c" name="preferences" property="values(categorys)">
categories<bean:write name='javax.portlet.id'/>.push('<bean:write name="c"/>')
</logic:iterate>
</script>
<button type="button" <logic:notEmpty name="preferences" property="value(style)">class="<bean:write name="preferences" property="value(style)"/>"</logic:notEmpty><logic:notEmpty name="preferences" property="value(tabindex)">tabindex="<bean:write name="preferences" property="value(tabindex)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(size)">size="<bean:write name="preferences" property="value(size)"/>"</logic:notEmpty> onclick="CopyPortlet.singleCopy('<%=formURL%>',categories<bean:write name='javax.portlet.id'/>,<bean:write name="preferences" property="value(choose)"/>,'<bean:write name="preferences" property="value(value)" />')"   <logic:notEmpty name="preferences" property="value(size)">size="<bean:write name="preferences" property="value(size)"/>"</logic:notEmpty>><bean:write name="preferences" property="value(value)"/></button>
