#pragma once

#include "..\pub\treectrlex.h"
#include "..\pub\SkinScroll\SkinScrollWnd.h"
#include "..\pub\SkinScroll\SkinScrollBar.h"

// ConferenceDlg.h : header file
//
class CMainFrame;
class CMeetingRoomFrame;
class LServer;
class Conference;
class ConferenceMgr;
/////////////////////////////////////////////////////////////////////////////
// CConferenceDlg dialog

class CConferenceDlg : public CDialog
{
// Construction
public:
	CConferenceDlg(CMainFrame* pMainFrame, CWnd* pParent = NULL);   // standard constructor
	enum { IDD = IDD_CONFERENCE_DLG };

	void setMyPicture( string fileName, BOOL bShow );
	void addServer( LServer* pServer );
	void modifyServer( LServer* pServer );
	void removeServer( LServer* pServer );
	LServer* getCurSelServer();
	void setSelectedServer( HTREEITEM hItem ) {	this->m_TreeCtrl.SelectItem( hItem ); };

	// �Ƿ���Ա༭��ɾ������
	BOOL canEditConference();
	BOOL canDeleteConference();
	// �Ƿ���Լ�����˳�����,�ж�����: �����Ƿ�ɼ����Ƿ�ѡ�н����еĻ�����Ƿ��Ѿ��������
	BOOL canJoinOrQuitConference( BOOL bCanJoin );
	// �Ƿ���Բ鿴������Ϣ
	BOOL canLookConference();
	// �������Ƿ��д򿪵Ļ�����
	BOOL hasRoomOpened( LServer* pServer );
	// ���з������Ƿ��д򿪵Ļ�����
	BOOL hasRoomOpened();
	// �жϻ������Ƿ����
	BOOL isRoomExist( LServer* pServer, __int64 conferenceId );
	// ��ʾָ��������
	void showRoom( LServer* pServer, __int64 conferenceId );
	// �˳����л�����
	void quitAllRoom( LServer* pServer );
	void serverDisconnect( LServer* pServer );
	void serverReconnect( LServer* pServer, Conference* pConference );


	// ���һ������
	void notifyAddConference( Conference* pConference, LServer* pServer );
	// ����һ������
	void notifyConferenceFinish( Conference* pConference, LServer* pServer );
	// ɾ��һ��������
	void notifyDeleteConference( Conference* pConference, LServer* pServer );
	// �޸Ļ���
	void notifyModifyConference( Conference* pConference, LServer* pServer );
	// ���鿪ʼ
	void notifyStartConference( Conference* pConference, LServer* pServer );
	// ������������
	void notifyInviteConference( Conference* pConference, LServer* pServer, int nShow );
	// �����������
	void notifyKickUserFromConference( __int64 confId, LServer* pServer );

protected:
	// ���������ҽ���
    CMeetingRoomFrame* createRoomFrame( LServer* pServer, string sConferenceName, int nShow );
	ConferenceMgr* getCurSelConferenceMgr();
	void setChildrenNum( HTREEITEM hItem, int nDelta );
	// �õ�ָ������Ļ����ҽ���
	CMeetingRoomFrame* getRoomById( LServer* pServer, __int64 conferenceId );

	// �������б�
	typedef vector<CMeetingRoomFrame*> RoomList;
	typedef map<LServer*, RoomList> RoomMap;
	RoomMap			m_rooms;
	CMainFrame*		m_pMainFrame;
	CTreeCtrlEx		m_TreeCtrl;
	CImageList		m_ImageList;
	HBITMAP			m_hBmpScrollBar;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMRclickConferenceTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkConferenceTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedConferenceTree(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK() {};
	virtual void OnCancel() {};
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnRoomClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnKickFromRoom(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnLookConference();
	afx_msg void OnJoinConference();
	afx_msg void OnQuitConference();
	afx_msg void OnLoginserver();
	afx_msg void OnCancelloginserver();
	afx_msg void OnLogoutserver();
	afx_msg void OnRegisternew();
	afx_msg void OnLoginanother();
	afx_msg void OnAddserver();
	afx_msg void OnCheckserver();
	afx_msg void OnRemoveserver();
	afx_msg void OnEditconference();
	afx_msg void OnDeleteconference();
	afx_msg void OnEditconferencenotice();
	afx_msg void OnLookconferencenotice();
};
