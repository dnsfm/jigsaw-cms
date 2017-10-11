#pragma once

#include "VideoWindow.h"
#include "TKL_Player.h"

class VideoDecoder;
struct PACK_VIDEO;

class VideoPlay
{
public:
    VideoPlay();
    ~VideoPlay();
    bool create(int nwidth, int nheight, bool bTKLPlayer = false);
    void destroy();

    bool addVideo(HWND hWnd, __int64 conferenceId);
    bool removeVideo(__int64 conferenceId);
    int getVideoCount();

    void decode(PACK_VIDEO *ppv, unsigned char* pDst);
    void play(unsigned char* pData, int nLen = 0);
	DWORD m_dwPrevKeyFrameNum; // previous key frame number

private:

    VideoDecoder* m_pDecoder;        // Video Decoder
    VideoWindowMap m_videoWindowMap; // All video windows
	int m_nWidth;
	int m_nHeight;

public:
	// ��ʼ��tklplayer
	bool TKLInit(BYTE* pBuf, int nLen = 1024);

private:
	// �ͷ�tklplayer��Դ
	void TKLDestroy();
	// ������Ƶ����
	bool TKLPlay(BYTE* pBuf, int nLen);
	// ��Ӳ�����
	bool TKLAddPlayer(HWND hWnd, __int64 confId);
	// ɾ��������
	bool TKLRemovePlayer(__int64 confId);

	// �������б�
	map<__int64, ULONG> m_TKLPlayerMap;
	// ��ʼ������
	UCHAR m_TKLHead[1024];

	// �Ƿ���tklplayer
	bool m_bTKLPlayer;
    // �Ƿ��ѳ�ʼ��
	bool m_bTKLInit;

};

