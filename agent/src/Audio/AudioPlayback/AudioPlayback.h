#pragma once

class AudioPlayback
{
public:

    // Constructor
    AudioPlayback();

    // Destructor
    ~AudioPlayback();

    // create/destroy
    bool create(int nDeviceId = WAVE_MAPPER);
    void destroy();

    // Play audio data
    void play(char* pAudioBuffer, int len);

	// Return buffer count which are being played.
	int getPlayingBufferCount();

private:

    //��������������Ϣ���̺߳���
	static unsigned int WINAPI AudioPlaybackThreadProc(LPVOID lpParameter); 

    //�߳̾����ID
    HANDLE m_hAudioPlayback;
    unsigned int m_AudioPlaybackId;

    //�����豸�ľ��
	HWAVEOUT m_hOut;

    // ���ڲ��ŵĻ�������Ŀ
    LONG volatile m_nPlayingBufferCount;

public:

	// ���ŵĻ�������Ŀ����
    static const int MAX_PLAYING_BUFFER = 6;

};
