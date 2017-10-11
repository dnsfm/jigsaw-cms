#ifndef LServer_H
#define LServer_H

#include "FLVCC.h"
#include "message/MatrixC/MatrixCLib/MessageTarget.h"
#include "model/DBUser.h"

#define CONTACTDLG_ITEM		1
#define CONFERENCEDLG_ITEM	2
#define SYSMSGDLG_ITEM		3

#define NORMAL_USER							0
#define SYSTEM_MANAGER						1
#define CONFERENCE_MANAGER					2
#define GROUP_MANAGER						3
#define CONFERENCE_AND_GROUP_MANAGER		4

class Contact;
class ContactMgr;
class CMeetingRoomFrame;
class TransModel;
class ConferenceMgr;
class ConferenceModelMgr;
class RunningConference;
class MultiConferenceMatrixC;
class CMainFrame;
class CooperationManager;

//����Ҫע��Ļ��������
class LServer : public LyvcMessage::MessageTarget {

public:
	LServer(CooperationManager* pCooperManager, CMainFrame* pMainFrame,	string sServerName, string IP, int port);
	~LServer();
	bool create();
	void destroy();

private:
	// ��Server��Ӧ�Ľ���CMainFrameָ��,��Ҫ���洦����¼�����CMainFrame�ṩ�ķ���
	CMainFrame*   m_pMainFrame;
    // ����Ƶ��Դ�������
	CooperationManager* m_pCooperManager;
	// ����������
	string  m_sServerName;
	// ��������ַ���˿�
	string	m_sIP;
	int		m_nPort;
	// ¼ʱʹ�õ��ʻ�������
	string	m_sUserName;
	string	m_sPassword;
	// ������״̬
	UINT	m_nStatus;	
	// �Ƿ���Ĭ�Ϸ�����
	BOOL	m_bDefaultServer;
	// �Ƿ��ס��¼���û�������
	BOOL	m_bRememberUserPass;
	// �ڽ����Ӧ����
	HTREEITEM m_htiContact, m_htiConference, m_htiSysmsg;
	// ��־id
	UINT m_nServerId;
	// ��������������ַ
	string m_sDeleteConferenceURL;
	string m_sCreateConferenceNoticeURL;
	string m_sCreateBulletinURL;
	string m_sEditConferenceURL;
	string m_sConferenceModeMgrURL;
	string m_sSystemRoleMgrURL;
	string m_sCommonContactMgrURL;
	string m_sCreateFromalConferenceURL;
	string m_sSelfInfoMgrURL;
	// �û�ע����ַ
	string m_sUserRegisterURL;
	// �ͻ���������ַ
	string m_sClientDownloadURL;

