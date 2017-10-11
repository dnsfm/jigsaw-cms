<%@ page contentType="text/html; charset=UTF-8" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ taglib uri="/WEB-INF/fulong-portal.tld" prefix="portlet"%>
<table cellpadding="0" cellspacing="0" border="0">
  <portlet:form action="save" method="POST">
    <tr>
      <td class="pannelDiv" rowspan="2">
        <select id="pannelSelect" name="pannelSelect" onchange="selectPanel(this)" size="10">
          <option value="0" selected="selected">基本设置</option>
        </select>
      </td>
      <td>
        <fieldset>
          <table width="100%" cellpadding="2" cellspacing="2" border="0" class="formTable">
            <tr>
              <td class="formTitle">属性</td>
              <td class="formComponent">
                <input name="preference(category-id)" type="hidden" value="<bean:write name="definition" ignore="true"/>" />
                <html:hidden property="preference(propertyId)"/>
                <input type="text" name="fieldName" readonly="readonly" value="<logic:present name="property"><bean:write name="property" property="name" ignore="true"/></logic:present><logic:notPresent name="property"><bean:write name="propertyDeleted" ignore="true"/></logic:notPresent>" />
                <button type="button" class="commonbut" id="search" onclick="searchPropertyDefinition('<bean:write name="definition" ignore="true"/>')">选择...</button>
              </td>
            </tr>
            <tr>
              <td class="formTitle">宽度</td>
              <td class="formComponent"><html:text property="preference(width)"/> </td>
            </tr>
            <tr>
              <td class="formTitle">高度</td>
              <td class="formComponent"><html:text property="preference(height)"/> </td>
            </tr>
            <tr>
              <td class="formTitle">初始值</td>
              <td class="formComponent"><html:text property="preference(value)"/> </td>
            </tr>
            <tr>
              <td class="formTitle">Tab键顺序</td>
              <td class="formComponent">
                <html:text property="preference(tabindex)"/>
              </td>
            </tr>
            <tr>
              <td class="formTitle">样式</td>
              <td class="formComponent">
                <html:text property="preference(style)"/><button type="button" class="commonbut" onclick="doSelectStyle(this.form.elements['preference(style)'],'')">选择...</button>
              </td>
            </tr>
          </table>
        </fieldset>
        <div class="toolbar">
          <button type="button" onclick="validatorRequired(new Array(form.elements['preference(propertyId)']),new Array('属性'),this.form)">保存</button>
          <button type="button" onclick="window.parent.close()">取消</button>
        </div>
      </td>
    </tr>
  </portlet:form>
</table>
<script language="javascript" src="/ide/common/script/portlet.js" type="text/javascript" ></script>
<script type="text/javascript" language="javascript">
  /**
  *选择待显示的属性
  */
  function searchPropertyDefinition($categoryId){
    var arr = CMSDialog.PropertyDefinitionSelector($categoryId);
    if(arr!=null){
      document.getElementsByName("fieldName")[0].value = arr.name;
      document.getElementsByName("preference(propertyId)")[0].value = arr.ID;
    }
  }
</script>
