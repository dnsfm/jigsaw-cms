#pragma once

#include "resource.h"
#include "RichEditCtrlEx.h"
#include "staticsplitter.h"
#include "..\pub\linkbutton.h"
#include "..\pub\SkinScroll\SkinScrollWnd.h"
#include "..\pub\SkinScroll\SkinScrollBar.h"
#include "TabItem.h"

// CChatDlg �Ի���
class CChatDlg : public CDialog, public CTabItem
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChatDlg();
// �Ի�������
	enum { IDD = IDD_CHAT_DLG };

	void setCharFormat( CHARFORMAT cf );
	void sendWritingMessageFlag();
	void setWritingMessageFlag( __int64 userId, bool bFlag );
	// ���������Ϣ
	void appendMsg(CString name, CString msg);
	void appendSysMsg( CString msg );
	// �ָ����ƶ�
	void SplitterMoved(int pos);
	// ���÷ָ���λ��
	void SetSplitterPos(int pos);
	// ���´��ڿؼ�
	void UpdateSizes();
	void layout();

private:
	void saveChatMsg( CString date, CString time, CString sender, CString receiver, CString msg, CString file );

public:
	// �����˵�����
	CString				m_sChatWithName;
	// �ָ���λ��
	int					m_SplitterPos;

private:
	// ��ʾ������Ϣ
	CRichEditCtrlEx		m_ChatMsg;
	// ����������Ϣ
	CRichEditCtrlEx		m_SendMsg;
	// ���϶��ķָ���
	CStaticSplitter		m_Splitter;
	int					m_cy;
	int					m_nMinHeight;
	CBrush				m_brush;
	CLinkButton			m_btnFont;
	CLinkButton			m_btnSend;
	bool				m_bIsSendWritingMsg;
	CString				m_strWritingUser;
	HBITMAP				m_hBmpScrollBar;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedFont();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	afx_msg void OnBnClickedSend();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};
