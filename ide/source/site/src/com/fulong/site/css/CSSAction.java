package com.fulong.site.css;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * Show the content of the css file.
 * <p>Title: WebMaster Core Library</p>
 *
 * <p>Description: Longcon WebMaster SV3</p>
 *
 * <p>Copyright: Copyright (c) 2005</p>
 *
 * <p>Company: Beijing Zhongke Fulong Computer Tech. LTD</p>
 *
 * @author Lixf
 * @version 1.0
 */
public class CSSAction extends CSSBaseAction {

    /**
     * cssPerform
     *
     * @param mapping ActionMapping
     * @param form ActionForm
     * @param request HttpServletRequest
     * @param response HttpServletResponse
     * @return ActionForward
     * @throws Exception
     * @todo Implement this com.fulong.cms.site.css.CSSBaseAction method
     */
    public ActionForward cssPerform(ActionMapping mapping, ActionForm form,
                                    HttpServletRequest request,
                                    HttpServletResponse response) throws
            Exception {
        /*
          String id=request.getParameter("id");
          StyleSheet styleSheet=this
                                .getCSSRepository(request,response)
                                .getCSS(id);
          CSSRuleList cssRuleList=styleSheet.getCSSRules();
          CSSRulelistIterator iterator=new CSSRulelistIterator(cssRuleList);
          request.setAttribute("css", styleSheet);
          request.setAttribute("cssRuleList",iterator);
         */
        return mapping.findForward("success");
    }
}
