// MainFrm.h : interface of the CMainFrame class
//
#pragma once

#include "LoginDialog.h"

class Conference;
class LServer;
class CImageTabWnd;
class CContactDlg;
class CConferenceDlg;
class CSysinfoDlg;
class CMeetingRoomFrame;
class CAdBGDlg;

class CMainFrame : public CFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)	
public:
	CMainFrame();
	virtual ~CMainFrame();

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

/*
 * LServer��Ϣ�������
 */
	// ��¼�ɹ�
	void notifyLoginSuccessed( LServer* pServer );
	// ��¼ʧ��
	void notifyLoginFailed( const char* reason, LServer* pServer );
	// ���ͻ��˰汾
	void notifyCheckVersion( BOOL bHasNewVersion, BOOL bNeedUpdate, LServer* pServer );
	// ���ù���ַ
	void notifyAdvertizementAddress( CString sAdHomepage, CString sAdMainframe, CString sAdRoomframe );

	CContactDlg* getContactDlg() { return m_pContactDlg; };
	CConferenceDlg* getConferenceDlg() { return m_pConferenceDlg; };
	CSysinfoDlg* getSysinfoDlg() { return m_pSysmsgDlg; };
	LServer* getServerById( UINT nId );
	LServer* isServerExist( string sName, string sIP, int nPort, CString& str );
	BOOL isDuplicateServer( LServer* pServer, string sName, string sIP, int nPort, CString& str );
	LServer* addServer( string sName, string sIP, int nPort, string sUsername, string sPassword, BOOL bDefault = FALSE );

/*
 * �������
 */
	void OnViewAndModifyServer(LServer* pServer);
	afx_msg void OnAddServer();
	void OnRemoveServer(LServer* pServer);
	BOOL OnLoginServer(LServer* pServer, BOOL bAutoLogin = FALSE);
	void OnCancelLoginServer(LServer* pServer);
	void OnLogoutServer(LServer* pServer);
	void OnRegisterNewUser(LServer* pServer);
	void OnLoginAnother(LServer* pServer);
    
	//�ͻ����Ƿ��з������Ѿ���¼�����ڵ�¼
	BOOL hasServerLoginOrLogining();
	//����ϵͳ����ͼ�����ʾ����
	void SetTaskIcon(LServer* pServer, BOOL bShowCurUser);
	void SetTaskIcon( CString sServer, CString sUsername, CString sRealname, int nStatus, BOOL bShowCurUser );
	LServer* getDefaultServer();
	//�õ���ǰѡ�еķ�����
	LServer* getCurSelServer();

private:
	// ���ط�����
	void loadServer();
	void modifyServer( LServer* pServer );
	BOOL getUsernameAndPassword( string& sUsername, string& sPassword, BOOL& bMember );
	void saveServer();
	BOOL getServerInfo( CString str, string& sName, string& sIP, int& nPort, string& sUsername, string& sPassword );
	void removeServer( LServer* pServer );
	//������ǩ��
	void CreateImgTab();	
	//ɾ����ʾ��
	void removeNotifiers();
	//���������в���
	BOOL processCmdline(CString sCmd);
	//����������ת��������ʱ�ķ���,����ǰ��װĿ¼Ҫ��ͬ
	void transformData( LServer* pServer );

public:
    // ���ɷ�����id
	static UINT getServerId() { return m_nServerIdSeed++; };
	CString getRoomAdUrl() { return m_sAdRoomframe; };
	BOOL isLoginDlgVisable() { return m_dlgLogin.IsWindowVisible(); };

