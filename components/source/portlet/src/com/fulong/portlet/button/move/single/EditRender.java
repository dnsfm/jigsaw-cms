package com.fulong.portlet.button.move.single;

import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.fulong.longcon.site.Channel;
import com.fulong.longcon.site.SiteTemplate;
import com.fulong.portlet.PortletRender;

/**
 * <p>
 * Title: 龙驭网站内容管理系统核心引擎
 * </p>
 * 
 * <p>
 * Description: 龙驭网站内容管理系统核心引擎
 * </p>
 * 
 * <p>
 * Copyright: 北京中科辅龙计算机技术有限公司 2006
 * </p>
 * 
 * <p>
 * Company: 北京中科辅龙计算机技术有限公司
 * </p>
 * 
 * @author jiangqi
 * @version 2.0
 */
public class EditRender extends PortletRender {
	/**
	 * execute
	 * 
	 * @param request
	 *            RenderRequest
	 * @param response
	 *            RenderResponse
	 * @throws Exception
	 */
	public ActionForward render(ActionMapping mapping, ActionForm form, RenderRequest request, RenderResponse response)
			throws Exception {
		//request.setAttribute("categorys", this.lookUpDefinition(request));
		SiteTemplate template = null;
		Channel channel = null;
		String channelPath = request.getPreferences().getValue("channel", "");
		if(channelPath!=null&&!channelPath.equals("")&&channelPath.indexOf("/")>=0){
			template = this.parseTemplate(channelPath);
			channel = this.parseChannel(channelPath);
		}else{
			template = this.getCurrentSiteTemplate(request, response);
		}
		String categorys = request.getPreferences().getValue("categorys", "");
		if(categorys == null || categorys.length()<=0 || categorys == "" ){
			request.setAttribute("categorys", this.lookUpDefinition(request));
		}else{
			request.setAttribute("categorys", this.getRepository().getDefinitionManager()
					.getDefinition(categorys));
		}
		request.setAttribute("channel", channel);
		request.setAttribute("siteTemplate", template);

		return mapping.findForward("success");
	}
}