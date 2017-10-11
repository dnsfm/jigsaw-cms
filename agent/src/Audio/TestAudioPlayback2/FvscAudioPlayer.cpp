// FvscAudioPlayer.cpp: implementation of the FvscAudioPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FvscAudioPlayer.h"
#include "../AudioCommon/AudioCommon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FvscAudioPlayer::FvscAudioPlayer()
{
	m_codec = NULL;
	m_player = NULL;
}	

FvscAudioPlayer::~FvscAudioPlayer()
{
}

UINT FvscAudioPlayer::_playAudioThread(LPVOID lparam)
{
	TRACE1("_playAudioThread %x \n", GetCurrentThreadId());

	FvscAudioPlayer* pMgr = (FvscAudioPlayer*)lparam;	
	while(!pMgr->m_isEnd)
	{
		MSG msg;
		while(GetMessage(&msg,0,0,0))
		{
			if (pMgr->m_isEnd)
				return TRUE;

			switch(msg.message)
			{				
			//��Ƶ������ɺ�������̷߳���һ����Ϣ
			case WOM_DONE:
			{				
				WAVEHDR* pwh=(WAVEHDR*)msg.lParam;
				waveOutUnprepareHeader((HWAVEOUT)msg.wParam,pwh,sizeof(WAVEHDR));
				pMgr->m_iAudioBuf--;
				delete []pwh->lpData;//ɾ��Play����ʱ������ڴ�
				delete pwh;
			}
			break;
			}
		}		
	}
	return TRUE;
}

void FvscAudioPlayer::init()
{	
	if (!m_codec)
		m_codec = new FvsAudioCodec;

	m_isEnd = FALSE;

	//����һ���߳�
	m_pThreadPlayAudio=::AfxBeginThread(_playAudioThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	if (!m_pThreadPlayAudio)
		return;		
	m_pThreadPlayAudio->ResumeThread();

	InitAudioPlay();
}

void FvscAudioPlayer::destroy()
{
	m_isEnd = TRUE;

	if (m_codec != NULL)
	{	
		Sleep(50);
		delete m_codec;
		m_codec = NULL;
	}

	if (m_player != NULL)
	{
		DestroyAudioPlay();
		delete m_player;
		m_player = NULL;
	}
}


BOOL FvscAudioPlayer::InitAudioPlay()
{	
	m_iAudioBuf = 0;

	if (!m_player)
		m_player = new CAudioPlay;

	if (!m_player->Create(0, m_pThreadPlayAudio->m_nThreadID, (DWORD)this, CALLBACK_THREAD))
	{
		DestroyAudioPlay();
		return FALSE;
	}

	return TRUE;
}

void FvscAudioPlayer::DestroyAudioPlay()
{
	if (m_player)
		m_player->Destroy();
}


void FvscAudioPlayer::playDecodeData(char* pAudioBuffer, int len)
{
	//Ϊ�˱����ӳٹ��������ۻ��Ļ��峬������ʱ������������Ļ���
	if (m_iAudioBuf < 6)
	{
		m_iAudioBuf++;
		m_player->Play(pAudioBuffer, len);	
	}
	else
	{
		TRACE("Start to throw audio data.\n");
	}
}

void FvscAudioPlayer::playEncodeData(PACK_AUDIO *ppa, int len)
{
	if (m_pThreadPlayAudio)
	{
		char pAudioBuffer[AudioCommon::SIZE_AUDIO_FRAME];
		if (m_codec->DecodeAudioData((char*)(ppa)+sizeof(PACK_AUDIO),ppa->data_size,pAudioBuffer,0))
		{
			playDecodeData(pAudioBuffer, AudioCommon::SIZE_AUDIO_FRAME);

			//Ϊ���Ժ�¼��ʹ�ã��������ٷ���ԭ���Ļ�����
			memcpy(((char*)ppa + sizeof(PACK_AUDIO)), pAudioBuffer, AudioCommon::SIZE_AUDIO_FRAME);
			ppa->data_size = AudioCommon::SIZE_AUDIO_FRAME;
		}
	}
}