	__int64 m_expertId;
	__int64 m_confIdFromWeb;

public:
	void setTreeItem( HTREEITEM hItem, int nType );
	HTREEITEM getTreeItem( int nType );
	CMainFrame* getMainFrame() { return m_pMainFrame; };
	void setServerName( string sName ) { m_sServerName = sName; };
	string getServerName() { return m_sServerName; };
	void setIP( string sIP ) { m_sIP = sIP; };
	string getIP() { return m_sIP; };
	void setPort( int port ) { m_nPort = port; };
	int getPort() { return m_nPort; };
	void setStatus( UINT nStatus ) { m_nStatus = nStatus; };
	UINT getStatus() { return m_nStatus; };
	void setUserName( string sName ) { m_sUserName = sName; };
	string getUserName()const{return m_sUserName;};
	void setPassword( string sPassword ) { m_sPassword = sPassword; };
	string getPassword()const{return m_sPassword;};
	void setDefaultServer( BOOL bDefault = TRUE ) { m_bDefaultServer = bDefault; };
	BOOL isDefaultServer() { return m_bDefaultServer; };
	void setRememberUserPass( BOOL bFlag = TRUE ) { m_bRememberUserPass = bFlag; };
	BOOL isRememberUserPass() { return m_bRememberUserPass; };
	UINT getServerId() { return m_nServerId; };
	string getDeleteConferenceURL() { return m_sDeleteConferenceURL; };
	string getCreateConferenceNoticeURL() { return m_sCreateConferenceNoticeURL; };
	string getCreateBulletinURL() { return m_sCreateBulletinURL; };
	string getEditConferenceURL() { return m_sEditConferenceURL; };
	string getConferenceModeMgrURL() { return m_sConferenceModeMgrURL; };
	string getSystemRoleMgrURL() { return m_sSystemRoleMgrURL; };
	string getCommonContactMgrURL() { return m_sCommonContactMgrURL; };
	string getCreateFromalConferenceURL() { return m_sCreateFromalConferenceURL; };
	string getSelfInfoMgrURL() { return m_sSelfInfoMgrURL; };
	string getUserRegisterURL() { return m_sUserRegisterURL; };
	string getClientDownloadURL() { return m_sClientDownloadURL; };
	int getUserRole() { return m_selfInfo.userRole; };
	void setExpertId( __int64 id ) { m_expertId = id; };
	__int64 getExpertId() { return m_expertId; };
	void setConfIdFromWeb( __int64 id ) { m_confIdFromWeb = id; };
	__int64 getConfIdFromWeb() { return m_confIdFromWeb; };

protected:
	/*
	 * �û�������Ϣ
	 */
   	DBUser m_selfInfo;

	// ���ø�����Ϣ
	void setSelfInfo(const DBUser& dbUser) {m_selfInfo = dbUser;};

public:
	// ��ȡ������Ϣ
	DBUser getSelfInfo()const {return m_selfInfo;};

	// ���ID
	USERID getId() const {return m_selfInfo.id;};

	// ���Email
    string getEmail()const {return m_selfInfo.strEmail;};

	// ���ȫ��
    string getRealName()const {return m_selfInfo.getRealName();};

	//�û���¼����
	void cmdLogin();

	void cmdKeepAlive();

	string getRemoteIP();

	// �޸ĸ�����Ϣ
	void cmdChangeUserInfo( DBUser userInfo, string password );

protected:
	// ���汾
    void cmdCheckVersion();

	// ��ȡý���������ַ
	void cmdGetMediaServerAddr() const;	

protected:

	// ����ģʽ������
    ConferenceModelMgr* m_pConferenceModeMgr;

public:

	ConferenceModelMgr* getConferenceModeMgr() const
	{
		return m_pConferenceModeMgr;
	}

protected:

	// ���������
	ConferenceMgr* m_pConferenceMgr;

public:

    ConferenceMgr* getConferenceMgr() const
	{
		return m_pConferenceMgr;
	};

private:

	// ý����Ϣ��������
	TransModel*		m_pTransModel;

public:

    TransModel* getTransModel() const
	{
		return m_pTransModel;
	};

private:

	// ��ϵ�˹�����
    ContactMgr*			m_pContactMgr;

public:

    // ��ȡ��ϵ�˹�����
    ContactMgr* getContactMgr() const
	{
	    return this->m_pContactMgr;
	};

public:
    // MessageHandler
    void UserLoginResponse(LyvcMessage::BaseMessage* pMessage);
    void UserDetail(LyvcMessage::BaseMessage* pMessage);
    void MediaServerAddress(LyvcMessage::BaseMessage* pMessage);
    void ServerInternalError(LyvcMessage::BaseMessage* pMessage);
	void CheckVersion(LyvcMessage::BaseMessage* pMessage);
	void Advertizement(LyvcMessage::BaseMessage* pMessage);
	void ServerInfo(LyvcMessage::BaseMessage* pMessage);
	void KickDuplicateLogin(LyvcMessage::BaseMessage* pMessage);
	void LoginSuccessfully(LyvcMessage::BaseMessage* pMessage);
	void KeepAlive(LyvcMessage::BaseMessage* pMessage);
    // Exception Hanlder
    void ExceptionHandler(LyvcMessage::BaseMessage* pMessage);

};

#endif //LSERVER_H
