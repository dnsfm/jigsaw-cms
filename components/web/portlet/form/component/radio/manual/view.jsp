<%@page contentType="text/html; charset=UTF-8"%><%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%><%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<input	id="<bean:write name="preferences" property="value(propertyId)"/>"	type="radio"	value="<bean:write name="preferences" property="value(value)"/>" name="<bean:write name="preferences" property="value(propertyId)"/>" <logic:equal value="true" name="preferences" property="value(checked)">checked="checked"</logic:equal>/>
	<logic:notEmpty  name="preferences" property="value(label)"><label for="<bean:write name="preferences" property="value(propertyId)"/>"><bean:write name="preferences" property="value(label)" filter="false"/></label></logic:notEmpty>