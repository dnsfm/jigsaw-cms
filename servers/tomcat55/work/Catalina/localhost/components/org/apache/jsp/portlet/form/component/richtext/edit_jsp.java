package org.apache.jsp.portlet.form.component.richtext;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;

public final class edit_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {

  private static java.util.List _jspx_dependants;

  static {
    _jspx_dependants = new java.util.ArrayList(4);
    _jspx_dependants.add("/WEB-INF/struts-html.tld");
    _jspx_dependants.add("/WEB-INF/struts-bean.tld");
    _jspx_dependants.add("/WEB-INF/struts-logic.tld");
    _jspx_dependants.add("/WEB-INF/fulong-portal.tld");
  }

  private org.apache.jasper.runtime.TagHandlerPool _005fjspx_005ftagPool_005fportlet_005fform_0026_005fmethod_005faction;
  private org.apache.jasper.runtime.TagHandlerPool _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fname_005fignore_005fnobody;
  private org.apache.jasper.runtime.TagHandlerPool _005fjspx_005ftagPool_005fhtml_005fhidden_0026_005fproperty_005fnobody;
  private org.apache.jasper.runtime.TagHandlerPool _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fproperty_005fname_005fignore_005fnobody;
  private org.apache.jasper.runtime.TagHandlerPool _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody;
  private org.apache.jasper.runtime.TagHandlerPool _005fjspx_005ftagPool_005fhtml_005frewrite_0026_005fpage_005fmodule_005fnobody;

  public Object getDependants() {
    return _jspx_dependants;
  }

  public void _jspInit() {
    _005fjspx_005ftagPool_005fportlet_005fform_0026_005fmethod_005faction = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fname_005fignore_005fnobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _005fjspx_005ftagPool_005fhtml_005fhidden_0026_005fproperty_005fnobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fproperty_005fname_005fignore_005fnobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _005fjspx_005ftagPool_005fhtml_005frewrite_0026_005fpage_005fmodule_005fnobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
  }

  public void _jspDestroy() {
    _005fjspx_005ftagPool_005fportlet_005fform_0026_005fmethod_005faction.release();
    _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fname_005fignore_005fnobody.release();
    _005fjspx_005ftagPool_005fhtml_005fhidden_0026_005fproperty_005fnobody.release();
    _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fproperty_005fname_005fignore_005fnobody.release();
    _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.release();
    _005fjspx_005ftagPool_005fhtml_005frewrite_0026_005fpage_005fmodule_005fnobody.release();
  }

  public void _jspService(HttpServletRequest request, HttpServletResponse response)
        throws java.io.IOException, ServletException {

    JspFactory _jspxFactory = null;
    PageContext pageContext = null;
    HttpSession session = null;
    ServletContext application = null;
    ServletConfig config = null;
    JspWriter out = null;
    Object page = this;
    JspWriter _jspx_out = null;
    PageContext _jspx_page_context = null;


    try {
      _jspxFactory = JspFactory.getDefaultFactory();
      response.setContentType("text/html; charset=UTF-8");
      pageContext = _jspxFactory.getPageContext(this, request, response,
      			null, true, 8192, true);
      _jspx_page_context = pageContext;
      application = pageContext.getServletContext();
      config = pageContext.getServletConfig();
      session = pageContext.getSession();
      out = pageContext.getOut();
      _jspx_out = out;

      out.write("<table cellpadding=\"0\" cellspacing=\"0\" border=\"0\">\r\n");
      out.write("  ");
      if (_jspx_meth_portlet_005fform_005f0(_jspx_page_context))
        return;
      out.write("</table>\r\n");
      out.write("<script language=\"javascript\" src=\"");
      if (_jspx_meth_html_005frewrite_005f0(_jspx_page_context))
        return;
      out.write("\" type=\"text/javascript\" ></script>\r\n");
      out.write("<script type=\"text/javascript\" language=\"javascript\">\r\n");
      out.write("  /**\r\n");
      out.write("  *选择待显示的属性\r\n");
      out.write("  */\r\n");
      out.write("  function searchPropertyDefinition($categoryId){\r\n");
      out.write("    var arr = CMSDialog.PropertyDefinitionSelector($categoryId);\r\n");
      out.write("    if(arr!=null){\r\n");
      out.write("      document.getElementById(\"fieldName\").value = arr.name;\r\n");
      out.write("      document.getElementById(\"preference(propertyId)\").value = arr.ID;\r\n");
      out.write("    }\r\n");
      out.write("  }\r\n");
      out.write("</script>\r\n");
    } catch (Throwable t) {
      if (!(t instanceof SkipPageException)){
        out = _jspx_out;
        if (out != null && out.getBufferSize() != 0)
          out.clearBuffer();
        if (_jspx_page_context != null) _jspx_page_context.handlePageException(t);
      }
    } finally {
      if (_jspxFactory != null) _jspxFactory.releasePageContext(_jspx_page_context);
    }
  }

