<%@page contentType="text/html; charset=UTF-8"%><%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%><%@taglib uri="/WEB-INF/fulong.tld" prefix="fulong"%><%@taglib uri="/WEB-INF/fulong-portal.tld" prefix="portlet"%>
<img alt="" src='/components/chart/<bean:write name="key" />.png' border="0" width="<bean:write name='preferences' property='value(width)'/>" height="<bean:write name='preferences' property='value(height)'/>" />