<%@ page contentType="text/html; charset=UTF-8" %>
<%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@taglib uri="/WEB-INF/fulong.tld" prefix="fulong"%>
<%@taglib uri="/WEB-INF/fulong-cms.tld" prefix="cms"%>
<%@taglib uri="/WEB-INF/fulong-portal.tld" prefix="portlet"%>
<table cellpadding="0" cellspacing="0" border="0">
    <portlet:form action="save" method="POST" onsubmit="doSubmit(this)">
        <tr>
            <td class="pannelDiv" rowspan="2">
                <select id="pannelSelect" name="pannelSelect" onchange="selectPanel(this)" size="10">
                    <option value="0" selected="selected">基本设置</option>
                    <option value="1">满足内容</option>
                    <option value="2">不满足内容</option>
                </select></td>
                <td><fieldset>
                  <table width="100%" cellpadding="2" cellspacing="2" border="0" class="formTable">
                    <tr>
                      <td class="formTitle" valign="top">内容来源</td>
                      <td class="formComponent" valign="top">
                        <table border=0 cellpadding=0 cellspacing=0>
                          <tr>
                            <td>
                              <html:radio style="width:25px" styleId="b1" property="preference(contentType)" value="default">
                                <label for="b1">使用URL参数指定内容</label></html:radio>
                              </td>
                            </tr>
                            <tr>
                              <td>
                                <html:radio style="width:25px" styleId="b2" property="preference(contentType)" value="user"><label for="b2">使用当前登录用户</label></html:radio>
                              </td>
                            </tr>
                            <tr>
                              <td>
                                <html:radio style="width:25px" styleId="b3" property="preference(contentType)" value="site"><label for="b3">使用当前网站所属用户</label></html:radio>
                              </td>
                            </tr>
                          </table>
                        </td>
                      </tr>
                      <tr>
                        <td nowrap="nowrap">内容分类</td>
                        <td>
                          <html:hidden property="preference(category)"/>
                          <input type="text" name="categoryName" readonly="readonly" value="<bean:write name="category" property="name" ignore="true"/>" />
                          <button type="button" class="commonbut" id="searchN" onclick="searchNodeDefinition(form.elements['preference(category)'],form.elements['categoryName'])">选择...</button>
                        </td>
                      </tr>
                      <tr>
                        <td nowrap="nowrap">条件</td>
                        <td nowrap="nowrap"  class="selectionEditor">
                  <table cellpadding="0" cellspacing="0" border="0">
                  <tr>
                  <td>
                            <select multiple="multiple" name="preferences(conditions)" size="5" multiple="true" style="width:210px;">
                                <logic:present name="preferences" property="values(conditions)">
                                    <logic:iterate id="pattern" name="preferences" property="values(conditions)">
                                        <option value='<bean:write name="pattern" filter="false"/>'>
                                        <fulong:filter name="pattern" definition="category"/></option>
                                    </logic:iterate>
                                </logic:present>
                            </select>
                    </td><td valign="top">
                              <button type="button" class="commonbut" onclick="newFilter(form.elements['preference(category)'],form.elements['preferences(conditions)'])">添加</button><br/>
                              <button type="button" class="commonbut" onclick="deleteOption(form.elements['preferences(conditions)'])">删除</button>
                    </td>
                    </tr>
                    </table>
                        </td>
                      </tr>
                </table>
                </fieldset>
            <fieldset style="display:none">
              <table width="100%" cellpadding="2" cellspacing="2" border="0" class="formTable">
                <tr>
                  <td class="formTitle">显示内容</td>
                  <td class="formComponent" width="80%"><button type="button" onclick="editClipFile('<bean:write name="truePath" />',form.elements['preference(category)'],document.getElementById('editorFrame'))">修改...</button></td>
                </tr>
                <tr>
                  <td colspan="2">
                    <iframe scrolling="yes" marginheight="0" marginwidth="0" frameborder="0" src='<bean:write name="trueClipPath"/>?javax.portlet.page.mode=view' width="350px" height="280px" id="editorFrame">                </iframe>
                  </td>
                </tr>
              </table>
            </fieldset>
            <fieldset style="display:none">
              <table width="100%" cellpadding="2" cellspacing="2" border="0" class="formTable">
                <tr>
                  <td class="formTitle">显示内容</td>
                  <td class="formComponent" width="80%"><button type="button" onclick="editClipFile('<bean:write name="falsePath"/>',form.elements['preference(category)'],document.getElementById('editorFrame2'))">修改...</button></td>
                </tr>
                <tr>
                  <td colspan="2">
                    <iframe scrolling="yes" marginheight="0" marginwidth="0" frameborder="0" src='<bean:write name="falseClipPath"/>?javax.portlet.page.mode=view' width="350px" height="280px" id="editorFrame2">                </iframe>
                  </td>
                </tr>
              </table>
            </fieldset>
                <div class="toolbar">
          		<input type="submit" value="保存"/>
          		<button type="button" onclick="window.parent.close()">取消</button></div></td>
                </tr></portlet:form>
            </table>
            <script type="text/Javascript" src='/ide/common/script/portlet.js'></script>
            <script type="text/javascript" language="javascript">
            function doSubmit(oForm){
              selectAll(document.getElementsByName('preferences(conditions)')[0]);
              return true;
            }
            <bean:define name="preferences" property="value(category)" id="categoryID" type="String"/>
            var propertys=new Array();
            <logic:iterate id="defaultValues" name="preferences" property="values(conditions)">
            <bean:define id="defaultValueS" name="defaultValues" type="String"/>
            <%String propertyID=defaultValueS.split(" ")[0];%>
            <cms:propertyDefinition definitionID="<%=categoryID%>"  propertyID="<%=propertyID%>" ID="pro"/>
            propertys['<%=propertyID%>']=new Object();
            propertys['<%=propertyID%>'].name='<bean:write name="pro" property="name" ignore="true"/>';
            propertys['<%=propertyID%>'].ID='<bean:write name="pro" property="ID" ignore="true"/>';
            </logic:iterate>
            </script>