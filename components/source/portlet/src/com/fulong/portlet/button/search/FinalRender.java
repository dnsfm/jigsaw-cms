package com.fulong.portlet.button.search;

import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import com.fulong.portlet.PortletRender;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionForm;
import com.fulong.longcon.site.SiteTemplate;
import com.fulong.longcon.site.Channel;

/**
 * 保存按钮Final状态
 * 
 * <p>
 * Title: 龙驭门户引擎
 * </p>
 * 
 * <p>
 * Description: 龙驭网站内容管理系统核心引擎
 * </p>
 * 
 * <p>
 * Copyright: 北京中科辅龙计算机技术股份有限公司
 * </p>
 * 
 * <p>
 * Company: 北京中科辅龙计算机技术股份有限公司
 * </p>
 * 
 * @author Lixf
 * @version 1.0
 */
public class FinalRender extends PortletRender {
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
		String channel = request.getPreferences().getValue("channel", "");
		SiteTemplate template = this.getCurrentSiteTemplate(request, response);
		Channel aChannel = template.getChannel(channel);
		if (aChannel == null) {
			aChannel = this.getCurrentChannel(request, response);
		}
		request.setAttribute("channel", aChannel);
		request.setAttribute("preferences", request.getPreferences());
		return mapping.findForward("success");
	}

}