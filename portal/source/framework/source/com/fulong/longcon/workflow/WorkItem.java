/**
 * 
 */
package com.fulong.longcon.workflow;

/**
 *   
 * 
 * Coolink协同工作框架模型 
 *
 * Copyright: 2009-2011 北京中科辅龙计算机技术股份有限公司
 *
 * Company: 北京中科辅龙计算机技术股份有限公司
 *
 * @author lixf
 *
 * @version 2.0
 *
 */
public interface WorkItem {
	/**
	 * 判断工作项是否满足给定的条件
	 * @param conditions
	 * @return
	 */
	public boolean validate(String conditions);

}
