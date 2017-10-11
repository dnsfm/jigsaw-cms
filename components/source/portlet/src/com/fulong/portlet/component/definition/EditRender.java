package com.fulong.portlet.component.definition;

import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.fulong.longcon.repository.NodeDefinition;
import com.fulong.portlet.FormEditRender;

/**
 * 下拉框表单域占位符
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

	@Override
	public ActionForward formRender(NodeDefinition definition,
			ActionMapping mapping, ActionForm form, RenderRequest request,
			RenderResponse response) throws Exception {
		PortletPreferences preferences = request.getPreferences();
		//String definitionId = preferences.getValue("definitionId", NodeDefinition.NO_PROPERTIES_SCHEME);
		//NodeDefinition definition = this.getRepository().getDefinitionManager().getDefinition(definitionId);
		request.setAttribute("definition", definition);
		String categoryId = preferences.getValue("category", null);
		if (categoryId != null) {

			NodeDefinition category = this.getRepository().getDefinitionManager().getDefinition(categoryId);
			request.setAttribute("category", category);
		}
		return mapping.findForward("success");
	}
}