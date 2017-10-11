#pragma once

class ClientNotifier;

class TransModel
{
public:
	TransModel()
	{
	};

	virtual ~TransModel()
	{
	};

	virtual bool Create() = 0;
	virtual void Destroy() = 0;

// used by AVManager

public:
	// �װ�
	virtual void addWhiteboard( __int64 confId, void* pVoid ) = 0;
	virtual void removeWhiteboard( __int64 confId ) = 0;
	virtual void sendWhiteboardData( __int64 confId, char* buffer, int len ) = 0;

	// ����һ·��������
    virtual bool addUserAudioPlay(__int64 userId) = 0;

	// ɾ��һ·��������
    virtual bool removeUserAudioPlay(__int64 userId) = 0;

	// ��ʼ��������
	virtual void startSendAudio() = 0;

	// ֹͣ��������
	virtual void stopSendAudio() = 0;

	// ����һ·ͼ����ʾ
    virtual bool addUserVideoPlay(__int64 userId, HWND hVideoWnd, __int64 conferenceId, int nwidth, int nheight) = 0;

	// ɾ��һ·ͼ����ʾ
    virtual bool removeUserVideoPlay(__int64 userId, __int64 conferenceId) = 0;

    // ����һ·������Ƶ��ʾ
    virtual bool addLocalVideoWindow(HWND hWnd, __int64 conferenceId) = 0;

    // ɾ��һ·������Ƶ��ʾ
    virtual bool removeLocalVideoWindow(__int64 conferenceId) = 0;

	// ��ʼ������Ƶ
	virtual void startSendVideo(__int64 userId) = 0;

	// ֹͣ������Ƶ
	virtual void stopSendVideo(__int64 userId) = 0;

// used by RunningConference.cpp

	// �û������Ƿ�����Ƶ
	virtual void EnableSendVideo(BOOL bSend) = 0;

// used by DesktopManager

	// Set frame rate
	virtual void setFrameRateAndKeyFrameInterval(int frameRate, int keyFrameInterval) = 0;

public:

	// ��ʼ��������
	virtual void startSendDesktop() = 0;

	// ֹͣ��������
	virtual void stopSendDesktop() = 0;

	// ��ʼ����ĳ���û�������
	virtual void startReceiveUserDesktop(__int64 userId, string userName, ClientNotifier* pClientNotifier) = 0;

	// ֹͣ����ĳ���û�������
	virtual void stopReceiveUserDesktop(__int64 userId) = 0;

	// ��ʼ����ĳ���û�������
	virtual void startControlUserDesktop(__int64 userId) = 0;

	// ֹͣ����ĳ���û�������
	virtual void stopControlUserDesktop(__int64 userId) = 0;

	// �ҳ���ǰ�ۿ������������ϲ���Ǹ�
	virtual __int64 getTopDesktopClientId() = 0;

public:

// used by LServer

	//����UDP��������ip�Ͷ˿ڣ�������Socket����Ӧ�߳�
	virtual BOOL setUdpServer(string IP, int port) = 0;

    //����TCP��������ip�Ͷ˿ڣ�������Socket����Ӧ�߳�
    virtual BOOL setTcpServer(string IP, int port) = 0;

// used by self

	// ����UDP����, ���ط��͵Ľ��
	virtual int sendUDPData(char *buf, DWORD nlen) = 0;

	// ����TCP���ݣ����ط��͵Ľ��
	virtual BOOL sendTCPData(char* buf, DWORD nlen) = 0;

	// ������Ƶѹ����ͷ����
	virtual void setTKLHead(__int64 userId, UCHAR* pHead, int nLen = 1024) = 0;
};

