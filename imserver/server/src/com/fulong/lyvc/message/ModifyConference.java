///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

package com.fulong.lyvc.message;

import java.util.Date;

/**
 * ModifyConference
 * 
 * 龙驭视频会议系统 v3.0
 * 
 * 版权所有：北京中科辅龙计算机技术股份有限公司 2009
 * 
 * @author 李雄锋
 * 
 * 最后修改时间：2010-9-10
 */

public class ModifyConference extends BaseMessage{

	public static final int id = 156;

	public Date startTime;
	public Date endTime;
	public String conId;
	public String conModelId;
	public String conName;
	public String conDesc;
	public String conFileDesc;
	public String conFileURL;
	
	public String toXML() {
		StringBuffer xml = new StringBuffer();
		xml.append("<lyvcmessage>");
		xml.append("<id>" + id + "</id>");
		xml.append("<_senderid>" + this.getSenderId() + "</_senderid>");
		xml.append("<_conferenceid>" + this.getConferenceId() + "</_conferenceid>");
		xml.append("<startTime>");
		if(this.startTime != null) {
			xml.append(this.startTime.getTime());
		} else {
			xml.append(0);
		}
		xml.append("</startTime>");
		xml.append("<endTime>");
		if(this.endTime != null) {
			xml.append(this.endTime.getTime());
		} else {
			xml.append(0);
		}
		xml.append("</endTime>");
		xml.append("<conId>" + this.conId + "</conId>");
		xml.append("<conModelId>" + this.conModelId + "</conModelId>");
		xml.append("<conName>");
		if(this.conName != null) {
			xml.append(encodeHtmlEscape(this.conName));
		}
		xml.append("</conName>");
		xml.append("<conDesc>");
		if(this.conDesc != null) {
			xml.append(encodeHtmlEscape(this.conDesc));
		}
		xml.append("</conDesc>");
		xml.append("<conFileDesc>");
		if(this.conFileDesc != null) {
			xml.append(encodeHtmlEscape(this.conFileDesc));
		}
		xml.append("</conFileDesc>");
		xml.append("<conFileURL>");
		if(this.conFileURL != null) {
			xml.append(encodeHtmlEscape(this.conFileURL));
		}
		xml.append("</conFileURL>");
		xml.append("</lyvcmessage>");
		
		return xml.toString();
	}

	public void fromXML(String xmlString) throws MessageFormatException {
		String tagContent;
		
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "_senderid");
		this.setSenderId(tagContent);
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "_conferenceid");
		this.setConferenceId(tagContent);
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "startTime");
		this.startTime = new Date(Long.parseLong(tagContent));
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "endTime");
		this.endTime = new Date(Long.parseLong(tagContent));
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "conId");
		this.conId = tagContent;
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "conModelId");
		this.conModelId = tagContent;
		this.conName = BaseMessage.decodeHtmlEscape(BaseMessage.getStringBetweenTag(xmlString, "conName"));
		this.conDesc = BaseMessage.decodeHtmlEscape(BaseMessage.getStringBetweenTag(xmlString, "conDesc"));
		this.conFileDesc = BaseMessage.decodeHtmlEscape(BaseMessage.getStringBetweenTag(xmlString, "conFileDesc"));
		this.conFileURL = BaseMessage.decodeHtmlEscape(BaseMessage.getStringBetweenTag(xmlString, "conFileURL"));
	}

}
