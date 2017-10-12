<%@ page contentType="text/html; charset=UTF-8"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@taglib uri="/WEB-INF/fulong-cms.tld" prefix="fulong"%>
<%@ taglib uri="/WEB-INF/struts-tiles.tld" prefix="tiles"%>
<%@taglib uri="/WEB-INF/fulong.tld" prefix="fl"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>批量修改内容</title>
<meta http-equiv=Content-Type content="text/html; charset=UTF-8" />
<link rel="stylesheet" type="text/css" href="editor.css" />
<link rel="stylesheet" type="text/css" href='<html:rewrite page="/calendar/skins/aqua/theme.css" module="/common"/>' />
<script type="text/javascript" src='<html:rewrite page="/script/common.js" module="/common"/>'></script>
<script type="text/javascript" src='<html:rewrite page="/calendar/calendar.js" module="/common"/>'></script>
<script type="text/javascript" src='<html:rewrite page="/calendar/lang/cn_utf8.js" module="/common"/>'></script>
<script type="text/javascript" src="cmseditor.js"></script>
<script type="text/javascript" src="../classes/cmsdialog.js"></script>
</head>
<body style="text-align: center">
<h1>批量修改内容</h1>
<html:form action="batSave.do" enctype="multipart/form-data" method="POST">
<logic:iterate id="nodeid" name="nodes">
<input type="hidden" name="nodeID" value="<bean:write name="nodeid" ignore="true"/>">
</logic:iterate>
	<table border="1" cellpadding="2" cellspacing="0" class="sheetClass" width="100%" id="contentEditor">	
		<logic:iterate id="property" name="properties">
			<bean:define id="propID" name="property" property="ID" type="java.lang.String" />
			<bean:define id="definitionID" name="property" property="declaringNodeDefinition.ID" type="java.lang.String" />
			<tr>
				<th nowrap="nowrap"><bean:write name="property" property="name" /></th>
				<td>
				<table width="100%" border="0" cellspacing="0" cellpadding="2" id='tb<bean:write name="propID"/>'>
					<tbody id='<bean:write name="propID"/>'>
						<tr>
							<td id='td<bean:write name="propID"/>'>				
							<logic:equal value="1" name="property" property="type">
								<html:text property='<%= "values("+propID+")" %>' style="width:100%" value="" styleId='<%="id"+propID%>'/><input type="checkbox"  name="<%= "values("+propID+")" %>check" value="false" title="该属性列置空值" onclick="disableInput(this,'id<%=propID%>');"/>清空此属性值
							</logic:equal> 
							<logic:equal value="2" name="property" property="type">
								<html:file property='<%= "files("+propID+")" %>' style="width:100%"  styleId='<%="id"+propID%>'/><input type="checkbox"  name="<%= "values("+propID+")" %>check" value="false" title="该属性列置空值" onclick="disableInput(this,'id<%=propID%>');"/>清空此属性值
							</logic:equal> 
							<logic:equal value="3" name="property" property="type">
								<html:text property='<%= "values("+propID+")" %>' style="width:100%"  value="" style="ime-mode:disabled" onblur="CMSEditor_checkLong(this)" styleId='<%="id"+propID%>'
									onkeypress="if ((event.keyCode < 45 || event.keyCode > 57)) event.returnValue = false;" /><input type="checkbox"  name="<%= "values("+propID+")" %>check" value="false" title="该属性列置空值" onclick="disableInput(this,'id<%=propID%>');"/>清空此属性值
							</logic:equal> 
							<logic:equal value="4" name="property" property="type">
								<html:text property='<%= "values("+propID+")" %>' style="width:100%"  value="" style="ime-mode:disabled" onblur="CMSEditor_checkDouble(this)" styleId='<%="id"+propID%>'
									onkeypress="if ((event.keyCode < 45 || event.keyCode > 57)) event.returnValue = false;" />
								<input type="checkbox"  name="<%= "values("+propID+")" %>check" value="false" title="该属性列置空值" onclick="disableInput(this,'id<%=propID%>');"/>清空此属性值
							</logic:equal> 
							<logic:equal value="5" name="property" property="type">
								<html:text onblur="funcTimeValid(this)" property='<%= "values("+propID+")" %>' style="width:100%"  value="" style="ime-mode:disabled" styleId='<%="id"+propID%>'/><input type="button" style="height:24px;width:24px;" onclick="return showCalendar(this, this.previousSibling, '%Y-%m-%d %H:%M:%S', null, true);" value="..."/><input type="checkbox"  name="<%= "values("+propID+")" %>check" value="false" title="该属性列置空值" onclick="disableInput(this,'id<%=propID%>');"/>清空此属性值
							</logic:equal> 
							<logic:equal value="6" name="property" property="type">
								<html:radio property='<%= "values("+propID+")" %>' value="true">是</html:radio>
								<html:radio property='<%= "values("+propID+")" %>' value="false">否</html:radio>
							</logic:equal> 
							<logic:equal value="7" name="property" property="type">
								<html:text property='<%= "values("+propID+")" %>' style="width:100%"   value="" styleId='<%="id"+propID%>'/>
							    <input type="checkbox"  name="<%= "values("+propID+")" %>check" value="false" title="该属性列置空值" onclick="disableInput(this,'id<%=propID%>');"/>清空此属性值
							</logic:equal> 
							<logic:equal value="8" name="property" property="type">
								<html:text property='<%= "values("+propID+")" %>' style="width:100%"  value="" styleId='<%="id"+propID%>'/><input type="checkbox"  name="<%= "values("+propID+")" %>check" value="false" title="该属性列置空值" onclick="disableInput(this,'id<%=propID%>');"/>清空此属性值
								</logic:equal><logic:equal value="9" name="property" property="type">
								<html:text readonly="true" property='<%= "values("+propID+")" %>' style="width:100%"  value="" styleId='<%="id"+propID%>'/><input type="button" value=" ... " onclick="CMSEditor_selectNode(this.previousSibling)"/><input type="checkbox"  name="<%= "values("+propID+")" %>check" value="false" title="该属性列置空值" onclick="disableInput(this,'id<%=propID%>');"/>清空此属性值
							</logic:equal> 
							<logic:equal value="10" name="property" property="type">
								<html:textarea property='<%= "values("+propID+")" %>' cols="90" rows="5"  style="width:100%" value="" styleId='<%="id"+propID%>'/><input type="checkbox"  name="<%= "values("+propID+")" %>check" value="false" title="该属性列置空值" onclick="disableInput(this,'id<%=propID%>');"/>清空此属性值
							</logic:equal>
							</td>
                            <logic:notEqual value="6" name="property" property="type">
							<td width="20"><input type="button" class="btnValues" value="+" onclick="CMSEditor_addValue(this,document.getElementById('td<bean:write name="propID"/>'),<bean:write name="property" property="type"/>, true)" /></td>
							<td width="20"><input type="button" class="btnValues" value="-" onclick="CMSEditor_removeValue(this,document.getElementById('td<bean:write name="propID"/>'),<bean:write name="property" property="type"/>, true)" /></td>
						    </logic:notEqual>
						</tr>
					</tbody>
				</table>
				</td>
			</tr>
		</logic:iterate>
	</table>
	<div class="operation">
	<button id="btnOk" type="button" onclick="this.form.submit()" class="commonbut">保存</button>
	<button id="btnCancel" type="button" onclick="window.close();" class="commonbut">取消</button>
	</div>

	<script language="JavaScript" type="text/Javascript">
	function funcTimeValid(obj)
    {
   	 var selStr = obj.value;
   	 var bar=/^(\d{1,4})(-|\/)(\d{1,2})\2(\d{1,2})/;
   	 if(selStr != "")
   	 {
   		 if (!bar.test(obj.value))
		     {
	    	     alert("日期格式不正确!"); 
	    	     obj.value="";
	    	     obj.focus();
	    	     return; 
	    	 } 
	     }
	}
		function disableInput(obj,name){
			if(obj.checked == true){
				document.getElementById(name).value ="";
				document.getElementById(name).disabled = true;
			}else{
				document.getElementById(name).disabled = false;
			}
		}
	</script>    

</html:form>
</body>
</html>
