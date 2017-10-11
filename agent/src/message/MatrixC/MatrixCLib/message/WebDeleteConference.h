///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

#ifndef WebDeleteConference_H
#define WebDeleteConference_H

#include "BaseMessage.h"

namespace LyvcMessage {

class WebDeleteConference : public BaseMessage{

	public:
		static const id = 60;
		__int64 conId;

	public:
		virtual string toXML();
		virtual bool fromXML(string& xmlString);

}; // class

}; // namespace

#endif
