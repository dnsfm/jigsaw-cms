///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

#include "stdafx.h"
#include "ConferenceModelTableItem.h"

string LyvcMessage::ConferenceModelTableItem::toXML()
{
	const int BUFFERSIZE=64;
	char buffer[BUFFERSIZE];
	string xml;
	xml = xml + "<lyvcmessage>";
	xml = xml + "<id>";
	_snprintf(buffer, BUFFERSIZE, "%I32d", id);
	xml = xml + buffer;
	xml = xml + "</id>";
	xml = xml + "<_senderid>";
	_snprintf(buffer, BUFFERSIZE, "%I64d", this->_senderId);
	xml = xml + buffer;
	xml = xml + "</_senderid>";
	xml = xml + "<_conferenceid>";
	_snprintf(buffer, BUFFERSIZE, "%I64d", this->_conferenceId);
	xml = xml + buffer;
	xml = xml + "</_conferenceid>";
	xml = xml + "<modelId>";
	_snprintf(buffer, BUFFERSIZE, "%I64d", this->modelId);
	xml = xml + buffer;
	xml = xml + "</modelId>";
	xml = xml + "<modelName>";
	xml = xml + BaseMessage::encodeHtmlEscape(this->modelName);
	xml = xml + "</modelName>";
	xml = xml + "</lyvcmessage>";
	return xml;
}

bool LyvcMessage::ConferenceModelTableItem::fromXML(string& xmlString)
{
	string tagContent;
	
	tagContent = BaseMessage::getStringBetweenTag(xmlString, "_senderid");
	if(tagContent == ""){
		return false;
	}
	this->_senderId = _atoi64(tagContent.c_str());
	tagContent = BaseMessage::getStringBetweenTag(xmlString, "_conferenceid");
	if(tagContent == ""){
		return false;
	}
	this->_conferenceId = _atoi64(tagContent.c_str());
	tagContent = BaseMessage::getStringBetweenTag(xmlString, "modelId");
	if(tagContent == ""){
		return false;
	}
	this->modelId = _atoi64(tagContent.c_str());
	this->modelName = BaseMessage::decodeHtmlEscape(BaseMessage::getStringBetweenTag(xmlString, "modelName"));
	return true;
}

