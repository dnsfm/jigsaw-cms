package com.fulong.portlet.date.weekCalendar;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.fulong.portlet.cms.ListContentPortletRender;

/**
 * Title: Coolink平台协同服务管理系统
 * </p>
 * 
 * <p>
 * Description: Coolink平台协同服务管理系统
 * </p>
 * 
 * <p>
 * Copyright: 北京中科辅龙计算机技术股份有限公司 2009
 * </p>
 * 
 * <p>
 * Company: 北京中科辅龙计算机技术股份有限公司
 * </p>
 * 
 * @author lixiang
 * @version 3.1
 */
public class FinalRender extends ListContentPortletRender {

	/**
	 * execute
	 * 
	 * @param request
	 *            RenderRequest
	 * @param response
	 *            RenderResponse
	 * @throws Exception
	 */
	public ActionForward render(ActionMapping mapping, ActionForm form, RenderRequest request, RenderResponse response)
			throws Exception {	 
		//片段的路径
		request.setAttribute("path", getClipPath(request, response, ""));
		
	    request.setAttribute("preferences", request.getPreferences());

		PortletPreferences preferences = request.getPreferences();

		//取出当前时间
		Calendar calendar = null;
		calendar = Calendar.getInstance();
		calendar.getTime();
		
		//取出参数传递的时间
		String str = request.getParameter("dateParameter");
		if (str != null){
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd"); 
		Date par = sdf.parse(str);
		calendar.setTime(par);
		}
		String initialDate = preferences.getValue("initialDate", null);
		String startloc = preferences.getValue("startloc", "1");
		int intStartloc = Integer.parseInt(startloc);
		if (intStartloc>7){
			intStartloc=7;
		} else if (intStartloc<1){
			intStartloc=1;
		}
		List<Date> list=new ArrayList<Date>();
			
		//初始日期是当天
		if (initialDate.equals("today")) {
			
			for (int j=1;j<intStartloc;j++){
				calendar.add(Calendar.DATE, 1);
			}
			for(int i=1;i<9-intStartloc;i++)
			{
				list.add(calendar.getTime());
				calendar.add(Calendar.DATE, 1);
			}			

		//初始日期是周一
		} else {
			while(true) {
			if (Calendar.MONDAY==calendar.get(Calendar.DAY_OF_WEEK))
			{
				break;
			}
			calendar.add(Calendar.DATE, -1);
			}
			calendar.add(Calendar.DATE, -1);
			for (int j=0;j<intStartloc;j++){
				calendar.add(Calendar.DATE, 1);
			}
			for(int i=1;i<9-intStartloc;i++)
			{
				list.add(calendar.getTime());
				calendar.add(Calendar.DATE, 1);
			}				
		}
			//行数，列数为空时，设置为1
			String row = preferences.getValue("row", null);
			String column = preferences.getValue("column", null);
			if (row == null) {
				preferences.setValue("row", "1");
			}
			if (column == null) {
				preferences.setValue("column", "1");
			}
			
			//当行数和列数的乘积大于7时，补齐表格的空白，以便于jsp页面的轮空循环操作
			int rowInt = 0;
			int columnInt = 0;
			try {
				rowInt = Integer.parseInt(row);
				columnInt = Integer.parseInt(column);
			}catch(Exception e){
				rowInt = 1;
				columnInt = 1;
			}
			if(rowInt*columnInt>7){
				for(int i=0;i<rowInt*columnInt-8+intStartloc;i++){
					list.add(calendar.getTime());
				}
			}
			request.setAttribute("weekList", list.iterator());
			
			return mapping.findForward("success");	
	}

}