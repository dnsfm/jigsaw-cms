// FvscAudioPlayer.h: interface for the FvscAudioPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FvscAudioPlayer_H__5A6BBF45_B6E0_4220_A627_7D2407E3F6CD__INCLUDED_)
#define AFX_FvscAudioPlayer_H__5A6BBF45_B6E0_4220_A627_7D2407E3F6CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AudioPlay.h"
#include "FvsAudioCodec.h"
#include "../../common/common/MediaPacket/udp_media_def.h"

//�����Ľ��ܣ�������ȥ����
class FvscAudioPlayer  
{
public:
	FvscAudioPlayer();
	virtual ~FvscAudioPlayer();

public:

	int			m_iAudioBuf;


	CAudioPlay*		m_player;
	FvsAudioCodec*	m_codec;	//Ϊ�����ר�õĽ�����	

	BOOL		m_isEnd;	//�߳̽���

	void init();		
	void destroy();

	void playDecodeData(char* pAudioBuffer, int len);
	void playEncodeData(PACK_AUDIO *ppa, int len);

	static UINT _playAudioThread(LPVOID lparam);

protected:
	CWinThread* m_pThreadPlayAudio;
	

	BOOL InitAudioPlay();
	void DestroyAudioPlay();
};

#endif // !defined(AFX_FvscAudioPlayer_H__5A6BBF45_B6E0_4220_A627_7D2407E3F6CD__INCLUDED_)
