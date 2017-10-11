#ifndef RUNNING_CONFERENCE_H
#define RUNNING_CONFERENCE_H

#include "message/MatrixC/MatrixCLib/MessageTarget.h"

struct DBUser;
class CMeetingRoomFrame;
class AVManager;
class TransModel;
class ConferenceUser;
class Conference;
class ConferenceModelMgr;
class ConferenceUserMgr;
class DesktopManager;
class FileTransferMgr;
class YuntaiMgr;

class RunningConference : public LyvcMessage::MessageTarget {

private:
	vector<LyvcMessage::BaseMessage*> m_delaySendMsgs;
	__int64 m_idLastConfUser;

	// ָ������ָ��
	Conference* m_pConference;

	// ָ������ҽ����ָ��
	CMeetingRoomFrame* m_pRoom;

	// ��ǰ�û���ָ��
	ConferenceUser* m_pUser;

	// ����ģʽ��������ָ��
	ConferenceModelMgr* m_pConferenceModeMgr;

    // ������Ա�Ĺ�����
    ConferenceUserMgr* m_pConferenceUserMgr;

    // ����Ƶ������
    AVManager*	m_pAVManager;

	//���湲�������
	DesktopManager* m_pDesktopMgr;

	// �ļ����������
	FileTransferMgr* m_pFileTransferMgr;

	YuntaiMgr* m_pYuntaiMgr;

public:
	Conference* getConference() const
	{
		return m_pConference;
	}
	ConferenceUserMgr* getConferenceUserMgr() const
	{
		return m_pConferenceUserMgr;
	}

	//�ж��û��Ƿ��ڻ�����
	bool isUserInConference(USERID uid);

	//�Ƿ�����ʱ����
	BOOL isInstantConference();
	/*
	 *�ж��Ƿ���и���Ȩ��
	 */
	// �����Ƿ��з�����Ƶ��Ȩ��
	BOOL canSendVideo( __int64 uid );
	// �Լ��Ƿ��������ۿ���Ƶ��Ȩ��
	BOOL canReceiveVideo();

	// �����Ƿ��з�����Ƶ��Ȩ��
	BOOL canSendAudio( __int64 uid );
	// �Լ��Ƿ�����������������Ȩ��
	BOOL canReceiveAudio();
	
	// �Լ��Ƿ������뷢�Ե�Ȩ��
	BOOL canApplySpeak();
	// uid=0��ʾ�Լ��Ƿ��п��Ʒ��Ե�Ȩ�ޣ������ʾ�����Ƿ��ܿ��Ʒ���
	BOOL canControlSpeak( __int64 uid = 0 );
	
	// �Լ��Ƿ��ܷ����ļ�
	BOOL canSendFile();
	// �����Ƿ��ܽ����ļ�
	BOOL canReceiveFile( __int64 uid );

    // uid=0��ʾ�Լ��Ƿ��ܷ������棬�����ʾ�����Ƿ��ܷ�������
	BOOL canSendDesktop( __int64 uid = 0 );
    // uid=0��ʾ�Լ��Ƿ��ܽ������棬�����ʾ�����Ƿ��ܽ�������
	BOOL canReceiveDesktop( __int64 uid = 0 );

	// �Լ��Ƿ���������ϵ�˼������
	BOOL canInviteUser();
	// �Լ��Ƿ�������λ���Ա
	BOOL canKickUser();

	// �Լ��Ƿ��ܿ��Ʋλ���Ա������Ƶ
	BOOL canControlUser();
	// �Լ��Ƿ��ܽ��ܱ��˵Ŀ���
	BOOL isBeenControledUser();

	YuntaiMgr* getYuntaiMgr() const
	{
		return m_pYuntaiMgr;
	}

	// ��ȡ�ļ����������ָ��
	FileTransferMgr* getFileTransferMgr() const
	{
		return m_pFileTransferMgr;
	}

    // ��ȡָ�����湲���������ָ��
	DesktopManager* getDesktopManager() const
    {
        return m_pDesktopMgr;
    }

    // ��ȡ����Ƶ��������ָ��
    AVManager* getAVManager() const
    {
        return this->m_pAVManager;
    }

    // ��ȡָ������ҽ����ָ��
	CMeetingRoomFrame* getRoom()const
    {
        return m_pRoom;
    };

	// ��ȡ��������
	string getConferenceName() const;

    // ��ȡ����ID
	__int64 getConferenceId() const;

