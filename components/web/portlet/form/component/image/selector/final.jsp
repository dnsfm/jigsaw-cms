<%@page contentType="text/html; charset=UTF-8"%><%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%><%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%><%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<div id="preview_<bean:write name="preferences" property="value(propertyId)"/>" style="<logic:notEmpty name="preferences" property="value(previewWidth)">width:<bean:write name="preferences" property="value(previewWidth)"/>;</logic:notEmpty> <logic:notEmpty name="preferences" property="value(previewHeight)">height:<bean:write name="preferences" property="value(previewHeight)"/>;</logic:notEmpty>" <logic:notEmpty name="preferences" property="value(previewStyle)">class="<bean:write name="preferences" property="value(previewStyle)"/>"</logic:notEmpty>>
<logic:notEmpty name="preferences" property="value(value)"><img style="<logic:notEmpty name="preferences" property="value(previewWidth)">width:<bean:write name="preferences" property="value(previewWidth)"/>;</logic:notEmpty> <logic:notEmpty name="preferences" property="value(previewHeight)">height:<bean:write name="preferences" property="value(previewHeight)"/>;</logic:notEmpty>" src="<bean:write name="pathValue"/>" style="position:relative"/></logic:notEmpty><logic:empty name="preferences" property="value(value)"><img src="<logic:empty name="preferences" property="value(defaultImage)">/ide/common/images/no_pic.gif</logic:empty><logic:notEmpty name="preferences" property="value(defaultImage)"><bean:define id="defaultImage" name="preferences" property="value(defaultImage)" type="String"/><%=defaultImage%></logic:notEmpty>" width="100%" height="100%" /></logic:empty></div>
<input type="text" <logic:notEmpty name="preferences" property="value(size)">size="<bean:write name="preferences" property="value(size)"/>"</logic:notEmpty> name="<bean:write name="preferences" property="value(propertyId)" />" <logic:notEmpty name="preferences" property="value(textStyle)">class="<bean:write name="preferences" property="value(textStyle)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(value)">value="<bean:write name="preferences" property="value(value)"/>"</logic:notEmpty> />
<button <logic:notEmpty name="preferences" property="value(tabindex)">tabindex="<bean:write name="preferences" property="value(tabindex)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(buttonStyle)">class="<bean:write name="preferences" property="value(buttonStyle)"/>"</logic:notEmpty> onclick="openImageSelector(document.getElementById('preview_<bean:write name="preferences" property="value(propertyId)"/>'), this.form['<bean:write name="preferences" property="value(propertyId)" />']);" <%--onblur="Validator.ValidateComponent(this, this.name)"--%>>选择...</button>
