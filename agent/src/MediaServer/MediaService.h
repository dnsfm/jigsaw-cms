#pragma once
#include "serviceframework/service.h"

class MediaService : public Service
{
private:

	// Stop Event.
	HANDLE m_hStopEvent;

public:

    // ������������
	virtual int start();

    // ������ֹ����
	virtual int stop();
};
