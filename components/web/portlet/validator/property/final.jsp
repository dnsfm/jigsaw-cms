<%@ page contentType="text/html; charset=UTF-8" %><%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %><%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<span id="<bean:write name='javax.portlet.id'/>_0" style="display:none" <logic:notEmpty name='preferences' property='value(error-style)'>class=<bean:write name='preferences' property='value(error-style)'/></logic:notEmpty>><bean:write name="preferences" property="value(error-tips)"/></span>
<span id="<bean:write name='javax.portlet.id'/>_1" <logic:notEmpty name='preferences' property='value(tips-style)'>class=<bean:write name='preferences' property='value(tips-style)'/></logic:notEmpty>><bean:write name="preferences" property="value(tips)"/></span>
<logic:notEqual value="false" name="preferences" property="value(pw)">
<script type="text/javascript" language="javascript">
Validator.AddRule('<bean:write name="preferences" property="value(form)"/>','<bean:write name="preferences" property="value(propertyId)"/>','<bean:write name="javax.portlet.id"/>_1','<bean:write name="javax.portlet.id"/>_0','pwequal','<bean:write name="value" ignore="true"/>');
</script>
</logic:notEqual>
<logic:notEqual value="true" name="preferences" property="value(pw)">
<script type="text/javascript" language="javascript">
Validator.AddRule('<bean:write name="preferences" property="value(form)"/>','<bean:write name="preferences" property="value(propertyId)"/>','<bean:write name="javax.portlet.id"/>_1','<bean:write name="javax.portlet.id"/>_0','equal','<bean:write name="value" ignore="true"/>');
</script>
</logic:notEqual>