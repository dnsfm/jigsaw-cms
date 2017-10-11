#include "StdAfx.h"
#include "IOManager.h"
#include "../MatrixC.h"
#include "../../../Common/Common/Log/Log.h"

// #define DEBUG_PROTOCOL
#define DEBUG_PROTOCOL_MAX_SIZE 256

LyvcMessage::IOManager::IOManager(
		PIO_CALLBACK pCallback,     // Callback function
		void* pCallbackParameter,   // Callback parameter
        const char* strHost,        // Remote host ip
		int nPort)                  // Remote port
{
    this->m_pCallback = pCallback;
    this->m_pCallbackParameter = pCallbackParameter;
    this->m_strHost = string(strHost);
	this->m_nPort   = nPort;
}

LyvcMessage::IOManager::~IOManager()
{
}

BOOL LyvcMessage::IOManager::start()
{
    // Init Winsock
    WSADATA wsaData;
    ::WSAStartup(MAKEWORD(2,2), &wsaData);

    // Create window
    if( !createMessageWindow())
    {
        return FALSE;
    }

    // Create socket
	if( !m_TcpSocket.Create() )
	{
		return FALSE;
	}

    if (!m_TcpSocket.Connect(m_nPort, m_strHost.c_str()))
	{
		m_TcpSocket.Destroy();
		return FALSE;
	}

    // Run Socket read thread.
	unsigned int threadID;
	m_hSocketReadThread=(HANDLE)::_beginthreadex(NULL, 0, socketReadThreadProc, this, 0, &threadID);
	_RPTF1(_CRT_WARN, "MatrixC read tcp thread created, id: 0x%x \n",threadID);
	if (m_hSocketReadThread == 0)
	{
		m_TcpSocket.Destroy();
		return FALSE;
	}

	return TRUE;
}

BOOL LyvcMessage::IOManager::stop()
{
	// �ر�Socket
	if (m_TcpSocket.IsSocket())
	{
		m_TcpSocket.Destroy();
	}

    // ���ٴ���
	// ��һ���������ֹͣ�߳�֮ǰ�������߳��п��ܴ���
	// SendMessage��״̬�����������
    if( this->m_hWindow != NULL )
    {
        ::DestroyWindow(this->m_hWindow);
        this->m_hWindow = NULL;
    }

	// ֹͣ�߳�
    if( m_hSocketReadThread != 0 )
    {
	    ::WaitForSingleObject(m_hSocketReadThread, INFINITE);
		::CloseHandle(m_hSocketReadThread);
        m_hSocketReadThread = 0;
    }

    // ж��Winsock library
    ::WSACleanup();

	return TRUE;
}

// 
// findMessage �ҳ���ǰ����������һ��Message��
// ����
//    pBuf     : ������ָ��
//    dataSize : ����������
//    pContentStart  : ָ��Message��ʵ������(���л����)��ָ��
//    nContentLength : Message��ʵ������(���л����)�ĳ���
// ����ֵ
//    �ҵ���Message�������С�����л����+header line)�����û���ҵ�������-1
//
static int findMessage(char* pBuf, int dataSize, char*& pContent, int& nContentLength)
{
	// 1, ���� Content-Length ��
	char* pContentLengthLineStart = ::strstr(pBuf, "Content-Length:");
	if( pContentLengthLineStart == NULL )
	{
		return -1;
	}

	// 2, ȡ�� ʵ�����ݴ�С
	char* pContentLengthLineEnd = ::strchr(pContentLengthLineStart, '\r');
	if( pContentLengthLineEnd == NULL )
	{
		return -1;
	}
	*pContentLengthLineEnd = 0;
	nContentLength = ::atoi( pContentLengthLineStart + strlen("Content-Length:"));

	// 3, �ж������Ƿ�����
	if( pBuf + dataSize < pContentLengthLineEnd + 4 + nContentLength )
	{
        *pContentLengthLineEnd = '\r';
		return -1;
	}

	// 4, ����ʵ�����ݵ�ָ��
	pContent = pContentLengthLineEnd + 4;

	// 5, ���ص�ǰ��Ϣ�Ĵ�С
	return pContentLengthLineEnd + 4 + nContentLength - pBuf;
}

