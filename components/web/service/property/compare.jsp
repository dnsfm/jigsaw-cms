<%@ page contentType="text/html; charset=UTF-8" %>
<%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@taglib uri="/WEB-INF/struts-tiles.tld" prefix="tiles"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>日期属性值比较</title>
<base target="_self" />
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<meta http-equiv="Cache-Control" content="no-cache, must-revalidate" />
<meta http-equiv="expires" content="Wed, 26 Feb 1997 08:21:57 GMT" />
<link rel="stylesheet" type="text/css" href="/ide/service/styles.css"/>
<script language="Javascript" type="text/Javascript" src="/ide/common/script/common.js"></script>
<script language="Javascript" type="text/Javascript" src="/ide/service/scripts.js.jsp"></script>
<script language="Javascript" type="text/Javascript" src="/ide/cms/classes/cmsdialog.js"></script>
<script language="Javascript" type="text/Javascript" src="/ide/common/script/xmlhttp.js"></script>
<script language="Javascript" type="text/Javascript" src="/ide/common/script/ajax.js"></script>
<script type="text/javascript" language="javascript">
		var config = window.dialogArguments.parameters;
		function doInit(){
			config.populateForm(configForm);
		}
		function ok(){
			if(!validatePositive(configForm.time.value)){
				alert("刷新间隔必须是正数！");
				return;
			}
			config.updateFromForm(configForm);
			window.returnValue = config;
			window.close();   
		}
		function selectCategory(objID,objName){
			  var definition=CMSDialog.NodeDefinitionSelector();
				if(definition!=null){
			   if(definition.length>0){
			       for(var j=0;j<definition.length;j++){
			    	   objID.value=definition[j].ID;
			    	   objName.value=definition[j].name;
			       }
			     }
			  }
			}
		function validatePositive(time){
			var TIME_PATTERN = /^\d+(\.\d+)?$/;
			if(!TIME_PATTERN.test(time)){
				return false;
			}
			return true;
		}
		function selectProperty(categoryID,objID,objName,type){
			if(categoryID==null){
				alert("请选择分类！");
				return;
				}
			
			    var result=CMSDialog.PropertyDefinitionSelector(categoryID,'',type);
			    if(result!=null){
			    	objID.value=result.ID;
			    	objName.value=result.name;
			      }
		}
</script>
</head>
<body onload="doInit()">
<table cellpadding="0" cellspacing="0" border="0" width="100%">
		<tr>
			<td class="pannelDiv" valign="top"><select id="pannelSelect" name="pannelSelect" onchange="Service.SelectPanel(this)" size="10">
					<option value="0">基本信息</option>
			</select></td>
			<td id="tdFieldsets" valign="top" align="center">
			<form name="configForm">
			<fieldset class="fieldPanel">
			<div
				style="height: 200px;">
				<table>
				<tr>
			<td>内容分类<td>
			<td>
				<input type="hidden" name="compareCategoryID" />
			    <input type="text" name="compareCategoryName" readonly="readonly" />
				</td>
				<td>
			<button type="button" onclick="selectCategory(document.getElementById('compareCategoryID'),document.getElementById('compareCategoryName'))">选择...</button>
			</td>
			</tr>
			<tr>
			<td>属性1<td>
			<td>
				<input type="hidden" name="prop1ID" />
			    <input type="text" name="prop1Name" readonly="readonly" />
				</td>
				<td>
			<button type="button" onclick="selectProperty(document.getElementById('compareCategoryID').value,document.getElementById('prop1ID'),document.getElementById('prop1Name'),['5'])">选择...</button>
			</td>
			</tr>
			<tr>
			<td>属性2<td>
			<td>
				<input type="hidden" name="prop2ID" />
			    <input type="text" name="prop2Name" readonly="readonly" />
				</td>
				<td>
			<button type="button" onclick="selectProperty(document.getElementById('compareCategoryID').value,document.getElementById('prop2ID'),document.getElementById('prop2Name'),['5'])">选择...</button>
			</td>
			</tr>
			<tr>
			<td>比较结果属性<td>
			<td>
				<input type="hidden" name="resultPropID" />
			    <input type="text" name="resultPropName" readonly="readonly" />
				</td>
				<td>
			<button type="button" onclick="selectProperty(document.getElementById('compareCategoryID').value,document.getElementById('resultPropID'),document.getElementById('resultPropName'))">选择...</button>
			</td>
			</tr>
			<tr>
			<td>结果显示<td>
			<td>
			    <input type="text" name="resultMore" />
				</td>
				<td>
				属性1>属性2
			</td>
			</tr>
			<tr>
			<td>结果显示<td>
			<td>
				<input type="text" name="resultLess" />
				</td>
				<td>
				属性1<属性2
			</td>
			</tr>
			<tr>
			<td>差值属性<td>
			<td>
				<input type="hidden" name="reducePropID" />
			    <input type="text" name="reducePropName" readonly="readonly" />
				</td>
				<td>
				<button type="button" onclick="selectProperty(document.getElementById('compareCategoryID').value,document.getElementById('reducePropID'),document.getElementById('reducePropName'))">选择...</button>
			</td>
			</tr>
			<tr>
			<td>刷新间隔(小时)<td>
			<td>
			<input type="text" name="time" />
				</td>
				<td>
				
			</td>
			</tr>
			</table>
				</div>
			</fieldset>
			</form>
			<div id="toolbar">
		    <button type="button" onclick="ok()" id="btnOK">确定</button>
		    <button type="button" onclick="window.close()" id="btnCancel">取消</button>
			</div>
			</td>
		</tr>
</table>
</body>
</html>
