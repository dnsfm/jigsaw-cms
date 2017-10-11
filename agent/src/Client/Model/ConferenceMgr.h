#ifndef CONFERENCE_MGR_H
#define CONFERENCE_MGR_H

#include "message/MatrixC/MatrixCLib/MessageTarget.h"

class LServer;
class Conference;
class RunningConference;
class MultiConferenceMatrixC;
class CMeetingRoomFrame;

class ConferenceMgr : public LyvcMessage::MessageTarget
{
public:
	ConferenceMgr( LyvcMessage::MatrixC* pMatrixC, LServer* pServer );
	~ConferenceMgr();
	bool create() { return true; };
	void destroy() { };

	// ��������㷵�ػ���ָ��
	Conference* getConferenceByItem( HTREEITEM hItem );

	// ���ݻ������Ʒ��ػ���ָ��
	Conference* getConferenceByName( string sConfName );

private:
	LServer* m_pServer;

	/**
	* ��ʽ�����б�
	*/
	typedef std::map<__int64, Conference*> ConferenceMap;
	ConferenceMap m_conferences;

	// ���ӻ���
	void addConference(Conference* pConference);

	// ɾ������
	void deleteConference(__int64 conferenceID);

	// ���ݻ���IDȡ�û���ָ�룬��������ڣ�����NULL
	Conference* getConferenceByID(__int64 conferenceID);

private:

	/*
	 * ���ڽ����еĻ����б�
	 */
	typedef std::map<__int64, RunningConference*> RunningConferenceMap;
	RunningConferenceMap m_runningConferences;

    // ���ÿһ�����еĻ��飬������һ����װ����MatrixC
    // ��Ի�����Ϣ���з���
    typedef map<__int64, MultiConferenceMatrixC*> MultiConferenceMatrixCMap;
    MultiConferenceMatrixCMap m_MultiConferenceMatrixCMap;

	// �������ڽ��еĻ���
	void addRunningConference(RunningConference* pRunningConference);

	// ɾ�����ڽ��еĻ���
	void deleteRunningConference(__int64 conferenceID);

	//����ID��ȡ���ڽ��еĻ���ָ��
	RunningConference* getRunningConferenceByID(__int64 conferenceID);

public:

	//�����Ƿ����ڽ���
	BOOL isConferenceGoing(__int64 conferenceId);

	// ֹͣ�������������еĻ���
	void stopAllRunningConference();

	// ����һ�����л������
	RunningConference* createRunningConference(
		Conference* pConference,                // ����
		CMeetingRoomFrame* pMeetingRoomFrame);  // ����Ľ���

	// ɾ�����л�����󣬴��ݻ����ID
	void destroyRunningConference(__int64 conferenceId);

private:
	//��ȡ�����б���Ϣ
	void cmdGetConferenceList() const;

public:
	// ���ʹ�����ʱ����
    void cmdCreateInstantConference(vector<__int64> participants);

public:
    void MediaServerAddress(LyvcMessage::BaseMessage* pMessage);
    void AddConference(LyvcMessage::BaseMessage* pMessage);
	void ConferenceFinish(LyvcMessage::BaseMessage* pMessage);
	void DeleteConference(LyvcMessage::BaseMessage* pMessage);
	void ModifyConference(LyvcMessage::BaseMessage* pMessage);
    void StartConference(LyvcMessage::BaseMessage* pMessage);
	void InviteConference(LyvcMessage::BaseMessage* pMessage);
	void KickUserFromConference(LyvcMessage::BaseMessage* pMessage);
	void DeleteConferenceUser(LyvcMessage::BaseMessage* pMessage);

};


#endif
