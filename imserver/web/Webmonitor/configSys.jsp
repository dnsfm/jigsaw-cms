<%@page contentType="text/html; charset=gb2312"%>
<%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@taglib uri="/WEB-INF/struts-tiles.tld" prefix="tiles"%>

<html:html locale="true">
<head>
<html:base />
<title>��Ƶ�����̨����ϵͳ</title>

<style type="text/css">
body {
	margin: 10px;
	font-size: 14px;
	font-family: ����;
}

a {
	color: #F00;
}

.clear {
	clear: both;
}

dhtmlgoodies_aTab input,dhtmlgoodies_aTab textarea {
	background-color: #ffffff;
	border-left: 0px;
	border-right: 0px;
	border-top: 0px;
	border-bottom: 1px solid #000000;
	margin: 6px;
}

input button {
	border-left: 1px solid #000000;
	border-right: 1px solid #000000;
	border-top: 1px solid #000000;
	border-bottom: 1px solid #000000;
}

.a3 {
	width: 30px;
	border: 0px;
	text-align: center;
}

.commonbut {
	background-image: url(images/sub.gif);
	width: 70px;
	height: 23px;
	padding-left: 18px;
	border: 0px;
	letter-spacing: 6px;
	cursor: hand;
}

.label {
	font-size: 13px;
	font-style: normal;
	font-weight: bolder;
	color: #00008B;
	padding-left: 0px;
}

.helptext {
	font-size: 12px;
	font-style: normal;
	color: #000000;
	padding-left: 20px;
}
</style>
<link rel="stylesheet" href="<html:rewrite page='/css/tab-view.css'/>"
	type="text/css" media="screen">
<link rel="stylesheet" href="<html:rewrite page='/css/calendar.css'/>"
	type="text/css" media="screen">
<script type="text/javascript"
	src="<html:rewrite page='/scripts/ajax2.js'/>"></script>
<script type="text/javascript"
	src="<html:rewrite page='/scripts/tab-view.js'/>"></script>
<script type="text/javascript"
	src="<html:rewrite page='/scripts/calendar.js'/>"></script>
</head>

