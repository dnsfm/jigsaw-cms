/**
 * 
 */
package com.fulong.longcon.workflow.xml;

import org.w3c.dom.Element;

import com.fulong.longcon.workflow.ImpActivity;
import com.fulong.longcon.workflow.ProcessDefinition;
import com.fulong.longcon.workflow.WorkItem;
import com.fulong.longcon.workflow.WorkflowService;

/**
 *  Implementation活动 
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
public class XMLImpActivity extends XMLActivity implements ImpActivity {
	
	public XMLImpActivity(Element element, ProcessDefinition definition,WorkflowService service){
		super(element,definition,service);
	}
	public int getType(){
		return IMPLEMENTATION;
	}
	/**
	 * 进入活动既直接执行活动
	 * 
	 * @param node
	 * @return
	 */
	public void enter(WorkItem node) throws Exception {
		super.enter(node);
		this.execute(node);
	}
}