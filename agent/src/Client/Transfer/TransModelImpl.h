#pragma once

class ConferenceUserMgr;
class ConferenceUser;

#include "TransModel.h"
#include "common/common/MediaPacket/tcp_media_def.h"
#include "common/common/MediaPacket/udp_media_def.h"
#include "SplitUDPPack.h"

namespace LyvcMessage
{
	class MatrixC;
};

class TcpLink;
class UdpLink;
class MultiAudioPlay;
class MultiVideoPlay;
class AudioCodec;
class VideoEncoder;
class VideoDecoder;
class DesktopServer;
class DesktopClient;
class CWhiteboardDlg;

class TransModelImpl : public TransModel
{
public:
	TransModelImpl(__int64 userId, LyvcMessage::MatrixC* pMatrixC);
	~TransModelImpl();

	virtual bool Create();
	virtual void Destroy();

private:
	map<__int64, CWhiteboardDlg*> m_whiteboardMap;
	CRITICAL_SECTION m_WhiteboardCs;

public:
	virtual void addWhiteboard( __int64 confId, void* pVoid );
	virtual void removeWhiteboard( __int64 confId );
	virtual void sendWhiteboardData( __int64 confId, char* buffer, int len );

	// ����һ·��������
    virtual bool addUserAudioPlay(__int64 userId);

	// ɾ��һ·��������
    virtual bool removeUserAudioPlay(__int64 userId);

	// ��ʼ��������
	virtual void startSendAudio();

	// ֹͣ��������
	virtual void stopSendAudio();

public:

	// ����һ·ͼ����ʾ
    virtual bool addUserVideoPlay(__int64 userId, HWND hVideoWnd, __int64 conferenceId, int nwidth, int nheight);

	// ɾ��һ·ͼ����ʾ
    virtual bool removeUserVideoPlay(__int64 userId, __int64 conferenceId);

    // ����һ·������Ƶ��ʾ
    virtual bool addLocalVideoWindow(HWND hWnd, __int64 conferenceId);

    // ɾ��һ·������Ƶ��ʾ
    virtual bool removeLocalVideoWindow(__int64 conferenceId);

	// ��ʼ������Ƶ
	virtual void startSendVideo(__int64 userId);

	// ֹͣ������Ƶ
	virtual void stopSendVideo(__int64 userId);

	// �û������Ƿ�����Ƶ
	virtual void EnableSendVideo(BOOL bSend);

	// Set frame rate
	virtual void setFrameRateAndKeyFrameInterval(int frameRate, int keyFrameInterval);

public:

	// ��ʼ��������
	virtual void startSendDesktop();

	// ֹͣ��������
	virtual void stopSendDesktop();

	// ��ʼ����ĳ���û�������
	virtual void startReceiveUserDesktop(__int64 userId, string userName, ClientNotifier* pClientNotifier);

	// ֹͣ����ĳ���û�������
	virtual void stopReceiveUserDesktop(__int64 userId);

	// ��ʼ����ĳ���û�������
	virtual void startControlUserDesktop(__int64 userId);

	// ֹͣ����ĳ���û�������
	virtual void stopControlUserDesktop(__int64 userId);

	// �ҳ���ǰ�ۿ������������ϲ���Ǹ�
	virtual __int64 getTopDesktopClientId();

public:

    //����TCP��������ip�Ͷ˿ڣ�������Socket����Ӧ�߳�
    virtual BOOL setTcpServer(string IP, int port);

	// ����TCP���ݣ����ط��͵Ľ��
	virtual BOOL sendTCPData(char* buf, DWORD nlen);

	//����UDP��������ip�Ͷ˿ڣ�������Socket����Ӧ�߳�
	virtual BOOL setUdpServer(string IP, int port);

	// ����UDP����, ���ط��͵Ľ��
	virtual int sendUDPData(char *buf, DWORD nlen);

    // �ɼ��������ݵĻص�����
    static void audioDataCallback(void* pObject, WAVEHDR* pWH);

    // �ɼ�ͼ�����ݵĻص�����
	static void videoDataCallback(void* pObject, LPVIDEOHDR lpVHdr);

private:

	// called periodically to send udp addr pack
    static void CALLBACK TimerFunction(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);

    // ���մ�ý�������������UDP���ݻص�����
	static void receiveUDPData(void* pObject, char* buf, int len);

