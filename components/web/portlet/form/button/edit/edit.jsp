<%@ page contentType="text/html; charset=UTF-8" %>
<%@taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@taglib uri="/WEB-INF/fulong.tld" prefix="fulong"%>
<%@taglib uri="/WEB-INF/fulong-portal.tld" prefix="portlet"%>
<table cellpadding="0" cellspacing="0" border="0">
    <portlet:form action="save" method="POST" onsubmit="doSubmit(this)">
        <tr>
            <td class="pannelDiv" rowspan="2">
                <select id="pannelSelect" name="pannelSelect" onchange="selectPanel(this)" size="10">
                    <option value="0" selected="selected">基本设置</option>
                    <option value="1">图片按钮</option>
                </select></td>
                <td><fieldset>
                    <table width="100%" cellpadding="2" cellspacing="2" border="0" class="formTable">
                        <tr>
                            <td class="formTitle">按钮名称</td>
                            <td class="formComponent"><html:text property="preference(value)"/> </td>
                        </tr>
                        <tr>
                            <td class="formTitle">样式</td>
                            <td class="formComponent">
                                <html:text property="preference(style)"/>
                                <button type="button" class="commonbut" onclick="doSelectStyle(this.form.elements['preference(style)'],'')">选择...</button>
                            </td>
                        </tr>
                        <tr>
                            <td class="formTitle">跳转到</td>
                            <td class="formComponent">
			                      <html:hidden property="preference(channel)"/>
			                      <input type="text" name="channelName" <logic:notEmpty name="channel">value="<bean:write name="siteTemplate" property="displayName" ignore="true"/>.<bean:write name="channel" property="displayName" ignore="true"/>"</logic:notEmpty>/><button type="button" class="commonbut" onclick="chooseColumn('<bean:write name="siteTemplate" property="name"/>',this.form.elements['preference(channel)'],this.form.elements['channelName'])">选择...</button>
	                  		</td>
                        </tr>
                        <tr>
              				<td class="formTitle"></td>
              				<td class="formComponent">
                				<html:checkbox style="width:25px" property="preference(openInNewWindow)">在新窗口打开</html:checkbox>
              				</td>
            			</tr>
            			<tr>
              				<td class="formTitle"></td>
              				<td class="formComponent">
                				<html:checkbox style="width:25px" property="preference(showHref)">以超链接展示</html:checkbox>
              				</td>
            			</tr>
                    </table>
                </fieldset>
                <fieldset style="display:none">
                  <table width="100%" cellpadding="2" cellspacing="2" border="0" class="formTable">
                        <tr>
                            <td class="formTitle">图片地址</td>
                            <td class="formComponent"><html:text property="preference(imgsrc)"/><button type="button" class="commonbut" onclick="openSelectorFileSelector(this.form['preference(imgsrc)']);">选择...</button> </td>
                          </tr>
                        <tr>
                            <td class="formTitle">图片高度</td>
                            <td class="formComponent">
                                <html:text property="preference(imgheight)"/>
                            </td>
                        </tr>
                        <tr>
                            <td class="formTitle">图片宽度</td>
                            <td class="formComponent">
                                <html:text property="preference(imgwidth)"/>
                            </td>
                        </tr>
                        <tr>
                            <td class="formTitle">图片样式</td>
                            <td class="formComponent">
                                <html:text property="preference(imgstyle)"/>
                                <button type="button" class="commonbut" onclick="doSelectStyle(this.form.elements['preference(imgstyle)'],'')">选择...</button>
                            </td>
                        </tr>
                        <tr>
                            <td class="formTitle">文字提示</td>
                            <td class="formComponent"><html:text property="preference(imgtitle)"/></td>
                        </tr>
                    </table>
                </fieldset>
                <div class="toolbar">
          		<button type="button" onclick="validatorRequired(new Array(form.elements['preference(channel)']),new Array('导航'),this.form)">保存</button>
          		<button type="button" onclick="window.parent.close()">取消</button></div></td>
                </tr></portlet:form>
            </table>
            <script language="javascript" src="/ide/common/script/portlet.js" type="text/javascript" ></script>
            <script type="text/javascript" language="javascript">
            function doSubmit(oForm){
              return true;
            }
            function openSelectorFileSelector($oEcho)
            {
              var templateID = window.parent.dialogArguments.template.ID;
              var url = "/ide/site/resource/index.do?templateID="+templateID;
              var sOptions = "dialogHeight=600px;dialogWidth=780px;center=yes;resizable=no;status=no";
              var ret = window.showModalDialog(url, null, sOptions);
              if (ret != null && ret[0])
              $oEcho.value = ret[0];
            }
            </script>