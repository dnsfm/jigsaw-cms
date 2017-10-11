// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

class LServer;
class CYuntaiDlg;
class CControlSpeakDlg;
class CControlDlg;
class CRoomView;
class CFileTransferDlg;
class CMarkWnd;
class RunningConference;
class ConferenceUser;
class CFileTransferMgrDlg;
class CAttenderDlg;
class CStatusBarDlg;
class CWhiteboardDlg;

class CMeetingRoomFrame : public CFrameWnd
{	
	DECLARE_DYNAMIC(CMeetingRoomFrame)

public:
	CMeetingRoomFrame(LServer* pServer, CWnd* pWnd);
	virtual ~CMeetingRoomFrame();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_adUrl;
	CString	m_sUserConfigFile;

	// ʵ��
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void serverDisconnect();
	void serverReconnect();
	void setSplitterPosition();
	void notifyConferenceMsg( string msg );

	void notifyShowUserPicture( __int64 uid, string fileName );
	void notifyEvaluateVideoQuality( __int64 userId, int quality );
	void notifyWritingMessage( __int64 receiverId, __int64 senderId, bool bFlag );
	void notifyApplySpeak( __int64 applyerId );
	void notifyAppointSpeaker( __int64 senderId, __int64 speakerId );
	void notifyStopSpeak( __int64 senderId, __int64 speakerId );

	// �����Ƿ�����Ƶ�ı�־
	void setSendMyVideoFlag( BOOL bSend );
	//������ʾĳ���λ���Ա����
	void popupAttenderDlg( __int64 uid );
	//�ջ���ʾ���вλ���Ա����
	void popbackAllVideoDlg( int nMode );
	//������ʾģʽ
	void setViewMode( int nMode );
	//��ӻ�����Ա
	void addConferenceUser(ConferenceUser* pConfUser);
	//ɾ��������Ա
	void deleteConferenceUser(USERID uid, bool bVirtualUser = false);
	int getConfUserCount();
	//�յ�������Ϣ,bPublic��ʾ�Ƿ��ǹ�����
	void receivedChatMessage(USERID senderId, string msg, BOOL bPublic = FALSE);
	//ֹͣ�ۿ�ĳ�˵���Ƶ����Ҫ�ص��������
	void closeVideoWindow(USERID uid);
	//�ۿ�ĳ�˵���Ƶ
	void showVideoWindow(USERID uid);
	//��ȡ������Ƶ����
	HWND getLocalVideoWindow();
	//��ȡ����ͨ��ѹ�����ɼ�����Ƶ����
	HWND getLocalCompressionVideoWindow(USERID uid);
	//��ȡ�ļ�����Ի���
	CFileTransferDlg* getSendFileDlg();
	CFileTransferDlg* getRecvFileDlg();
	CYuntaiDlg* getYuntaiDlg();
	void addYuntaiHolder( __int64 uid, int nCommPort );
	CWhiteboardDlg* getWhiteboardDlg();

	void setMyPicture();
	void setMyPicture( string fileName, BOOL bShow );
	void evaluateVideoQuality( __int64 userId, int quality );
	string getConferenceName();
	string getServerIP();
	CString getUserConfigFile();
	BOOL isContact( __int64 uid );
	void applyContact(  __int64 uid );
	void sendWritingMessageFlag( __int64 receiverId, bool bFlag );
	//��̨����
	void yuntaiControl( __int64 uid );
	// �����ļ�
	void sendFile();
	void dragFileToSend( CString fileName, __int64 uid );
	void applySendFile( vector<__int64> ids );
	// �����Ƿ����������ı�־
	void setIsListenFlag(bool bIsListen, __int64 uid);
	//�����촰�����һ��
	void addChatwith(__int64 uid);
	//�û���ConferenceDlg�����˳������ҵ���
	void exit();
	//���û���ָ��
	void setConference(RunningConference* pConf);

    // ����Ƶ���
	void startVideo(__int64 uid);
	void stopVideo(__int64 uid);
	void startAudio(__int64 uid);
	void stopAudio(__int64 uid);
	BOOL canStartVideo(__int64 uid);
	BOOL canStopVideo(__int64 uid);
    BOOL canStartAudio(__int64 uid);
    BOOL canStopAudio(__int64 uid);

	void setFrameRateAndKeyFrameInterval(int frameRate, int keyFrameInterval);

	//�����RunningConference�ķ���
	void kickUserFromRoom( __int64 userId );
	void deleteUserFromConference( __int64 userId );
	void getConferneceUsers( vector<__int64>& v );
	BOOL isInstantConference();
	__int64 getConferenceId();
	__int64 getSelfId();
	string getSelfName();
	string getSelfUserName();
	string getUserNameById(__int64 uid);
	BOOL isUserInConference( __int64 uid );
	BOOL isBeenControledUser();
	void sendChatMsg(CString msg, USERID uid);
	void watchUser( __int64 uid, string beWatched, int nViewMode );
	void listenToUser( __int64 uid, string beListened );
	void sendMyVideo(BOOL bSend);
	void appointSpeaker( __int64 uid );
	void stopSpeaker( __int64 uid );
    BOOL canKickUser();
	BOOL canSendFile();
    BOOL canSendFileToUser( __int64 uid = 0 );
	BOOL canInviteUser();