<body>
<html:form action="getSystemConfig.do" method="post">
	<div id="tabView">
	<div class="dhtmlgoodies_aTab" style="height: 360px; background: url(images/bgfu.gif);">
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 75%">
		<tr valign="top">
			<td width="100px"><div class="label">��վ���⣺</div></td>
			<td align="left"><html:text property="systemTitle" maxlength="32" size="30" /></td>
		</tr>
		<tr valign="top">
			<td colspan="2" align="center"><input type="submit"
				onclick="this.form.action='<html:rewrite page="/modifySystemTitle.do"/>'; window.parent.location.reload()"
				value="�ύ" class="commonbut" /></td>
		</tr>
		<tr valign="top" height="*">
			<td height="*">&nbsp;</td><td></td>
		</tr>
	</table>
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 25%">
		<tr valign="bottom">
			<td colspan="2" align="left">
			<div class="label">˵����</div>
			</td>
		</tr>
		<tr valign="bottom" height="6">
			<td colspan="2" height="6" align="right" background="images/fgx.gif"
				style="background-repeat: no-repeat;" /></td>
		</tr>
		<tr valign="bottom">
			<td colspan="2" align="left"><div class="helptext">�����뱾������վ�����ƣ������ƽ���ʾ�ڱ���վ����ҳ��Ķ�����</div></td>
		</tr>
	</table>
	</div>
	<div class="dhtmlgoodies_aTab" style="height: 360px; background: url(images/bgfu.gif);">
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 75%">
		<logic:present name="ModiNetResult">
		<tr>
			<td colspan="2">
				<font color="red"><bean:write name="ModiNetResult" /></font>
			</td>
		</tr>
		</logic:present>
		<tr>
			<td width="100px"><div class="label">IP ��ַ��</div></td>
			<td>
			<div style="border-width: 1; border-color: balck; border-style: solid; width: 165; font-size: 9pt">
			<input name="ip1" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='ip1'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="ip2" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='ip2'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="ip3" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='ip3'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="ip4" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='ip4'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />
			</div>
			</td>
		</tr>
		<tr>
			<td><div class="label">�������룺</div></td>
			<td>
			<div style="border-width: 1; border-color: balck; border-style: solid; width: 165; font-size: 9pt">
			<input name="mask1" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='mask1'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="mask2" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='mask2'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="mask3" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='mask3'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="mask4" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='mask4'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />
			</div>
			</td>
		</tr>
		<tr>
			<td><div class="label">�� �أ�</div></td>
			<td>
			<div style="border-width: 1; border-color: balck; border-style: solid; width: 165; font-size: 9pt">
			<input name="gateway1" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='gateway1'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="gateway2" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='gateway2'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="gateway3" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='gateway3'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="gateway4" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='gateway4'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />
			</div>
			</td>
		</tr>
		<tr>
			<td><div class="label">DNS��������</div></td>
			<td>
			<div style="border-width: 1; border-color: balck; border-style: solid; width: 165; font-size: 9pt">
			<input name="dns1" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='dns1'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="dns2" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='dns2'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="dns3" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='dns1'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />.
			<input name="dns4" maxlength="3" class="a3" value="<bean:write name="SystemConfigForm" property='dns1'/>"
				onKeyDown="checkIPValid_1()" onKeyUp="checkIPValid_2(this)" />
			</div>
			</td>
		</tr>
		<tr>
			<td colspan="2" align="center">
			<button type="submit"
				onclick="return checknet(this.form);"
				class="commonbut">�ύ</button>
			</td>
		</tr>
		<tr valign="top" height="*">
			<td height="*">&nbsp;</td><td></td>
		</tr>
	</table>
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 25%">
		<tr valign="bottom">
			<td colspan="2" align="left">
			<div class="label">˵����</div>
			</td>
		</tr>
		<tr valign="bottom" height="6">
			<td colspan="2" height="6" align="right" background="images/fgx.gif"
				style="background-repeat: no-repeat;" /></td>
		</tr>
		<tr valign="bottom">
			<td colspan="2" align="left"><div class="helptext">������������������������Ƶ�������������ַ��</div></td>
		</tr>
	</table>

	</div>
	<div class="dhtmlgoodies_aTab" style="height: 360px; background: url(images/bgfu.gif);">
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 75%">
		<logic:present name="changePassOk">
		<tr>
			<td colspan="2">
				<font color="red"><bean:write name="changePassOk" /></font>
			</td>
		</tr>
		</logic:present>

		<tr>
			<td width="100px"><div class="label">�����룺</div></td>
			<td><html:password property="oldPassword" size="19"
				maxlength="16" />
				<logic:present name="invaildPassword">
					<font color="red"><bean:write name="invaildPassword" /></font>
				</logic:present>
			</td>
		</tr>

		<tr>
			<td><div class="label">�����룺</div></td>
			<td><html:password property="newPassword" size="19"
				maxlength="16" /></td>
		</tr>
		<tr>
			<td><div class="label">ȷ�������룺</div></td>
			<td><html:password property="confirmPassword" size="19"
				maxlength="16" /></td>
		</tr>
		<tr>
			<td colspan="2" align="center">
			<button type="submit" onclick="return check(this.form);"
				class="commonbut">�޸�</button>
			<logic:present name="passwordUpdated">
				<font color="#00FF99"><bean:write name="passwordUpdated" /></font>
			</logic:present></td>
		</tr>
		<tr valign="top" height="*">
			<td height="*">&nbsp;</td><td></td>
		</tr>
	</table>
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 25%">
		<tr valign="bottom">
			<td colspan="2" align="left">
			<div class="label">˵����</div>
			</td>
		</tr>
		<tr valign="bottom" height="6">
			<td colspan="2" height="6" align="right" background="images/fgx.gif"
				style="background-repeat: no-repeat;" /></td>
		</tr>
		<tr valign="bottom">
			<td colspan="2" align="left"><div class="helptext">�޸ķ��ʱ���վ�Ĺ���Ա���롣</div></td>
		</tr>
	</table>

	</div>
	<div class="dhtmlgoodies_aTab" style="height: 360px; background: url(images/bgfu.gif);">
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 75%">
		<logic:present scope="request" name="backup">
		<tr valign="top">
			<td colspan="2" align="left">
			<div class="label"><bean:write name="backup"/></div>
			</td>
		</tr>
		</logic:present>
		<tr valign="top">
			<td colspan="2" align="left">
			<div class="label"><bean:write name="SystemConfigForm" property="lastBackupInfo"/></div>
			</td>
		</tr>
		<tr>
			<td align="center">
			<button type="submit" class="commonbut"
				onclick="this.form.action='<html:rewrite page="/backupDatabase.do"/>'">����</button>
			</td>
		</tr>
		<tr>
			<td align="center">
			<button type="submit" class="commonbut"
				onclick="this.form.action='<html:rewrite page="/restoreDatabase.do"/>'">�ָ�</button>
			</td>
		</tr>
		<tr valign="top" height="*">
			<td height="*">&nbsp;</td><td></td>
		</tr>
	</table>
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 25%">
		<tr valign="bottom">
			<td colspan="2" align="left">
			<div class="label">˵����</div>
			</td>
		</tr>
		<tr valign="bottom" height="6">
			<td colspan="2" height="6" align="right" background="images/fgx.gif"
				style="background-repeat: no-repeat;" /></td>
		</tr>
		<tr valign="bottom">
			<td colspan="2" align="left"><div class="helptext">���õı���ϰ�ߣ��ܹ�������δȻ��</div></td>
		</tr>
	</table>

	</div>
	<div class="dhtmlgoodies_aTab" style="height: 360px; background: url(images/bgfu.gif);">
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 75%">
		<logic:equal scope="session" name="ServerInfo" property="state"	value="1">
			<tr>
				<td><div class="label">ϵͳ��<bean:write scope="session" name="ServerInfo"
					property="startTime" />��ʼ����</div></td>
			</tr>
			<tr>
				<td align="center">
				<button type="submit" class="commonbut"
					onclick="this.form.action='<html:rewrite page="/stopServer.do"/>'">ֹͣ</button>
				<!--\u00A0\u00A0<button class="commonbut2" >�鿴��־</button>--></td>
			</tr>
		</logic:equal>
		<logic:equal scope="session" name="ServerInfo" property="state"	value="0">
			<tr>
				<td><div class="label">ϵͳֹͣ��<font color="#FF0000"><bean:write
					scope="session" name="ServerInfo" property="stopTime" /></font></div></td>
			</tr>
			<tr>
				<td>
				<button type="submit" class="commonbut1"
					onclick="this.form.action='<html:rewrite page="/startServer.do"/>'">����</button>
				<!--\u00A0\u00A0<button class="commonbut2" >�鿴��־</button>--></td>
			</tr>
		</logic:equal>
		<tr valign="top" height="*">
			<td height="*">&nbsp;</td><td></td>
		</tr>
	</table>
	<table width="100%" border="0" cellpadding="4" cellspacing="2" style="height: 25%">
		<tr valign="bottom">
			<td colspan="2" align="left">
			<div class="label">˵����</div>
			</td>
		</tr>
		<tr valign="bottom" height="6">
			<td colspan="2" height="6" align="right" background="images/fgx.gif"
				style="background-repeat: no-repeat;" /></td>
		</tr>
		<tr valign="bottom">
			<td colspan="2" align="left"><div class="helptext">�鿴�͸ı���Ƶ������������״̬��</div></td>
		</tr>
	</table>

	</div>
	</div>
