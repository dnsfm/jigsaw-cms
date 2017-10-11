#pragma once

#include "WinsockWrapper/WinsockWrapper/TCPSocket.h"

class TcpLink
{
public:

    // �յ������Ժ�Ļص�����ԭ�Ͷ���
    typedef void (*TCPLINK_CALLBACK)(void* pObject, char* pBuffer, int nLength);

public:
	TcpLink(
		TCPLINK_CALLBACK pCallback,     // Callback function
		void* pCallbackParameter);      // Callback parameter
	~TcpLink();

	BOOL Create(string IP, int port);
	void Destroy();

    // ��õײ��SOCKET
	SOCKET getSocket();

    // ����TCP���ݰ�
	int send(char* buf, int dwLen);

private:

	string	m_sServerIP;                    // ������IP
	int		m_nPort;                        // �������˿�

	TCPLINK_CALLBACK m_pCallback;           // �ص�����
	void*        m_pCallbackParameter;      // �ص������Ĳ���

    // �ײ��Socket
	CTCPSocket		m_Socket;

    // ��ȡsocket���߳̾��
	HANDLE			m_hSocketThread;
	
    // ��ȡSocket���̺߳���
	static unsigned int WINAPI SocketThreadProc(LPVOID lpParameter);	
};