	//�����DesktopManager��һЩ����
	void inviteDesktop(__int64 uid);
	void stopSendDesktop(__int64 uid);
	void applyDesktop(__int64 uid);
	void stopReceiveDesktop(__int64 uid);
	void applyControlDesktop(__int64 uid);
	void stopSendControlDesktop(__int64 uid);
	void stopReceiveControlDesktop();

	BOOL canInviteDesktop(__int64 uid);
	BOOL canStopSendDesktopToUser(__int64 uid);
	BOOL canApplyDesktop(__int64 uid = 0);
	BOOL canStopReceiveDesktopFromUser(__int64 uid);
	BOOL canApplyControlDesktop(__int64 uid);
	BOOL canStopSendControlDesktopToUser(__int64 uid);
	BOOL canStopReceiveControlDesktopFromUser(__int64 uid);

private:
	// �ر�ǰ����״̬�������ļ�
	void writeIni();
	// �л���ʾģʽ
	void switchViewmode();

private:
	__int64					m_nConfId;
	string					m_strConfName;
	RunningConference*		m_pConference;	//��������
	LServer*				m_pServer;

	CWnd*					m_pParentWnd;// �ر�ʱҪ֪ͨ�Ĵ���
	CYuntaiDlg*				m_pYuntaiDlg;
	CControlSpeakDlg*		m_pControlSpeakDlg;
	CControlDlg*			m_pControlDlg;	//���п��ƴ���
	CRoomView*				m_pRoomView;
	CMarkWnd*				m_pMarkWnd;		//��ע����
	CTime					m_timeEnterRoom;
	CFileTransferMgrDlg*	m_pFileTransferMgrDlg;
	CStatusBarDlg*			m_pStatusBarDlg;

	CToolBar				m_wndToolBar,m_wndColorBar;

	BOOL					m_bIsSpeaking;
	BOOL					m_bIsApplyingSpeak;
	BOOL					m_bIsInitChatDlgSplitterPos;

private:  
	// ���ɵ���Ϣӳ�亯��
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnTimer(UINT nIDEvent);

public:
	// ����˵���
	afx_msg void OnConferenceInfo();
	afx_msg void OnViewconfhistory();
	afx_msg void OnInviteConference();
	afx_msg void OnUpdateInviteConference(CCmdUI *pCmdUI);
	afx_msg void OnKickUser();
	afx_msg void OnUpdateKickUser(CCmdUI *pCmdUI);
	afx_msg void OnCenterControl();
	afx_msg void OnUpdateCenterControl(CCmdUI *pCmdUI);
	afx_msg void OnSendFile();
	afx_msg void OnUpdateSendFile(CCmdUI *pCmdUI);
	afx_msg void OnOpenReceived();
	afx_msg void OnExit();
	afx_msg void OnApplyspeak();
	afx_msg void OnUpdateApplyspeak(CCmdUI *pCmdUI);
	afx_msg void OnControlspeak();
	afx_msg void OnUpdateControlspeak(CCmdUI *pCmdUI);

	// �鿴�˵���
	afx_msg void OnViewConfuserlist();
	afx_msg void OnUpdateViewConfuserlist(CCmdUI *pCmdUI);
	afx_msg void OnSortattenders();
	afx_msg void OnViewNormal();
	afx_msg void OnUpdateViewNormal(CCmdUI *pCmdUI);
	afx_msg void OnViewOneVga();
	afx_msg void OnUpdateViewOneVga(CCmdUI *pCmdUI);
	afx_msg void OnViewDialog();
	afx_msg void OnUpdateViewDialog(CCmdUI *pCmdUI);
	afx_msg void OnViewFourCif();
	afx_msg void OnUpdateViewFourCif(CCmdUI *pCmdUI);
	afx_msg void OnViewSixteenQcif();
	afx_msg void OnUpdateViewSixteenQcif(CCmdUI *pCmdUI);
	afx_msg void OnSeprateVideo();
	afx_msg void OnUpdateSeprateVideo(CCmdUI *pCmdUI);

