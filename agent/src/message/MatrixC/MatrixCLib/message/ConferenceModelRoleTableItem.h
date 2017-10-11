///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

#ifndef ConferenceModelRoleTableItem_H
#define ConferenceModelRoleTableItem_H

#include "BaseMessage.h"

namespace LyvcMessage {

class ConferenceModelRoleTableItem : public BaseMessage{

	public:
		static const id = 54;
		__int64 modelId;
		__int64 roleId;
		string roleName;
		string rights;

	public:
		virtual string toXML();
		virtual bool fromXML(string& xmlString);

}; // class

}; // namespace

#endif
