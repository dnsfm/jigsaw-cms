<%@page contentType="text/html; charset=GBK"%>
<%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@taglib uri="/WEB-INF/struts-tiles.tld" prefix="tiles"%>

<html>
<head>
<meta http-equiv="refresh" content="10;GetAllUserInfo.do" />
<title>��Ƶ�����̨����ϵͳ</title>

<script type="text/javascript">
function selectUser(string) {
	window.open("getDetail.do?"+string);
}
function checkPage(form,totalPageNum){
  if(form.targetPage.value > totalPageNum){
	alert('ָ����ҳ��������');
	form.targetPage.value = '';
	return false;
  }
  return true;
}
</script>
<link href="css/stylejq.css" rel="stylesheet" type="text/css" />

</head>

<body>
<form name="getAllUser" method="POST"
	action="<html:rewrite page="/GetAllUserInfo.do?act=goto"/>">
<table bgcolor="#FFFFFF" width="100%" border="0" cellspacing="0"
	cellpadding="0">
	<tr>
		<td valign="top" height="440px" width="100%">
		<table width="98%" border="1" align="center" cellpadding="2"
			cellspacing="0" bordercolorlight="#CCCCCC" bordercolordark="#FFFFFF">
			<tr>
				<th bgcolor="#d1e3fb" width="40%">�� ��</th>
				<th bgcolor="#d1e3fb">��¼ʱ��</th>
			</tr>
			<logic:iterate name="UserInfo" id="user" indexId="index">
				<tr onmouseover="this.bgColor='#dcf0f9'">
					<td align="center"><bean:write name="user" property="lastname" /><bean:write
						name="user" property="firstname" /></td>
					<td align="center"><bean:write name="user"
						property="entertime" /></td>
				</tr>
			</logic:iterate>
		</table>
		</td>
	</tr>
	<tr>
		<td>
		<table cellpadding="1" cellspacing="0">
			<tfoot>
				<tr>
					<td align="right" colspan="10"><span style="font-size: 12px;">
					�ܹ�<bean:write name="totalNum" />����¼ ��ǰΪ<bean:write name="curPage" />/<bean:write
						name="totalPage" />ҳ <logic:greaterThan name="curPage" value="1">
						��<a href="<html:rewrite page="/GetAllUserInfo.do"/>?act=first">��ҳ</a>��
						<a
							href="<html:rewrite page="/GetAllUserInfo.do"/>?act=pre&curPage=<bean:write name="curPage"/>">��һҳ</a>
					</logic:greaterThan>
					<%if (Integer.parseInt((String) request.getAttribute("curPage")) < Integer.parseInt((String) request.getAttribute("totalPage"))) { %>
					��<a href="<html:rewrite page="/GetAllUserInfo.do"/>?act=next&curPage=<bean:write name="curPage"/>">��һҳ</a>
					��<a href="<html:rewrite page="/GetAllUserInfo.do"/>?act=last">ĩҳ</a>
					<%}%>
					��ת�� <input size="1" name="targetPage" /> <input type="submit"
						id="go" onclick="return checkPage(this.form,<bean:write name="totalPage"/>);"
						value="��ת" /> </span>
					</td>
				</tr>
			</tfoot>
		</table>
		</td>
	</tr>
</table>


</form>
</body>
</html>
