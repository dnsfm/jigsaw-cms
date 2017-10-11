#pragma once

class FvsmUser
{
public:
	FvsmUser();
	~FvsmUser();

	SOCKADDR		m_udpAddr;	        // �û���UDP��ַ
	__int64			m_userId;           // �û�ID

    // ����һ��ý���źŽ�����
	BOOL addReceiver(__int64 userId, int dataType);	

    // ɾ��һ��ý���źŽ�����
	BOOL removeReceiver(__int64 userId, int dataType);
	
    //�����Լ���������
	list<__int64> m_audioReceivers;

    //�����Լ�ͼ�����
	list<__int64> m_videoReceivers;

    // �Ƿ����ڽ��ܲ�����ָ���û�������
    BOOL isReceiveAudioFromUser(__int64 userId);

    // �Ƿ����ڽ��ܲ�����ָ���û���ͼ��
    BOOL isReceiveVideoFromUser(__int64 userId);
};

