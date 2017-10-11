#pragma once

#include "common/common/MediaPacket/udp_media_def.h"

class AudioProcessPlay
{

private:
	string              m_name;          // ��������
    PROCESS_INFORMATION m_processInfo;   // �������Ž�����Ϣ
    HANDLE              m_hEvent;        // ͨѶ�õ�Event����  
    PVOID               m_pFileMapView;  // �ļ�ӡ����ͼ
    HANDLE              m_hFileMap;      // �ļ�ӡ����

public:

    AudioProcessPlay();
    ~AudioProcessPlay();

    // ��������
    BOOL create(string name);

    // ���ٶ���
    void destroy();

    // ������������
    BOOL play(PACK_AUDIO *ppa);

};