</html:form>
<script language="javascript">
{
	// ��ʼ��Tabҳ�棬���δָ��Tab�ţ�����ʾ��һҳ
	var strictDocType = false;
	var page=<%=request.getParameter("page")%>
	if(page==null)
	{
		page=0;
	}
	initTabs('tabView',Array('��վ����','��������','�����޸�','���ݱ���','ϵͳ״̬'),page,'560','320');
}
</script>
<script>
// IP��ַ���뺯��
function checkIPValid_1()
{
	if(event.shiftKey)
	{
		event.returnValue=false;
		return;
	}
	var keyCode = parseInt(event.keyCode);
	var result=true;
	if((keyCode==8) || (keyCode==37) || (keyCode==39) || (keyCode==9)) return;

	if((keyCode>=48) && (keyCode<=57)) return;
	else result=false;
	if((keyCode>=96) && (keyCode<=105)) return;
	else result=false;

	if((keyCode==110) || (keyCode==190) || (keyCode==32))
	{
		event.keyCode=9;
		return;
	}
	if(result==false) event.returnValue=false;
}

function checkIPValid_2(mask)
{

	if(typeof(mask) != 'object'){
		mask = eval(mask)
	}
	var maskInt=parseInt(mask.value);
	if((maskInt<0) || (maskInt>255))
	{
		mask.value=255;
		alert(maskInt+"���Ǹ���ЧIP��ַ����ָ��һ������0��255֮�����ֵ");
	}
}

function check(form){
	if(form.newPassword.value!=form.confirmPassword.value){
		alert("������������ȷ�����벻һ��,����������");
		return false;
	}
	form.action='<html:rewrite page="/modifyPassword.do"/>';
}

function checknet(form){
	form.action='<html:rewrite page="/modifyNet.do"/>';
	if(document.getElementsByName("ip1")[0].value.length==0) {alert("IP������д����");return false;}
	if(document.getElementsByName("ip2")[0].value.length==0) {alert("IP������д����");return false;}
	if(document.getElementsByName("ip3")[0].value.length==0) {alert("IP������д����");return false;}
	if(document.getElementsByName("ip4")[0].value.length==0) {alert("IP������д����");return false;}
	if(document.getElementsByName("mask1")[0].value.length==0) {alert("����������д����");return false;}
	if(document.getElementsByName("mask2")[0].value.length==0) {alert("����������д����");return false;}
	if(document.getElementsByName("mask3")[0].value.length==0) {alert("����������д����");return false;}
	if(document.getElementsByName("mask4")[0].value.length==0) {alert("����������д����");return false;}
	if(document.getElementsByName("gateway1")[0].value.length==0) {alert("����������д����");return false;}
	if(document.getElementsByName("gateway2")[0].value.length==0) {alert("����������д����");return false;}
	if(document.getElementsByName("gateway3")[0].value.length==0) {alert("����������д����");return false;}
	if(document.getElementsByName("gateway4")[0].value.length==0) {alert("����������д����");return false;}
	if(document.getElementsByName("dns1")[0].value.length==0) {alert("DNS������д����");return false;}
	if(document.getElementsByName("dns2")[0].value.length==0) {alert("DNS������д����");return false;}
	if(document.getElementsByName("dns3")[0].value.length==0) {alert("DNS������д����");return false;}
	if(document.getElementsByName("dns4")[0].value.length==0) {alert("DNS������д����");return false;}
}

</script>

</body>
<!-- html:javascript formName="SystemConfigForm" staticJavascript="true" -->
</html:html>
