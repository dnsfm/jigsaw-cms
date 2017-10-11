#ifndef UDPLINK_H
#define UDPLINK_H

#include "WinsockWrapper/WinsockWrapper/UDPSocket.h"

class UdpLink
{
public:

    // �յ������Ժ�Ļص�����ԭ�Ͷ���
    typedef void (*UDPLINK_CALLBACK)(void* pObject, char* pBuffer, int nLength);

public:
	UdpLink(
		UDPLINK_CALLBACK pCallback,     // Callback function
		void* pCallbackParameter);      // Callback parameter

	~UdpLink();

	BOOL Create(string IP, int port);
	void Destroy();

    // ��õײ��SOCKET
	SOCKET getSocket();

    // ����UDP���ݰ�
	int send(char* buf, int dwLen);

private:

	string	m_sServerIP;                    // ������IP
	int		m_nPort;                        // �������˿�(UDP)

	UDPLINK_CALLBACK m_pCallback;           // �ص�����
	void*        m_pCallbackParameter;      // �ص������Ĳ���

    // �ײ��Socket
	CUDPSocket		m_MediaUdpSocket;

    // ��ȡsocket���߳̾��
	HANDLE			m_hUSockThread;
	
    // ��ȡSocket���̺߳���
	static unsigned int WINAPI USockThreadProc(LPVOID lpParameter);	
};

#endif //UDPLINK_H
