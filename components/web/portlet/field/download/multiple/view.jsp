<%@page contentType="text/html; charset=UTF-8"%><%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%><%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%><%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<ul <logic:notEmpty name="preferences" property="value(style)">class="<bean:write name="preferences" property="value(style)"/>"</logic:notEmpty>><logic:equal value="name" name="preferences" property="value(showWhat)"><li><a>文件名1</a></li><li><a>文件名2</a></li></logic:equal><logic:equal value="text" name="preferences" property="value(showWhat)"><li><a><logic:notEmpty name="preferences" property="value(text)"><bean:write name="preferences" property="value(text)" filter="false"/></logic:notEmpty></a></li><li><a><logic:notEmpty name="preferences" property="value(text)"><bean:write name="preferences" property="value(text)" filter="false"/></logic:notEmpty></a></li></logic:equal></ul>
