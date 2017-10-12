package com.fulong.site.channel;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.fulong.longcon.site.Channel;
import com.fulong.longcon.site.SiteFolder;

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
 * @date 2010-8-12	
 * @version 1.0.1
 */
public class DoCopyAction extends ChannelBaseAction {
    /**
     *
     * @throws Exception ：在这个方法的实现中，原则上不进行任何的异常处理，仅抛出异常
     * @param mapping ActionMapping
     * @param form ActionForm
     * @param request HttpServletRequest
     * @param response HttpServletResponse
     * @return ActionForward
     */
    protected ActionForward templateExecute(ActionMapping mapping,
                                            ActionForm form,
                                            HttpServletRequest request,
                                            HttpServletResponse response) throws
            Exception {
    	String channelPath = request.getParameter("channelPath");
    	String destPath = request.getParameter("destPath");
    	String name = request.getParameter("name");
    	String displayName = request.getParameter("displayName");
    	
    	Channel channel = this.parseChannel(channelPath,request);
    	if(channel==null){
    		response.sendError(HttpServletResponse.SC_BAD_REQUEST, "栏目不存在.");
    		return null;
    	}
    	
    	SiteFolder destFolder = this.parseFolder(destPath,request);
    	if(channel==null){
    		response.sendError(HttpServletResponse.SC_BAD_REQUEST, "文件夹不存在.");
    		return null;
    	}
    	
    	if(!this.copyTo(channel, destFolder, name, displayName,request)){
    		response.sendError(HttpServletResponse.SC_BAD_REQUEST, "复制失败.");
    	}
    	
        return null;
    }
}