	// ��ȡ��ǰ�û�ID
	USERID getSelfId() const;

	// ��ȡ��ǰ�û�
	ConferenceUser* getSelf() const;

    // ���ݽ�ɫIDȡ�ý�ɫ����
    string getRoleName(__int64 nRoleID);

    // ��ȡĳ�������Ա
    ConferenceUser* getUser(USERID userID) const;

    // ���ĳ�������Ա����ʵ����
	string getUserRealName(USERID userId) const;

public:

	// ý���źŴ�������
	TransModel* m_pTransModel;

public:
	RunningConference(
		Conference* pConference,                 // �ٿ��Ļ���
		CMeetingRoomFrame* pRoom,                // �����ҽ���
		DBUser& dbUser,                          // �û���Ϣ
        LyvcMessage::MatrixC* pMatrixC,          // �ײ���Ϣϵͳ
		TransModel* pTransModel,                 // ý���źŴ�������
		ConferenceModelMgr* pConferenceModeMgr);  // ����ģʽ������

	~RunningConference();
	
	bool create();
	void destroy();

public:
	void cmdSetUserPicture( string fileName, __int64 receiverId = 0 );
    void evaluateVideoQuality( __int64 receiverId, int nQuality );

	// �Լ���������������Ϣ
    void cmdWritingMessage( __int64 receiverId, bool bFlag );

	// ָ��������
	void cmdAppointSpeaker( __int64 uid );

	// ֹͣ����
	void cmdStopSpeak( __int64 uid );

    // ���뷢��
	void cmdApplySpeak();

    // �տ�ĳ�ˣ�ͬʱֹͣ�տ������ˣ�Ȩ�޼��п���ģʽ���ܿؽ�ɫ����
    void cmdWatchUser(USERID userId, string beWatched, int nViewMode );

    // ����ĳ�ˣ�ͬʱֹͣ���������ˣ�Ȩ�޼��п���ģʽ���ܿؽ�ɫ����
    void cmdListenToUser(USERID userId, string beListened);

	// ����ĳ���û�
	void cmdKickUser(__int64 userId);

	// ��ֹĳ���û��μӴ˻���
	void cmdDeleteUserFromConference(__int64 userId);

    // ����������Ϣ��ĳ���û�
    void cmdChat(USERID userId, string strContent);

    // ����������Ϣ�������û�
    void cmdChatPublic(string strContent);

	// ����ĳ���û��������
	void cmdInviteConference(__int64 contactId, __int64 conferenceId);

	// ����������ע��Ϣ
	void cmdStartMarkWindow(__int64 uid);

	// ���ͻ�ֹͣ�����ҵ���Ƶ
	void sendMyVideo(BOOL bSend);

private:
	// delete �ӳٷ��͵Ĺ�����Ϣ
	void deleteDelaySendMsgs();

	// �����ӳٷ��͵Ĺ�����Ϣ
	void sendDelayMsgs();

    // �������
    void cmdJoinConference();

    // �˳�����
    void cmdQuitConference();

public:
    // Message Handler
    void JoinConferenceResponse(LyvcMessage::BaseMessage* pBaseMessage);
    void UserJoinConference(LyvcMessage::BaseMessage* pBaseMessage);
    void UserQuitConference(LyvcMessage::BaseMessage* pBaseMessage);
    void Broadcast(LyvcMessage::BaseMessage* pBaseMessage);
    void Chat(LyvcMessage::BaseMessage* pBaseMessage);
    void UserChannelBroken(LyvcMessage::BaseMessage* pBaseMessage);
    void StartMarkWindow(LyvcMessage::BaseMessage* pBaseMessage);
    void WatchUser(LyvcMessage::BaseMessage* pBaseMessage);
    void ListenToUser(LyvcMessage::BaseMessage* pBaseMessage);
	void ApplySpeak(LyvcMessage::BaseMessage* pBaseMessage);
	void AppointSpeaker(LyvcMessage::BaseMessage* pBaseMessage);
	void StopSpeak(LyvcMessage::BaseMessage* pBaseMessage);
	void WritingMessage(LyvcMessage::BaseMessage* pBaseMessage);
	void EvaluateVideoQuality(LyvcMessage::BaseMessage* pBaseMessage);
	void SetUserPicture(LyvcMessage::BaseMessage* pBaseMessage);

};
#endif //CONFERENCE_H
