#pragma once

#include "..\pub\treectrlex.h"
#include "..\pub\SkinScroll\SkinScrollWnd.h"
#include "..\pub\SkinScroll\SkinScrollBar.h"

class CMainFrame;
class LServer;
// SysinfoDlg.h : header file
//
#define LEAVEWORD 1
#define CONFNOTICE 2
#define SYSTEMMSG 3
/////////////////////////////////////////////////////////////////////////////
// CSysinfoDlg dialog

class CSysinfoDlg : public CDialog
{
// Construction
public:
	CSysinfoDlg(CMainFrame* pMainFrame, CWnd* pParent = NULL);   // standard constructor
	enum { IDD = IDD_SYSINFO_DLG };

public:
	/* ContactMgr���ýӿ� */
	// �յ�����
	void notifyLeaveword(string content, string senderName, int index, string sendDate, LServer* pServer);
	// �յ�����֪ͨ
	void notifyConfNotice(string title, string content, string sendDate, __int64 confId, LServer* pServer);
	// �յ�ϵͳ����
	void notifySystemMsg(string title, string content, string sendDate, LServer* pServer);

	/* ������� */
	// �õ���ǰѡ�еķ�����
	LServer* getCurSelServer();
	// ��ӷ�����
	void addServer( LServer* pServer );
	// �޸ķ�����
	void modifyServer( LServer* pServer );
	// ɾ��������
	void removeServer( LServer* pServer );
    // �鿴������Ϣ
	void lookMessage( LServer* pServer, int nType );
	// ��ʾ����
	void showContactMessage();

	void setSelectedServer( HTREEITEM hItem ) {	this->m_TreeCtrl.SelectItem( hItem ); };

private:
	void loadLeaveword( LServer* pServer );
	void loadSystemMsg( LServer* pServer );
	void loadConfNotice( LServer* pServer );
	// ��ʾ�������Ŀ
	void setChildrenNum( HTREEITEM hItem, int nDelta );
	int getItemIndex( HTREEITEM hParent, HTREEITEM hItem );
	void delMessageFromFile( int nIndex, int nType );
	void delAllMessageFromFile( int nType );

protected:
	// �����洰��
	CMainFrame*		m_pMainFrame;
	// ���ؼ�
	CTreeCtrlEx		m_TreeCtrl;
	// ���ؼ�����ʾ��ͼ��
	CImageList		m_ImageList;
	// ������
	HBITMAP			m_hBmpScrollBar;

	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnCancel() { };
	virtual void OnOK() { };
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNMDblclkSysinfoTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickSysinfoTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedSysinfoTree(NMHDR *pNMHDR, LRESULT *pResult);

	// �����˵��Ĵ������������洰��m_pMainFrame�ķ���
	afx_msg void OnLoginserver();
	afx_msg void OnCancelloginserver();
	afx_msg void OnLogoutserver();
	afx_msg void OnRegisternew();
	afx_msg void OnLoginanother();
	afx_msg void OnAddserver();
	afx_msg void OnCheckserver();
	afx_msg void OnRemoveserver();

	afx_msg void OnLookmessage();
	afx_msg void OnDelmessage();
	afx_msg void OnDelallmessage();
};