	// ����Ƶ�˵���
	afx_msg void OnApplyVideo();
	afx_msg void OnUpdateApplyVideo(CCmdUI *pCmdUI);
	afx_msg void OnStopReceiveVideo();
	afx_msg void OnUpdateStopReceiveVideo(CCmdUI *pCmdUI);
	afx_msg void OnStartListen();
    afx_msg void OnUpdateStartListen(CCmdUI *pCmdUI);
	afx_msg void OnStopListen();
    afx_msg void OnUpdateStopListen(CCmdUI *pCmdUI);
	afx_msg void OnYuntaicontrol();
	afx_msg void OnUpdateYuntaicontrol(CCmdUI *pCmdUI);
	afx_msg void OnChangevideoquality();

	// Զ�̹�������Ʋ˵���
	afx_msg void OnStartDesktopServer();
	afx_msg void OnUpdateStartDesktopServer(CCmdUI *pCmdUI);
	afx_msg void OnStopDesktopServer();
	afx_msg void OnUpdateStopDesktopServer(CCmdUI *pCmdUI);
	afx_msg void OnApplyDesktopShare();
	afx_msg void OnUpdateApplyDesktopShare(CCmdUI *pCmdUI);
	afx_msg void OnStopDesktopShare();
	afx_msg void OnUpdateStopDesktopShare(CCmdUI *pCmdUI);
	afx_msg void OnApplyDesktopControl();
	afx_msg void OnUpdateApplyDesktopControl(CCmdUI *pCmdUI);
	afx_msg void OnStopDesktopControl();
	afx_msg void OnUpdateStopDesktopControl(CCmdUI *pCmdUI);
	afx_msg void OnStopReceiveDesktopControl();
	afx_msg void OnUpdateStopReceiveDesktopControl(CCmdUI *pCmdUI);
	afx_msg void OnMark();
	afx_msg void OnUpdateMark(CCmdUI *pCmdUI);

	// �����˵���
	afx_msg void OnHelpContent();

	// �Զ�����Ϣ������
    afx_msg LRESULT OnReceiveApplyDesktopMsg(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnReceiveInviteDesktopMsg(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnReceiveApplyControlDesktopMsg(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnReceiveApplySendfileMsg(WPARAM wParam, LPARAM lParam);

	// �װ�Ĺ�����
	afx_msg void OnNewWhiteboard();
    afx_msg void OnFileOpen();
	afx_msg void OnSaveWhiteboard();
	afx_msg void OnRubber();
	afx_msg void OnUpdateRubber(CCmdUI* pCmdUI);

	afx_msg void OnSelect();
	afx_msg void OnUpdateSelect(CCmdUI* pCmdUI);
	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnRectangle();
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnEllipse();
	afx_msg void OnUpdateEllipse(CCmdUI* pCmdUI);
	afx_msg void OnCircle();
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void OnPoly();
	afx_msg void OnUpdatePoly(CCmdUI* pCmdUI);
	afx_msg void OnCurve();
	afx_msg void OnUpdateCurve(CCmdUI* pCmdUI);
	afx_msg void OnText();
	afx_msg void OnUpdateText(CCmdUI* pCmdUI);
	afx_msg void OnWidthThin();
	afx_msg void OnUpdateWidthThin(CCmdUI* pCmdUI);
	afx_msg void OnWidthNormal();
	afx_msg void OnUpdateWidthNormal(CCmdUI* pCmdUI);
	afx_msg void OnWidthWide();
	afx_msg void OnUpdateWidthWide(CCmdUI* pCmdUI);
	afx_msg void OnFillFalse();
	afx_msg void OnUpdateFillFalse(CCmdUI* pCmdUI);
	afx_msg void OnFillTrue();
	afx_msg void OnUpdateFillTrue(CCmdUI* pCmdUI);

	afx_msg void OnColorBlack();
	afx_msg void OnUpdateColorBlack(CCmdUI* pCmdUI);
	afx_msg void OnColorWhite();
	afx_msg void OnUpdateColorWhite(CCmdUI* pCmdUI);
	afx_msg void OnColorGray();
	afx_msg void OnUpdateColorGray(CCmdUI* pCmdUI);
	afx_msg void OnColorRed();
	afx_msg void OnUpdateColorRed(CCmdUI* pCmdUI);
	afx_msg void OnColorGreen();
	afx_msg void OnUpdateColorGreen(CCmdUI* pCmdUI);
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorBlue(CCmdUI* pCmdUI);
	afx_msg void OnColorPink();
	afx_msg void OnUpdateColorPink(CCmdUI* pCmdUI);
	afx_msg void OnColorYellow();
	afx_msg void OnUpdateColorYellow(CCmdUI* pCmdUI);
	afx_msg void OnColorCyan();
	afx_msg void OnUpdateColorCyan(CCmdUI* pCmdUI);

	afx_msg void OnSmallText();
	afx_msg void OnUpdateSmallText(CCmdUI* pCmdUI);
	afx_msg void OnNormalText();
	afx_msg void OnUpdateNormalText(CCmdUI* pCmdUI);
	afx_msg void OnBigText();
	afx_msg void OnUpdateBigText(CCmdUI* pCmdUI);
};


