#pragma once

#include "common/common/MediaPacket/udp_media_def.h"
#include "AudioProcessPlay.h"

class MultiAudioPlay {

public:    

	MultiAudioPlay(__int64 userId);
	~MultiAudioPlay();
    bool create();
    void destroy();

    // Create an audio play process for play
    bool createProcessForUser(__int64 userId);

    // Destroy user audio play process
    bool destroyProcessForUser(__int64 userId);

    // Play audio data packet, the packet will
    // be dispatched to proper audio process.
	void playAudioPack(PACK_AUDIO *ppa);

private:

    // �����û�ID
    // ���ǵ��п������ж���ͻ��˳���, ʹ�ô�������Ϊ
    // �������ų�������֣�����������
    __int64 m_userId;

    // �������Ž��̵ı��, ����
	int m_nInstanceCount;

	// ���е��������Ž���
	typedef std::map<__int64, AudioProcessPlay*> AudioProcessMap;
    AudioProcessMap m_audioProcesses;

	// �����п��ܱ�������鸴�ã��˴�Ϊ���ü���
	map<__int64, int> m_audioProcessUseCount;
};

