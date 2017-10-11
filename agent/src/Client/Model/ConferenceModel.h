#ifndef CONFERENCE_MODE_H
#define CONFERENCE_MODE_H

#include "ConferenceRole.h"

class ConferenceModel {

private:
    string  m_strName;               //����ģʽ����
    __int64 m_nID;                   //����ģʽID
    vector<ConferenceRole> m_roles;  //���������е��û����

public:

	ConferenceModel(__int64 nID, string strName);
	~ConferenceModel();

public:

	// ���ID
	__int64 getID();

	// �������
	string getName();

	// �����û����
	void addRole(ConferenceRole& conferenceRole);

	// ����ID��ȡ�û��������
	string getRoleName(__int64 nRoleID);

	// ����ID��ȡ�û����
	ConferenceRole* getRole(__int64 nRoleID);
};

#endif
