package com.fulong.portlet.validator.unique;

import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import com.fulong.longcon.repository.NodeDefinition;
import com.fulong.portlet.FormEditRender;

/**
 *文本域占位符
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
 * @author lixf
 * @version 3.1
 */
public class EditRender extends FormEditRender {
	/**
	 * execute
	 * 
	 * @param request
	 *            RenderRequest
	 * @param response
	 *            RenderResponse
	 * @throws Exception
	 */
	public ActionForward formRender(NodeDefinition definition, ActionMapping mapping, ActionForm form, RenderRequest request, RenderResponse response) throws Exception {
		PortletPreferences preferences = request.getPreferences();
		NodeDefinition category = lookUpDefinition(request);
		request.getPreferences().setValue("category", category.getID());
		request.setAttribute("category", category);
		preferences.setValue("category", category.getID());

		request.setAttribute("properties", definition.propertyDefinitions());
		request.setAttribute("preferences", request.getPreferences());
		return mapping.findForward("success");
	}
}
