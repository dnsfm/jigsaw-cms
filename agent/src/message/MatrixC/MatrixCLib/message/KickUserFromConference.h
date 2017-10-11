///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

#ifndef KickUserFromConference_H
#define KickUserFromConference_H

#include "BaseMessage.h"

namespace LyvcMessage {

class KickUserFromConference : public BaseMessage{

	public:
		static const id = 149;
		__int64 confUserId;
		__int64 confId;

	public:
		virtual string toXML();
		virtual bool fromXML(string& xmlString);

}; // class

}; // namespace

#endif
