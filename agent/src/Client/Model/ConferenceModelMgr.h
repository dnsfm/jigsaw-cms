#ifndef CONFERENCE_MODE_MGR_H
#define CONFERENCE_MODE_MGR_H

#include "message/MatrixC/MatrixCLib/MessageTarget.h"

class ConferenceModel;

class ConferenceModelMgr : public LyvcMessage::MessageTarget {

private:
	typedef std::map<__int64, ConferenceModel*> ConferenceModelMap;
	ConferenceModelMap m_modes;  // ���������еĻ���ģʽ�б�

	// ��ʱ�����ģʽID
	__int64 m_instantConferenceModelId;

public:
	ConferenceModelMgr( LyvcMessage::MatrixC* pMatrixC );
	~ConferenceModelMgr();
	bool create() { return true; };
	void destroy() { };

public:

	__int64 getInstantConferenceModelId();
	void setInstantConferenceModelId(__int64 id);

public:

	// ����һ�ֻ���ģʽ
	void addConferenceMode(__int64 nID, string strName);

	// ���ض��Ļ���ģʽ����һ���û����
	void addConferenceModeRole(__int64 nModeID, __int64 nRoleID, string strName, string rights);

	// ����IDȡ�û���ģʽ����
	string getConferenceModeNameByID(__int64 nID);

	// ���ݻ���ģʽID���û����IDȡ���û��������
	string getConferenceRoleNameByID(__int64 nConferenceModeID, __int64 nRoleID);

	ConferenceModel* getConferenceModeByID(__int64 nID);

private:
	//��ȡ����ģʽ�б�
	void cmdGetConferenceModeTable() const;

	//��ȡĳ������ģʽ���û�����б�
	void cmdGetConferenceModeRoleTable(__int64 nModeID) const;

public:
    void UserDetail(LyvcMessage::BaseMessage* pMessage);
    void ConferenceModelTableItem(LyvcMessage::BaseMessage* pMessage);
    void ConferenceModelRoleTableItem(LyvcMessage::BaseMessage* pMessage);
	void InstantConferenceModelId(LyvcMessage::BaseMessage* pMessage);

};

#endif
