#pragma once

#include "../rfb/rdr/DesktopServerCallback.h"

namespace LyvcMessage
{
	class MatrixC;
};

class DesktopServer
{
public:
	virtual ~DesktopServer(void);

public:
	static DesktopServer* getInstance();

	virtual void start(
		LyvcMessage::MatrixC* pMatrixC,       // ��Ϣϵͳ
		DESKTOPSERVER_CALLBACK pCallback,     // Callback function
		void* pCallbackParameter) = 0;        // Callback parameter

	virtual void stop() = 0;

	// ���ͳ�ʼ����Ϣ����������ͻ���
	virtual void reInitialize() = 0;

protected:
	DesktopServer(void);
};
