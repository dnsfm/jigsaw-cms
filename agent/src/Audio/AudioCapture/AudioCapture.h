/*
 * �����ɼ���ʵ����
 */

#ifndef _AudioCapture_H_
#define _AudioCapture_H_

#include "../AudioCommon/AudioCommon.h"
#include "AudioCaptureMgr.h"

class AudioCapture
{
public:
    AudioCapture(
        AudioCaptureMgr::PIO_CALLBACK pCallback,       // Callback function
		void* pCallbackParameter,                      // Callback parameter
		int nWaveInDeviceId);                          // WaveIn Device Id
    ~AudioCapture();

public:

    // ��ʼ��׽
	bool startCapture();

    // ֹͣ��׽
	bool stopCapture();

private:

    //����������׽��Ϣ���̺߳���
	static unsigned int WINAPI AudioInThreadProc(LPVOID lpParameter); 

    // �߳̾����ID
	int m_nWaveInDeviceId;
    HANDLE m_hAudioIn;
    unsigned int m_threadId;

private:

    // �����������ĸ���
    static const NUM_BUF = 8;

    // �����豸�ľ��
	HWAVEIN m_hIn;	

    // ����¼�ƵĻ�����
	WAVEHDR* m_pHdr;
	bool freeBuffer();
	bool allocBuffer();

   // �ص����������
    void* m_pCallbackParameter;
    AudioCaptureMgr::PIO_CALLBACK m_pCallback;

};

#endif 

