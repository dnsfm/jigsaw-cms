#ifndef CONFERENCE_H
#define CONFERENCE_H


#include "model/DBConference.h"

class Conference
{
public:
	enum ConferenceStatus  // ����״̬
	{
		Active = 1,   // �����ٿ�
		Inactive,      // ��δ�ٿ�
		Finished		// �ѽ���
	};

public:
	Conference(DBConference dbConference);
	~Conference();

public:
	// ��Ӧ�������
	HTREEITEM m_hItem;
	DBConference m_dbConference;  // ��������

private:
	ConferenceStatus m_status;    // ����״̬
	int m_nUserCount;             // �����е�����

public:

	// ȡ�û���״̬
	ConferenceStatus getStatus();

	// ���û���״̬
	void setStatus(ConferenceStatus status);
};

#endif