    // ���մ�ý�������������TCP���ݻص�����
	static void receiveTCPData(void* pObject, char* buf, int len);

	// ���沶׽�Ļص�����
	static void desktopServerCallback(void* pObject, char* buffer, int len);

    // �����û���ID
	__int64 m_userId;

	// ��������Ϣϵͳ
	LyvcMessage::MatrixC* m_pMatrixC;

	// Object to capture the desktop
	DesktopServer* m_pDesktopServer;

	// Object to display and manager peer's desktops
	DesktopClient* m_pDesktopClient;
	CRITICAL_SECTION m_DesktopClientCs;

    // ����������UDP����
	UdpLink* m_pServerUdpLink;

    // ά��UDP NAT Session�Ķ�ʱ��
	UINT m_idTimerEvent;

    // ��ý���������TCP����
	TcpLink* m_pServerTcpLink;

	//��·�������ſ�����
	MultiAudioPlay*	m_pMultiAudioPlay;
	CRITICAL_SECTION m_AudioPlayCs;

	//��·ͼ�񲥷ſ�����
	MultiVideoPlay* m_pMultiVideoPlay;
	CRITICAL_SECTION m_VideoPlayCs;

    //�������͵ı�����
	AudioCodec* m_pAudioEncoder;

	//��Ƶ���͵ı�����
    VideoEncoder* m_pVideoEncoder;

	int				m_nCurVideoBitRate;	//��ǰʵ��ʹ�õı�����
	int				m_nKeyFrameInterval;//��ǰ�ؼ�֡���

    DWORD			m_dwAudioSeqNo;
    char			m_audioPack[MAX_UDP_SIZE];

    DWORD			m_dwVideoSeqNo;
    char			m_videoPack[MAX_UDP_SIZE];

    // �Ƿ������̫����MTU����Ƶ�ؼ�֡���в�֣�Ĭ�ϲ��
    bool m_splitKeyFrameFlag;

	// startSendAudio�����õĴ���
	// startSendAudio���Ӹ����֣� stopSendAudio���ٸ�����
	// ���������ֲ�Ϊ0����ʼ����
	// ����������Ϊ0����ֹͣ����
	LONG volatile m_nStartSendAudioCallCount;

	// startSendVideo�����õĴ���
	// startSendVideo���Ӹ����֣� stopSendVideo���ٸ�����
	// ���������ֲ�Ϊ0����ʼ����
	// ����������Ϊ0����ֹͣ����
	LONG volatile m_nStartSendVideoCallCount;

	// startSendDesktop�����õĴ���
	// startSendDesktop���Ӹ����֣� stopSendDesktop���ٸ�����
	// ���������ֲ�Ϊ0����ʼ����
	// ����������Ϊ0����ֹͣ����
	LONG volatile m_nStartSendDesktopCallCount;

    // ������Ƶ����
	void SendEncodedVideoData(DWORD encodedLen, bool bKeyFrame);

private:

	// �û������Ƿ�����Ƶ
	BOOL m_bSendVideo;

public:
    // ��Ƶѹ�����ɼ�ͼ�����ݵĻص�����
	static void videoCompressDataCallback(void* pObject, LONG handle, UCHAR* pData, int nLen, bool bKeyFrame);

	// ���ý�����Ƶѹ�������ݵ�ͷ����
	virtual void setTKLHead(__int64 userId, UCHAR* pHead, int nLen = 1024);

private:
	// ��Ƶѹ����ÿһ·�ɼ�ͨ���ı��ز�������Ŀ
	LONG m_LocalTKLPlayer[4];
	// ��Ƶѹ����ÿһ·�ɼ�ͨ����Զ�̲�������Ŀ
	LONG m_RemotelTKLPlayer[4];

	// Ϊ��Ƶѹ����ÿһ·�ɼ�ͨ��׼��һ��֡���
	DWORD m_dwTKLSeqNo[4];

	/*
	 *�ؼ�֡��������
	*/
private:
	// ��ֺ�����ݿ�
	char partialBlocks[PARTIAL_BLOCK_COUNT][MAX_ETHERNET_UDP + sizeof(PACK_VIDEO)];
	// ÿ���С
	int partialBlockSize[PARTIAL_BLOCK_COUNT];
	// ����������ݵĻ�����
	BufferedKeyFrame bufferedKeyFrames[BUFFERED_KEYFRAME_NUMBER];

};

