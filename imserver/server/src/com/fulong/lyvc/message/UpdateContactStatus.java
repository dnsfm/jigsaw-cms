///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

package com.fulong.lyvc.message;

/**
 * UpdateContactStatus
 * 
 * 龙驭视频会议系统 v3.0
 * 
 * 版权所有：北京中科辅龙计算机技术股份有限公司 2009
 * 
 * @author 李雄锋
 * 
 * 最后修改时间：2010-9-10
 */

public class UpdateContactStatus extends BaseMessage{

	public static final int id = 112;

	public boolean bIsCommon;
	public int status;
	public String contactId;

	public String toXML() {
		StringBuffer xml = new StringBuffer();
		xml.append("<lyvcmessage>");
		xml.append("<id>" + id + "</id>");
		xml.append("<_senderid>" + this.getSenderId() + "</_senderid>");
		xml.append("<_conferenceid>" + this.getConferenceId() + "</_conferenceid>");
		xml.append("<bIsCommon>");
		if( this.bIsCommon){
			xml.append(1);
		} else {
			xml.append(0);
		}
		xml.append("</bIsCommon>");
		xml.append("<status>" + this.status + "</status>");
		xml.append("<contactId>" + this.contactId + "</contactId>");
		xml.append("</lyvcmessage>");
		
		return xml.toString();
	}

	public void fromXML(String xmlString) throws MessageFormatException {
		String tagContent;
		
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "_senderid");
		this.setSenderId(tagContent);
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "_conferenceid");
		this.setConferenceId(tagContent);
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "bIsCommon");
		if( tagContent.equals("0")) {
			this.bIsCommon = false;
		} else {
			this.bIsCommon = true;
		}
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "status");
		this.status = Integer.parseInt(tagContent);
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "contactId");
		this.contactId = tagContent;
	}

}
