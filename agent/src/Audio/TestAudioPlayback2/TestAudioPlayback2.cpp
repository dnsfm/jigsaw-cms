// TestAudioPlayback2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TestAudioPlayback2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
 * �°���������Ŵ����� dedede ��������������¼����������
 * Ϊ����֤��һ�㣬��ԭ�����������Ŵ�������һ��exe
 */

// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

#include "..\AudioCapture\AudioCaptureMgr.h"
#include "FvscAudioPlayer.h"


void playData(void* pObject, WAVEHDR* pWH)
{
    FvscAudioPlayer* pPlayer = (FvscAudioPlayer*)pObject;
    pPlayer->playDecodeData(pWH->lpData, pWH->dwBytesRecorded);
    return;
}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("��������: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
	}

    printf("Begin to record and play, press Enter to stop it...\n");

	FvscAudioPlayer audioPlay;
	audioPlay.init();

    AudioCaptureMgr::PIO_CALLBACK pCallback = playData;
    AudioCaptureMgr::create(pCallback, &audioPlay);

    AudioCaptureMgr::startCapture();
    ::getchar();
    AudioCaptureMgr::stopCapture();

	audioPlay.destroy();

    AudioCaptureMgr::destroy();

	return nRetCode;
}
