package com.fulong.taglib.common;

import javax.servlet.jsp.JspException;

import com.fulong.taglib.CompareTagBase;

/**
 *
 * <p>Title: 龙驭网站内容管理系统</p>
 *
 * <p>Description: 龙驭网站内容管理系统</p>
 *
 * <p>Copyright: 北京中科辅龙计算机技术股份有限公司 2008</p>
 *
 * <p>Company: 北京中科辅龙计算机技术股份有限公司</p>
 *
 * @author Lixf
 * @version 3.0
 */

public class EqualTag extends CompareTagBase {

	private static final long serialVersionUID = -8774815393237386064L;

	/**
     * Evaluate the condition that is being tested by this particular tag,
     * and return <code>true</code> if the nested body content of this tag
     * should be evaluated, or <code>false</code> if it should be skipped.
     * This method must be implemented by concrete subclasses.
     *
     * @exception JspException if a JSP exception occurs
     */
    protected boolean condition() throws JspException {
        return (condition(0, 0));
    }

}
