#include "stdafx.h"
#include "FileMappingFlag.h"
#include "common/common/Log/Log.h"
#include "common/common/MediaPacket/udp_media_def.h"
#include "Audio/AudioCommon/AudioCommon.h"
#include "Audio/AudioPlayback/AudioPlayback.h"
#include "Audio/AudioCodec/AudioCodec.h"

void openLog()
{
	char filename[MAX_PATH];
	::ZeroMemory(filename, MAX_PATH);
	::GetModuleFileName(NULL, filename, MAX_PATH);
    char* appNameEnd = ::strrchr(filename, '.');
    *appNameEnd = 0;

    char logFileName[1024];
    _snprintf(logFileName, 1024, "%s_%d.log", filename, time(NULL));
	Log::open(logFileName);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    // Open log
#ifdef _DEBUG
    openLog();
    FVS_DEBUG1("%s", lpCmdLine);
#endif

    if( __argc < 6 )
    {
        FVS_DEBUG("Insufficent parameters. Program exit.");
        Log::close();
        return -1;
    }

	// Enhance local thread priority
	::SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

    // ���ļ�ӳ��
	HANDLE hFileMapT = OpenFileMapping(
            FILE_MAP_READ | FILE_MAP_WRITE,
            FALSE,
            __argv[1]);
	if (hFileMapT == NULL)
    {
        FVS_DEBUG("Can't open file mapping object");
        Log::close();
		return -1;		 
    }

	PVOID pView = MapViewOfFile(hFileMapT, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	if (pView == NULL)
	{
        FVS_DEBUG("Can't map view for file mapping object");
		CloseHandle(hFileMapT);
        Log::close();
		return -1;
	}
    
    DWORD* pFlag      = (DWORD*)pView;
	PACK_AUDIO *pPack = (PACK_AUDIO *)(((char*)pView) + sizeof(DWORD));

	//���¼�����
	HANDLE hCounterIn = OpenEvent(
            EVENT_ALL_ACCESS,
            true,
            __argv[2]);
	if (hCounterIn == NULL)
	{
        FVS_DEBUG("Can't open event object");
        UnmapViewOfFile(pView);
        ::CloseHandle(hFileMapT);
        Log::close();
		return -1;
	}

    // �������ݻ�����
    int bufferSize = atoi(__argv[3]);
    char* pSrcBuffer = new char[bufferSize];

    // �򿪸����̾��
    HANDLE hParentProcess = ::OpenProcess(
        SYNCHRONIZE,
        FALSE,
        atoi(__argv[4]));
    if( hParentProcess == NULL ) {
        FVS_DEBUG("Can't open parent process");
        delete[] pSrcBuffer;
        UnmapViewOfFile(pView);
        ::CloseHandle(hFileMapT);
        Log::close();
        return -1;
    }
    HANDLE h[2];
    h[0] = hParentProcess;
    h[1] = hCounterIn;

    // ��ʼ��������
    AudioCodec codec;

    // �����������Ŷ���
    AudioPlayback playback;
    playback.create(atoi(__argv[5]));

	while(1)
	{
    	int ret = WaitForMultipleObjects(2, h, FALSE, INFINITE);

		if (ret == WAIT_ABANDONED || ret == WAIT_FAILED )
        {
            FVS_DEBUG("WaitForMultipleObject failed: ABANDONED or FAILED");
			break;
        }

        // Parent process terminated.
        if( ret == WAIT_OBJECT_0 + 0 )
        {
            FVS_DEBUG("Parent proecess exit prematurly.");
            break;
        }

		ResetEvent(hCounterIn);

		if (*pFlag == FileMappingFlag::STOP)
		{
            FVS_DEBUG("Parent proecess wants us to quit, do it.");
			break;
		}

		else if (*pFlag == FileMappingFlag::NEW_DATA)
		{
		    // �����ǰ���ڲ��ŵĿ������������ƣ��׵������ӵ�����
			if( playback.getPlayingBufferCount() > AudioPlayback::MAX_PLAYING_BUFFER )
			{
				FVS_DEBUG1("Skip an audio pack. Playing buffer count is %d", playback.getPlayingBufferCount());
				continue;
			}

            // Copy the data out of the file mapping in case it is overwritten by main process
            int srcLength = pPack->data_size;
            memcpy(pSrcBuffer, (char*)(pPack) + sizeof(PACK_AUDIO), pPack->data_size);

            // Get decoded data
    		char pAudioBuffer[AudioCommon::SIZE_AUDIO_FRAME];
            int nLen;
	    	BOOL result = codec.DecodeAudioData(
                    pSrcBuffer,
                    srcLength,
                    pAudioBuffer,
                    &nLen);

            // Play it
            if(result)
            {
                playback.play(pAudioBuffer, nLen);
            }
		}

        else
        {
            FVS_DEBUG1("Unknown flag: %d", *pFlag);
            Log::flush();
            _ASSERTE(FALSE);
        }

	}

    // �رո����̾��
    ::CloseHandle(hParentProcess);

    // �ͷŻ�����
    delete[] pSrcBuffer;

	//�����������Ŷ���
	playback.destroy();

    // �����¼�����
	CloseHandle(hCounterIn);

    // ȡ���ļ�ӳ��
	UnmapViewOfFile(pView);
	CloseHandle(hFileMapT);
	
    // �ر�Log
#ifdef _DEBUG
    Log::close();
#endif

	return 0;
}

