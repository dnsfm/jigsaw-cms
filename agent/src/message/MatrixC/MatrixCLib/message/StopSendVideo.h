///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

#ifndef StopSendVideo_H
#define StopSendVideo_H

#include "BaseMessage.h"

namespace LyvcMessage {

class StopSendVideo : public BaseMessage{

	public:
		static const id = 80;
		__int64 conferenceId;
		__int64 senderId;
		__int64 receiverId;

	public:
		virtual string toXML();
		virtual bool fromXML(string& xmlString);

}; // class

}; // namespace

#endif
