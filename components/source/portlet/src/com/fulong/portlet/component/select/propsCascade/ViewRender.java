package com.fulong.portlet.component.select.propsCascade;

import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import com.fulong.portlet.PortletRender;

/**
 * <p>Title: Coolink平台协同管理系统</p>
 *
 * <p>Description: Coolink平台协同管理系统</p>
 *
 * <p>Copyright: 北京中科辅龙计算机技术股份有限公司 2010</p>
 *
 * <p>Company: 北京中科辅龙计算机技术股份有限公司</p>
 *
 * @author luobin
 * @date 2010-9-8	
 * @version 1.0.1
 */
public class ViewRender extends PortletRender {

	public ActionForward render(ActionMapping mapping, ActionForm form, RenderRequest request, RenderResponse response)
			throws Exception {
		request.setAttribute("preferences", request.getPreferences());
		return mapping.findForward("success");
	}
}