  private boolean _jspx_meth_portlet_005fform_005f0(PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  portlet:form
    com.fulong.taglib.portal.PortletFormTag _jspx_th_portlet_005fform_005f0 = (com.fulong.taglib.portal.PortletFormTag) _005fjspx_005ftagPool_005fportlet_005fform_0026_005fmethod_005faction.get(com.fulong.taglib.portal.PortletFormTag.class);
    _jspx_th_portlet_005fform_005f0.setPageContext(_jspx_page_context);
    _jspx_th_portlet_005fform_005f0.setParent(null);
    _jspx_th_portlet_005fform_005f0.setAction("save");
    _jspx_th_portlet_005fform_005f0.setMethod("POST");
    int _jspx_eval_portlet_005fform_005f0 = _jspx_th_portlet_005fform_005f0.doStartTag();
    if (_jspx_eval_portlet_005fform_005f0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
      do {
        out.write("<tr>\r\n");
        out.write("      <td class=\"pannelDiv\" rowspan=\"2\">\r\n");
        out.write("        <select id=\"pannelSelect\" name=\"pannelSelect\" onchange=\"selectPanel(this)\" size=\"10\">\r\n");
        out.write("          <option value=\"0\" selected=\"selected\">基本设置</option>\r\n");
        out.write("        </select>\r\n");
        out.write("      </td>\r\n");
        out.write("      <td>\r\n");
        out.write("        <fieldset>\r\n");
        out.write("          <table width=\"100%\" cellpadding=\"2\" cellspacing=\"2\" border=\"0\" class=\"formTable\">\r\n");
        out.write("            <tr>\r\n");
        out.write("              <td class=\"formTitle\">属性</td>\r\n");
        out.write("              <td class=\"formComponent\">\r\n");
        out.write("                <input name=\"preference(category-id)\" type=\"hidden\" value=\"");
        if (_jspx_meth_bean_005fwrite_005f0(_jspx_th_portlet_005fform_005f0, _jspx_page_context))
          return true;
        out.write("\" />\r\n");
        out.write("                ");
        if (_jspx_meth_html_005fhidden_005f0(_jspx_th_portlet_005fform_005f0, _jspx_page_context))
          return true;
        out.write("<input type=\"text\" name=\"fieldName\" readonly=\"readonly\" value=\"");
        if (_jspx_meth_bean_005fwrite_005f1(_jspx_th_portlet_005fform_005f0, _jspx_page_context))
          return true;
        out.write("\" />\r\n");
        out.write("                <button class=\"commonbut\" id=\"search\" onclick=\"searchPropertyDefinition('");
        if (_jspx_meth_bean_005fwrite_005f2(_jspx_th_portlet_005fform_005f0, _jspx_page_context))
          return true;
        out.write("')\">选择...</button>\r\n");
        out.write("              </td>\r\n");
        out.write("            </tr>\r\n");
        out.write("            <tr>\r\n");
        out.write("              <td class=\"formTitle\">宽度</td>\r\n");
        out.write("              <td class=\"formComponent\">");
        if (_jspx_meth_html_005ftext_005f0(_jspx_th_portlet_005fform_005f0, _jspx_page_context))
          return true;
        out.write("</td>\r\n");
        out.write("            </tr>\r\n");
        out.write("            <tr>\r\n");
        out.write("              <td class=\"formTitle\">高度</td>\r\n");
        out.write("              <td class=\"formComponent\">");
        if (_jspx_meth_html_005ftext_005f1(_jspx_th_portlet_005fform_005f0, _jspx_page_context))
          return true;
        out.write("</td>\r\n");
        out.write("            </tr>\r\n");
        out.write("            <tr>\r\n");
        out.write("              <td class=\"formTitle\">初始值</td>\r\n");
        out.write("              <td class=\"formComponent\">");
        if (_jspx_meth_html_005ftext_005f2(_jspx_th_portlet_005fform_005f0, _jspx_page_context))
          return true;
        out.write("</td>\r\n");
        out.write("            </tr>\r\n");
        out.write("            <tr>\r\n");
        out.write("              <td class=\"formTitle\">Tab键顺序</td>\r\n");
        out.write("              <td class=\"formComponent\">\r\n");
        out.write("                ");
        if (_jspx_meth_html_005ftext_005f3(_jspx_th_portlet_005fform_005f0, _jspx_page_context))
          return true;
        out.write("</td>\r\n");
        out.write("            </tr>\r\n");
        out.write("            <tr>\r\n");
        out.write("              <td class=\"formTitle\">样式</td>\r\n");
        out.write("              <td class=\"formComponent\">\r\n");
        out.write("                ");
        if (_jspx_meth_html_005ftext_005f4(_jspx_th_portlet_005fform_005f0, _jspx_page_context))
          return true;
        out.write("<button class=\"commonbut\" onclick=\"doSelectStyle(this.form.elements('preference(style)'),'')\">选择...</button>\r\n");
        out.write("              </td>\r\n");
        out.write("            </tr>\r\n");
        out.write("          </table>\r\n");
        out.write("        </fieldset>\r\n");
        out.write("        <div class=\"toolbar\">\r\n");
        out.write("          <button onclick=\"validatorRequired(new Array(form.elements('preference(propertyId)')),new Array('属性'),this.form)\">保存</button>\r\n");
        out.write("          <button onclick=\"window.close()\">取消</button>\r\n");
        out.write("        </div>\r\n");
        out.write("      </td>\r\n");
        out.write("    </tr>\r\n");
        out.write("  ");
        int evalDoAfterBody = _jspx_th_portlet_005fform_005f0.doAfterBody();
        if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
          break;
      } while (true);
    }
    if (_jspx_th_portlet_005fform_005f0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fportlet_005fform_0026_005fmethod_005faction.reuse(_jspx_th_portlet_005fform_005f0);
      return true;
    }
    _005fjspx_005ftagPool_005fportlet_005fform_0026_005fmethod_005faction.reuse(_jspx_th_portlet_005fform_005f0);
    return false;
  }

