package com.fulong.portlet.component.file.selector;

import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import com.fulong.portlet.PortletRender;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionForm;

/**
 * 文件选择表单域占位符
 * 
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
 * @author lichengzhao
 * @version 3.1
 */
public class PreviewRender extends PortletRender {
	/**
	 * 
	 * @param mapping
	 *            ActionMapping
	 * @param form
	 *            ActionForm
	 * @param request
	 *            RenderRequest
	 * @param response
	 *            RenderResponse
	 * @return ActionForward
	 * @throws Exception
	 */
	public ActionForward render(ActionMapping mapping, ActionForm form, RenderRequest request, RenderResponse response)
			throws Exception {
		request.setAttribute("preferences", request.getPreferences());
		return mapping.findForward("success");
	}
}
