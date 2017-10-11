#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "../../../WinsockWrapper/WinsockWrapper/TCPSocket.h"

namespace LyvcMessage {

class IOManager;

struct MESSAGELENGTH_PACK
{
	IOManager* pIOManager;
	int nLength;
};

class IOManager
{
public:

    // �յ������Ժ�Ļص�����ԭ�Ͷ���
    typedef void (*PIO_CALLBACK)(void* pObject, const char* pBuffer, int nLength);

public:

	// ������Ϣ�Ĵ�С����Ϊ 64k
	static const int CMD_PACKET_SIZE = 1024*64;

    // ���ڱ�ʾ�յ����ݵĴ�����ϢID
    static const int DATA_RECEIVED_MESSAGE = WM_USER + 1;

public:

	IOManager(
		PIO_CALLBACK pCallback,     // Callback function
		void* pCallbackParameter,   // Callback parameter
        const char* strHost,        // Remote host ip
		int nPort);                 // Remote port

	~IOManager();

public:

	// �����շ��߳�
	BOOL start();

	// ֹͣ�շ��߳�
	BOOL stop();

	// ��������
	void sendData(const char *pBuf, DWORD len);

private:

	PIO_CALLBACK m_pCallback;           // �ص�����
	void*        m_pCallbackParameter;  // �ص������Ĳ���
	string       m_strHost;             // ��������ַ
	int          m_nPort;               // �������˿�

	CTCPSocket   m_TcpSocket;	    // Socket
    HWND         m_hWindow;         // Ͷ����Ϣ�Ĵ��ھ��
	HANDLE       m_hSocketReadThread;  // �����̵߳ľ��

private:

    // �������ڽ���Socket��Ϣ�Ĵ���
    BOOL createMessageWindow();

    // ����Socket��Ϣ�Ĵ��ڵĴ��ڹ���
    static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// ���ڽ���Socket���ݵ��߳�
	static unsigned int WINAPI socketReadThreadProc(LPVOID lpParameter);

	// ������Ϣ֪ͨ�������
	void notifyConnectionBroken();

};  // class

};  // namespace

#endif