private:
	// �������б�
	map<UINT, LServer*> m_servers;
	// �������ɷ�����id
	static UINT		m_nServerIdSeed;
	// ����ַ
	CString			m_sAdHomepage;
	CString			m_sAdMainframe;
	CString			m_sAdRoomframe;
	//λͼ��ǩ����
	CImageTabWnd*	m_pImageTab;		
	//��ϵ�˶Ի���
	CContactDlg*	m_pContactDlg;		
	//�����б�Ի���
	CConferenceDlg*	m_pConferenceDlg;	
	//ϵͳ��Ϣ�Ի���
	CSysinfoDlg*	m_pSysmsgDlg;		
	//ϵͳ����
	NOTIFYICONDATA	m_TaskIcon;
	//������ʾ�����
	int				m_nNotifyId;
	//������ʾ���б�
	CPtrList		m_pTaskNotifyList;
	//��¼�Ի���
	CLoginDialog	m_dlgLogin;		
	// ���Ի���
	CAdBGDlg*		m_pAdBG;
	//������С��С
	int				m_nMinX, m_nMinY;
	BOOL			m_bShowAdDlg;
	BOOL			m_bFirstLogin;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);		
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

	//������ʾ��رյ���Ϣ�������б������
	afx_msg LRESULT OnTaskbarNotifierClosed(WPARAM wParam,LPARAM lParam);
	//��Ҫ������ʾ�����Ϣ����������ʾ��
	afx_msg LRESULT OnReceivedSysMsg(WPARAM wParam,LPARAM lParam);
	//weblauncher����Ϣ����
	afx_msg LRESULT OnReceivedMsgFromWeblauncher(WPARAM wParam,LPARAM lParam);
	//ϵͳ���̵���Ϣ����
	afx_msg LRESULT OnShellTrayIcon(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDisconnectServer(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnLoginFailed(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCheckVersion(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDuplicateLogin(WPARAM wParam, LPARAM lParam);

	//�ļ��˵���
	afx_msg void OnLogin();
	afx_msg void OnUpdateLogin(CCmdUI *pCmdUI);
	afx_msg void OnLogout();
	afx_msg void OnUpdateLogout(CCmdUI *pCmdUI);
	afx_msg void OnLookLeavewords();
	afx_msg void OnUpdateLookLeavewords(CCmdUI *pCmdUI);
	afx_msg void OnOpenReceived();
	afx_msg void OnCloseWnd();

	//��ϵ�˲˵���
	afx_msg void OnSearchContact();	
	afx_msg void OnUpdateSearchContact(CCmdUI *pCmdUI);
	afx_msg void OnSendLeaveword();
	afx_msg void OnUpdateSendLeaveword(CCmdUI *pCmdUI);
	afx_msg void OnSendEmail();
	afx_msg void OnUpdateSendEmail(CCmdUI *pCmdUI);
	afx_msg void OnDelContact();
	afx_msg void OnUpdateDelContact(CCmdUI *pCmdUI);
	afx_msg void OnPropertyContact();
	afx_msg void OnUpdatePropertyContact(CCmdUI *pCmdUI);
	afx_msg void OnCreateContactGroup();
	afx_msg void OnUpdateCreateContactGroup(CCmdUI *pCmdUI);
	afx_msg void OnDelContactGroup();
	afx_msg void OnUpdateDelContactGroup(CCmdUI *pCmdUI);
	afx_msg void OnRenameContactGroup();
	afx_msg void OnUpdateRenameContactGroup(CCmdUI *pCmdUI);
	afx_msg void OnCommoncontactmgr();
	afx_msg void OnUpdateCommoncontactmgr(CCmdUI *pCmdUI);

	//����˵���
	afx_msg void OnCreateInstantconf();
	afx_msg void OnUpdateCreateInstantconf(CCmdUI *pCmdUI);
	afx_msg void OnCreateformalconf();
	afx_msg void OnUpdateCreateformalconf(CCmdUI *pCmdUI);
	afx_msg void OnJoinConference();
	afx_msg void OnUpdateJoinConference(CCmdUI* pCmdUI);
	afx_msg void OnQuitConference();
	afx_msg void OnUpdateQuitConference(CCmdUI* pCmdUI);
	afx_msg void OnLookConference();
	afx_msg void OnUpdateLookConference(CCmdUI *pCmdUI);
	afx_msg void OnViewConfhistory();
	afx_msg void OnUpdateViewConfhistory(CCmdUI *pCmdUI);
//	afx_msg void OnConfmodemgr();
//	afx_msg void OnUpdateConfmodemgr(CCmdUI *pCmdUI);
//	afx_msg void OnSystemrolemgr();
//	afx_msg void OnUpdateSystemrolemgr(CCmdUI *pCmdUI);

	//���߲˵���
	afx_msg void OnAlwaysTop();
	afx_msg void OnUpdateAlwaysTop(CCmdUI *pCmdUI);
	afx_msg void OnSelfinfomgr();
	afx_msg void OnUpdateSelfinfomgr(CCmdUI *pCmdUI);
	afx_msg void OnSendsystemmsg();
	afx_msg void OnUpdateSendsystemmsg(CCmdUI *pCmdUI);
	afx_msg void OnAVWizard();
	afx_msg void OnUpdateAvWizard(CCmdUI *pCmdUI);
	afx_msg void OnSetpicture();
	afx_msg void OnOption();

	//�����˵���
	afx_msg void OnHelpContent();
	afx_msg void OnAbout();

	//ϵͳ���̵����˵���
	afx_msg void OnMenuHide();
	afx_msg void OnUpdateMenuHide(CCmdUI *pCmdUI);
	afx_msg void OnTrayMenuOpen();
	afx_msg void OnUpdateMenuShow(CCmdUI *pCmdUI);
	afx_msg void OnTrayMenuExit();
	afx_msg void OnAddserver2();
};
