<%@page contentType="text/html; charset=UTF-8"%><%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%><%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%><%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<logic:notEqual value="on"  name="preferences" property="value(showHref)">
<logic:empty name="preferences" property="value(imgsrc)">
<button <logic:notEmpty name="preferences" property="value(style)">class="<bean:write name="preferences" property="value(style)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(tabindex)">tabindex="<bean:write name="preferences" property="value(tabindex)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(size)">size="<bean:write name="preferences" property="value(size)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(size)">size="<bean:write name="preferences" property="value(size)"/>"</logic:notEmpty>  ><bean:write name="preferences" property="value(value)"/></button>
</logic:empty>
<logic:notEmpty name="preferences" property="value(imgsrc)">
<img <logic:notEmpty name="preferences" property="value(imgstyle)">class="<bean:write name="preferences" property="value(imgstyle)"/>"</logic:notEmpty><logic:notEmpty name="preferences" property="value(tabindex)">tabindex="<bean:write name="preferences" property="value(tabindex)"/>"</logic:notEmpty><logic:notEmpty name="preferences" property="value(imgsrc)">src="<bean:write name="preferences" property="value(imgsrc)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(imghwidth)">width="<bean:write name="preferences" property="value(imgwidth)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(imgheight)">height="<bean:write name="preferences" property="value(imgheight)"/>"</logic:notEmpty>/>
</logic:notEmpty>
</logic:notEqual>
<logic:equal value="on"  name="preferences" property="value(showHref)">
<a href="javascript:void(0)" <logic:notEmpty name="preferences" property="value(style)">class="<bean:write name="preferences" property="value(style)"/>"</logic:notEmpty> <logic:notEmpty name="preferences" property="value(tabindex)">tabindex="<bean:write name="preferences" property="value(tabindex)"/>"</logic:notEmpty>  ><bean:write name="preferences" property="value(value)"/></a>
</logic:equal>

