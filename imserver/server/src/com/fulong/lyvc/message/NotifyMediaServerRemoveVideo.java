///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

package com.fulong.lyvc.message;

/**
 * NotifyMediaServerRemoveVideo
 * 
 * 龙驭视频会议系统 v3.0
 * 
 * 版权所有：北京中科辅龙计算机技术股份有限公司 2009
 * 
 * @author 李雄锋
 * 
 * 最后修改时间：2010-9-10
 */

public class NotifyMediaServerRemoveVideo extends BaseMessage{

	public static final int id = 45;

	public String fromUserId;
	public String toUserId;

	public String toXML() {
		StringBuffer xml = new StringBuffer();
		xml.append("<lyvcmessage>");
		xml.append("<id>" + id + "</id>");
		xml.append("<_senderid>" + this.getSenderId() + "</_senderid>");
		xml.append("<_conferenceid>" + this.getConferenceId() + "</_conferenceid>");
		xml.append("<fromUserId>" + this.fromUserId + "</fromUserId>");
		xml.append("<toUserId>" + this.toUserId + "</toUserId>");
		xml.append("</lyvcmessage>");
		
		return xml.toString();
	}

	public void fromXML(String xmlString) throws MessageFormatException {
		String tagContent;
		
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "_senderid");
		this.setSenderId(tagContent);
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "_conferenceid");
		this.setConferenceId(tagContent);
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "fromUserId");
		this.fromUserId = tagContent;
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "toUserId");
		this.toUserId = tagContent;
	}

}
