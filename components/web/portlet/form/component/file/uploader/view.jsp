<%@page contentType="text/html; charset=UTF-8"%><%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%><%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%><%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<input type="file" disabled="true" <logic:notEmpty name="preferences" property="value(size)">size="<bean:write name="preferences" property="value(size)"/>"</logic:notEmpty> name="<bean:write name="preferences" property="value(propertyId)" ignore="true"/>" <logic:notEmpty name="preferences" property="value(style)">class="<bean:write name="preferences" property="value(style)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(tabindex)">tabindex="<bean:write name="preferences" property="value(tabindex)"/>"</logic:notEmpty> />