  private boolean _jspx_meth_bean_005fwrite_005f0(javax.servlet.jsp.tagext.JspTag _jspx_th_portlet_005fform_005f0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  bean:write
    org.apache.struts.taglib.bean.WriteTag _jspx_th_bean_005fwrite_005f0 = (org.apache.struts.taglib.bean.WriteTag) _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fname_005fignore_005fnobody.get(org.apache.struts.taglib.bean.WriteTag.class);
    _jspx_th_bean_005fwrite_005f0.setPageContext(_jspx_page_context);
    _jspx_th_bean_005fwrite_005f0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_portlet_005fform_005f0);
    _jspx_th_bean_005fwrite_005f0.setName("definition");
    _jspx_th_bean_005fwrite_005f0.setIgnore(true);
    int _jspx_eval_bean_005fwrite_005f0 = _jspx_th_bean_005fwrite_005f0.doStartTag();
    if (_jspx_th_bean_005fwrite_005f0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fname_005fignore_005fnobody.reuse(_jspx_th_bean_005fwrite_005f0);
      return true;
    }
    _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fname_005fignore_005fnobody.reuse(_jspx_th_bean_005fwrite_005f0);
    return false;
  }

  private boolean _jspx_meth_html_005fhidden_005f0(javax.servlet.jsp.tagext.JspTag _jspx_th_portlet_005fform_005f0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:hidden
    org.apache.struts.taglib.html.HiddenTag _jspx_th_html_005fhidden_005f0 = (org.apache.struts.taglib.html.HiddenTag) _005fjspx_005ftagPool_005fhtml_005fhidden_0026_005fproperty_005fnobody.get(org.apache.struts.taglib.html.HiddenTag.class);
    _jspx_th_html_005fhidden_005f0.setPageContext(_jspx_page_context);
    _jspx_th_html_005fhidden_005f0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_portlet_005fform_005f0);
    _jspx_th_html_005fhidden_005f0.setProperty("preference(propertyId)");
    int _jspx_eval_html_005fhidden_005f0 = _jspx_th_html_005fhidden_005f0.doStartTag();
    if (_jspx_th_html_005fhidden_005f0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fhtml_005fhidden_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005fhidden_005f0);
      return true;
    }
    _005fjspx_005ftagPool_005fhtml_005fhidden_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005fhidden_005f0);
    return false;
  }

  private boolean _jspx_meth_bean_005fwrite_005f1(javax.servlet.jsp.tagext.JspTag _jspx_th_portlet_005fform_005f0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  bean:write
    org.apache.struts.taglib.bean.WriteTag _jspx_th_bean_005fwrite_005f1 = (org.apache.struts.taglib.bean.WriteTag) _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fproperty_005fname_005fignore_005fnobody.get(org.apache.struts.taglib.bean.WriteTag.class);
    _jspx_th_bean_005fwrite_005f1.setPageContext(_jspx_page_context);
    _jspx_th_bean_005fwrite_005f1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_portlet_005fform_005f0);
    _jspx_th_bean_005fwrite_005f1.setName("property");
    _jspx_th_bean_005fwrite_005f1.setProperty("name");
    _jspx_th_bean_005fwrite_005f1.setIgnore(true);
    int _jspx_eval_bean_005fwrite_005f1 = _jspx_th_bean_005fwrite_005f1.doStartTag();
    if (_jspx_th_bean_005fwrite_005f1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fproperty_005fname_005fignore_005fnobody.reuse(_jspx_th_bean_005fwrite_005f1);
      return true;
    }
    _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fproperty_005fname_005fignore_005fnobody.reuse(_jspx_th_bean_005fwrite_005f1);
    return false;
  }

  private boolean _jspx_meth_bean_005fwrite_005f2(javax.servlet.jsp.tagext.JspTag _jspx_th_portlet_005fform_005f0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  bean:write
    org.apache.struts.taglib.bean.WriteTag _jspx_th_bean_005fwrite_005f2 = (org.apache.struts.taglib.bean.WriteTag) _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fname_005fignore_005fnobody.get(org.apache.struts.taglib.bean.WriteTag.class);
    _jspx_th_bean_005fwrite_005f2.setPageContext(_jspx_page_context);
    _jspx_th_bean_005fwrite_005f2.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_portlet_005fform_005f0);
    _jspx_th_bean_005fwrite_005f2.setName("definition");
    _jspx_th_bean_005fwrite_005f2.setIgnore(true);
    int _jspx_eval_bean_005fwrite_005f2 = _jspx_th_bean_005fwrite_005f2.doStartTag();
    if (_jspx_th_bean_005fwrite_005f2.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fname_005fignore_005fnobody.reuse(_jspx_th_bean_005fwrite_005f2);
      return true;
    }
    _005fjspx_005ftagPool_005fbean_005fwrite_0026_005fname_005fignore_005fnobody.reuse(_jspx_th_bean_005fwrite_005f2);
    return false;
  }

  private boolean _jspx_meth_html_005ftext_005f0(javax.servlet.jsp.tagext.JspTag _jspx_th_portlet_005fform_005f0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:text
    org.apache.struts.taglib.html.TextTag _jspx_th_html_005ftext_005f0 = (org.apache.struts.taglib.html.TextTag) _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.get(org.apache.struts.taglib.html.TextTag.class);
    _jspx_th_html_005ftext_005f0.setPageContext(_jspx_page_context);
    _jspx_th_html_005ftext_005f0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_portlet_005fform_005f0);
    _jspx_th_html_005ftext_005f0.setProperty("preference(width)");
    int _jspx_eval_html_005ftext_005f0 = _jspx_th_html_005ftext_005f0.doStartTag();
    if (_jspx_th_html_005ftext_005f0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f0);
      return true;
    }
    _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f0);
    return false;
  }

  private boolean _jspx_meth_html_005ftext_005f1(javax.servlet.jsp.tagext.JspTag _jspx_th_portlet_005fform_005f0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:text
    org.apache.struts.taglib.html.TextTag _jspx_th_html_005ftext_005f1 = (org.apache.struts.taglib.html.TextTag) _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.get(org.apache.struts.taglib.html.TextTag.class);
    _jspx_th_html_005ftext_005f1.setPageContext(_jspx_page_context);
    _jspx_th_html_005ftext_005f1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_portlet_005fform_005f0);
    _jspx_th_html_005ftext_005f1.setProperty("preference(height)");
    int _jspx_eval_html_005ftext_005f1 = _jspx_th_html_005ftext_005f1.doStartTag();
    if (_jspx_th_html_005ftext_005f1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f1);
      return true;
    }
    _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f1);
    return false;
  }

  private boolean _jspx_meth_html_005ftext_005f2(javax.servlet.jsp.tagext.JspTag _jspx_th_portlet_005fform_005f0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:text
    org.apache.struts.taglib.html.TextTag _jspx_th_html_005ftext_005f2 = (org.apache.struts.taglib.html.TextTag) _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.get(org.apache.struts.taglib.html.TextTag.class);
    _jspx_th_html_005ftext_005f2.setPageContext(_jspx_page_context);
    _jspx_th_html_005ftext_005f2.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_portlet_005fform_005f0);
    _jspx_th_html_005ftext_005f2.setProperty("preference(value)");
    int _jspx_eval_html_005ftext_005f2 = _jspx_th_html_005ftext_005f2.doStartTag();
    if (_jspx_th_html_005ftext_005f2.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f2);
      return true;
    }
    _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f2);
    return false;
  }

  private boolean _jspx_meth_html_005ftext_005f3(javax.servlet.jsp.tagext.JspTag _jspx_th_portlet_005fform_005f0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:text
    org.apache.struts.taglib.html.TextTag _jspx_th_html_005ftext_005f3 = (org.apache.struts.taglib.html.TextTag) _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.get(org.apache.struts.taglib.html.TextTag.class);
    _jspx_th_html_005ftext_005f3.setPageContext(_jspx_page_context);
    _jspx_th_html_005ftext_005f3.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_portlet_005fform_005f0);
    _jspx_th_html_005ftext_005f3.setProperty("preference(tabindex)");
    int _jspx_eval_html_005ftext_005f3 = _jspx_th_html_005ftext_005f3.doStartTag();
    if (_jspx_th_html_005ftext_005f3.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f3);
      return true;
    }
    _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f3);
    return false;
  }

  private boolean _jspx_meth_html_005ftext_005f4(javax.servlet.jsp.tagext.JspTag _jspx_th_portlet_005fform_005f0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:text
    org.apache.struts.taglib.html.TextTag _jspx_th_html_005ftext_005f4 = (org.apache.struts.taglib.html.TextTag) _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.get(org.apache.struts.taglib.html.TextTag.class);
    _jspx_th_html_005ftext_005f4.setPageContext(_jspx_page_context);
    _jspx_th_html_005ftext_005f4.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_portlet_005fform_005f0);
    _jspx_th_html_005ftext_005f4.setProperty("preference(style)");
    int _jspx_eval_html_005ftext_005f4 = _jspx_th_html_005ftext_005f4.doStartTag();
    if (_jspx_th_html_005ftext_005f4.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f4);
      return true;
    }
    _005fjspx_005ftagPool_005fhtml_005ftext_0026_005fproperty_005fnobody.reuse(_jspx_th_html_005ftext_005f4);
    return false;
  }

  private boolean _jspx_meth_html_005frewrite_005f0(PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:rewrite
    org.apache.struts.taglib.html.RewriteTag _jspx_th_html_005frewrite_005f0 = (org.apache.struts.taglib.html.RewriteTag) _005fjspx_005ftagPool_005fhtml_005frewrite_0026_005fpage_005fmodule_005fnobody.get(org.apache.struts.taglib.html.RewriteTag.class);
    _jspx_th_html_005frewrite_005f0.setPageContext(_jspx_page_context);
    _jspx_th_html_005frewrite_005f0.setParent(null);
    _jspx_th_html_005frewrite_005f0.setPage("/script/portlet.jsp");
    _jspx_th_html_005frewrite_005f0.setModule("/common");
    int _jspx_eval_html_005frewrite_005f0 = _jspx_th_html_005frewrite_005f0.doStartTag();
    if (_jspx_th_html_005frewrite_005f0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _005fjspx_005ftagPool_005fhtml_005frewrite_0026_005fpage_005fmodule_005fnobody.reuse(_jspx_th_html_005frewrite_005f0);
      return true;
    }
    _005fjspx_005ftagPool_005fhtml_005frewrite_0026_005fpage_005fmodule_005fnobody.reuse(_jspx_th_html_005frewrite_005f0);
    return false;
  }
}