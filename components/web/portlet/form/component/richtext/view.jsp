<%@page contentType="text/html; charset=UTF-8"%><%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%><%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%><%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<div style="<logic:present name="preferences" property="value(width)">width:<bean:write name="preferences" property="value(width)"/>;</logic:present> <logic:present name="preferences" property="value(height)">height:<bean:write name="preferences" property="value(height)"/>;</logic:present> position:absolute;z-index:2"></div>
<input type="text" style="display: none;" name="<bean:write name="preferences" property="value(propertyId)" ignore="true"/>" <logic:notEmpty name="preferences" property="value(value)">value="<bean:write name="preferences" property="value(value)"/>"</logic:notEmpty> />
<iframe disabled="true" <logic:notEmpty name="preferences" property="value(width)">width="<bean:write name="preferences" property="value(width)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(height)">height="<bean:write name="preferences" property="value(height)"/>"</logic:notEmpty> allowtransparency="true" frameborder="0" id="eWebEditor" src="/ide/common/editor/richEditor.jsp?InstanceName=<bean:write name="preferences" property="value(propertyId)" ignore="true"/>" <logic:notEmpty name="preferences" property="value(style)">class="<bean:write name="preferences" property="value(style)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(tabindex)">tabindex="<bean:write name="preferences" property="value(tabindex)"/>"</logic:notEmpty> ></iframe>