unsigned int WINAPI LyvcMessage::IOManager::socketReadThreadProc(LPVOID lpParameter)
{
	IOManager* _this=(IOManager*)lpParameter;

	char pBuf[CMD_PACKET_SIZE + 1]; // �������ݵĻ�����
	int dataSize = 0;           // �������ڵ����ݳ���

	BOOL bRunning = TRUE;
	while(bRunning)
	{
		int readByteCount = 0;                    // ��һ�ζ�ȡ������ȡ���ֽ�
		int size = CMD_PACKET_SIZE - dataSize;    // ��������ʣ��Ŀռ�

		// ������ֽ��մ���,�˳��߳�
		if ((readByteCount=_this->m_TcpSocket.Receive(pBuf+dataSize, size)) <= 0)
		{
			_RPTF1(_CRT_WARN, "%x\n", ::GetLastError());
            _this->m_TcpSocket.Destroy();
			_this->notifyConnectionBroken();
			bRunning = FALSE;
			continue;
		}

		// �޸Ļ�����
		dataSize = dataSize + readByteCount;
		pBuf[dataSize] = 0;

		//
		// �п���һ�ζ��������Ϣ, ��Ҫ��ѭ���н��д���
        //

		// ��һ�����������
		int dataPos = 0;

		while(dataSize > 0)
		{
			// ��ǰXML��Ϣ���ʵ������λ��ָ�뼰��С
			char* pContent;
			int nContentLength;

			// ��ǰ��Ϣ�Ĵ�С
			int currentMessageSize = findMessage(pBuf+dataPos, dataSize, pContent, nContentLength);

			// �����������ʣ������ݲ���һ��������Ϣ��
			// ��ʣ�����ݿ�������������ʼ��Ȼ���˳�����
			if (currentMessageSize < 0)
			{
				if (dataSize != 0)
				{
					char buffer[CMD_PACKET_SIZE];
					::memcpy(buffer, pBuf+dataPos, dataSize);
					::memcpy(pBuf, buffer, dataSize);
					pBuf[dataSize] = 0;
				}
				break;
			}

			// ����ʣ������ݴ�С
			dataSize -= currentMessageSize;

			// ��sipMessage�е�ʵ�����ݿ������µĻ������У����͸�����
			char* pBuffer = (char*)malloc(nContentLength);
            ::memcpy(pBuffer, pContent, nContentLength);

#ifdef DEBUG_PROTOCOL
            string tmp = string(pBuffer, nContentLength);
            if( tmp.size() > DEBUG_PROTOCOL_MAX_SIZE )
            {
                FVS_DEBUG1("Receive: %s\n", tmp.substr(0, DEBUG_PROTOCOL_MAX_SIZE ).c_str());
            }
            else
            {
                FVS_DEBUG1("Receive: %s\n", tmp.c_str());
            }
#endif
            MESSAGELENGTH_PACK* mp = new MESSAGELENGTH_PACK();
			mp->pIOManager = _this;
			mp->nLength = nContentLength;
            // ֪ͨ����
            ::SendMessageCallback(_this->m_hWindow, IOManager::DATA_RECEIVED_MESSAGE, (WPARAM)pBuffer, (LPARAM)mp, NULL, NULL);

			// �����������
			dataPos += currentMessageSize;
		}
	}

    return 0;
}

// ��������
void LyvcMessage::IOManager::sendData(const char *pBuf, DWORD len)
{
    // ��鵱ǰ��Socket�Ƿ���Ч
    if(!this->m_TcpSocket.IsSocket() )
    {
        return;
    }

    // �������ݵĻ�����
	char buffer[CMD_PACKET_SIZE + 1];

    // ����ͷ��
	_snprintf(buffer, CMD_PACKET_SIZE + 1, LyvcMessage::MatrixC::LYVC_MESSAGE_HEADER, len);
    int headerLength = strlen(buffer);
	
    // �ϲ���Ϣ, �����Ϣ�ߴ���󣬲����͸���Ϣ
    if(len + headerLength > CMD_PACKET_SIZE) {
		_ASSERTE(FALSE);
        return;
    }
    ::memcpy(buffer + headerLength, pBuf, len);

#ifdef DEBUG_PROTOCOL
    string tmp = string(pBuf, len);
    if( tmp.size() > DEBUG_PROTOCOL_MAX_SIZE )
    {
        FVS_DEBUG1("Send: %s\n", tmp.substr(0, DEBUG_PROTOCOL_MAX_SIZE ).c_str());
    }
    else
    {
        FVS_DEBUG1("Send: %s\n", tmp.c_str());
    }
#endif

    // ������Ϣ
	if( !m_TcpSocket.Send(buffer, headerLength + len))
	{
        m_TcpSocket.Destroy();
		notifyConnectionBroken();
	}
}

void LyvcMessage::IOManager::notifyConnectionBroken()
{
#pragma message ("we use postmessage for notify connection broken, differs from simple message dispather")
    MESSAGELENGTH_PACK* mp = new MESSAGELENGTH_PACK();
	mp->pIOManager = this;
	mp->nLength = 0;
	::PostMessage(m_hWindow, DATA_RECEIVED_MESSAGE, (WPARAM)NULL, (LPARAM)mp);
	return;
}

BOOL LyvcMessage::IOManager::createMessageWindow()
{
    HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);

	WNDCLASSEX wcex;
    char* szWindowClass = "LyvcMessageIOManagerWindowClass";
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= (WNDPROC)IOManager::wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;
    ::RegisterClassEx(&wcex);

    this->m_hWindow = ::CreateWindow(
        szWindowClass,
        szWindowClass,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        NULL, NULL, hInstance, this);
    if( this->m_hWindow == NULL )
    {
        return FALSE;
    }

    return TRUE;
}

LRESULT CALLBACK LyvcMessage::IOManager::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //static IOManager* _this = NULL;

    if( message == IOManager::DATA_RECEIVED_MESSAGE)
	{
		MESSAGELENGTH_PACK* mp = (MESSAGELENGTH_PACK*) lParam;
		IOManager* _this = mp->pIOManager;
		(*(_this->m_pCallback))(_this->m_pCallbackParameter, (char*)wParam, mp->nLength);
		delete []((char*)wParam);
		delete mp;
		return 0;
	}

    // In WM_CREATE message, we preserve the "this" pointer
    //if( message == WM_CREATE ) {
    //    _this = (IOManager*)((CREATESTRUCT*)lParam)->lpCreateParams;
    //}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}
