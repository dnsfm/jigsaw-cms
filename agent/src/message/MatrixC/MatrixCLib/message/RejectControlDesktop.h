///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

#ifndef RejectControlDesktop_H
#define RejectControlDesktop_H

#include "BaseMessage.h"

namespace LyvcMessage {

class RejectControlDesktop : public BaseMessage{

	public:
		static const id = 104;
		__int64 conferenceId;
		__int64 senderId;
		__int64 receiverId;

	public:
		virtual string toXML();
		virtual bool fromXML(string& xmlString);

}; // class

}; // namespace

#endif
