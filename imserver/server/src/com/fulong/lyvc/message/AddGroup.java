///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

package com.fulong.lyvc.message;

/**
 * AddGroup
 * 
 * 龙驭视频会议系统 v3.0
 * 
 * 版权所有：北京中科辅龙计算机技术股份有限公司 2009
 * 
 * @author 李雄锋
 * 
 * 最后修改时间：2010-9-10
 */

public class AddGroup extends BaseMessage{

	public static final int id = 113;

	public boolean isCommon;
	public String groupId;
	public String parentGroupId;
	public String name;

	public String toXML() {
		StringBuffer xml = new StringBuffer();
		xml.append("<lyvcmessage>");
		xml.append("<id>" + id + "</id>");
		xml.append("<_senderid>" + this.getSenderId() + "</_senderid>");
		xml.append("<_conferenceid>" + this.getConferenceId() + "</_conferenceid>");
		xml.append("<isCommon>");
		if( this.isCommon){
			xml.append(1);
		} else {
			xml.append(0);
		}
		xml.append("</isCommon>");
		xml.append("<groupId>" + this.groupId + "</groupId>");
		xml.append("<parentGroupId>" + this.parentGroupId + "</parentGroupId>");
		xml.append("<name>");
		if(this.name != null) {
			xml.append(encodeHtmlEscape(this.name));
		}
		xml.append("</name>");
		xml.append("</lyvcmessage>");
		
		return xml.toString();
	}

	public void fromXML(String xmlString) throws MessageFormatException {
		String tagContent;
		
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "_senderid");
		this.setSenderId(tagContent);
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "_conferenceid");
		this.setConferenceId(tagContent);
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "isCommon");
		if( tagContent.equals("0")) {
			this.isCommon = false;
		} else {
			this.isCommon = true;
		}
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "groupId");
		this.groupId = tagContent;
		tagContent = BaseMessage.getStringBetweenTag(xmlString, "parentGroupId");
		this.parentGroupId = tagContent;
		this.name = BaseMessage.decodeHtmlEscape(BaseMessage.getStringBetweenTag(xmlString, "name"));
	}

}
