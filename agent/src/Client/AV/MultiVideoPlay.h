#pragma once

#include "Video/VideoConfig/VideoConfig.h"
#include "VideoWindow.h"

class VideoPlay;
struct PACK_VIDEO;

class MultiVideoPlay
{
public:	

	MultiVideoPlay();
	virtual ~MultiVideoPlay(); 
    bool create();
    void destroy();
  
	// ���յ���Ƶ�źţ����͵���Ӧ�Ĵ���
	void OnNetworkVideoData(PACK_VIDEO *ppv, DWORD len);

	//��׽����Ƶ����,���͵������ұ�����Ƶ����
	void OnLocalVideoData(LPVIDEOHDR lpVHdr);

    // ����һ·��Ƶ����
    void addUserVideoPlay(__int64 userId, HWND hWnd, __int64 conferenceId, int nwidth, int nheight, bool bTKLPlayer = false);

    // ɾ��һ·��Ƶ����
    void removeUserVideoPlay(__int64 userId, __int64 conferenceId);

    // ����һ·������Ƶ
    void addLocalVideoWindow(HWND hWnd, __int64 conferenceId);

    // ɾ��һ·������Ƶ
    void removeLocalVideoWindow(__int64 conferenceId);

	void setTKLHead(UCHAR* pData, int nLen, __int64 userId);

private:

    // Local video windows
    VideoWindowMap m_localVideoWindowMap;

    // Decode buffer for all decoder
    unsigned char* m_decodeBuffer;

    // VideoPlay list
    map<__int64, VideoPlay*> m_remoteVideoPlayMap;
};

