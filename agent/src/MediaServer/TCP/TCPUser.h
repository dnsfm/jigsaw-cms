#pragma once

class TCPForward;

class TCPUser
{
private:
	static const int BUFFER_SIZE = 8192;

	__int64 m_userId;    // User id
	SOCKET m_socket;     // Socket

	TCPForward* m_pTCPForward;

	// socket read thread handle and function
	HANDLE m_hThread;
	static unsigned int __stdcall ThreadProc(void* pObject);

public:

    TCPUser(__int64 userId, TCPForward* pTCPForward);
    ~TCPUser();

	bool Create();
	void Destroy();

	// ��ʼ TCP���ݵ�ת��
	bool startForward(SOCKET s);

	// ��������
	bool sendData(char* buffer, int iLen);
};
