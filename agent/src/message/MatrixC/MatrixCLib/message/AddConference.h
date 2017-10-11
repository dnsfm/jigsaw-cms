///////////////////////////////
// Message definition file
// Generated by lyvc Message
///////////////////////////////

#ifndef AddConference_H
#define AddConference_H

#include "BaseMessage.h"

namespace LyvcMessage {

class AddConference : public BaseMessage{

	public:
		static const id = 65;
		bool isStarted;
		bool isEnded;
		__time64_t startTime;
		__time64_t endTime;
		__int64 creatorId;
		__int64 conId;
		__int64 conModelId;
		string conName;
		string conDesc;
		string conFilesDesc;
		string conFilesURL;

	public:
		virtual string toXML();
		virtual bool fromXML(string& xmlString);

}; // class

}; // namespace

#endif
