#pragma once

#include "ui\pub\entabctrl.h"

class CChatDlg;
class CVideoBgDlg;
class CWhiteboardDlg;
class CTabItem;

// ��ʾ
class ChatAlerter : public CObject
{
public:
	ChatAlerter()
	{
		m_bFlag = TRUE;
		++m_nCount;
	}
	~ChatAlerter()
	{}

	BOOL m_bFlag;
private:
	ChatAlerter(const ChatAlerter &);
	ChatAlerter & operator = (const ChatAlerter &);

	USERID m_userId;
	static int m_nCount;
	int m_nTimerId;
public:
	static int GetCount()
	{
		return m_nCount;
	}
	void SetTimerId(int nTimerId)
	{
		m_nTimerId = nTimerId;
	}
	int GetTimerId()
	{
		return m_nTimerId;
	}
	USERID GetChatwithId()
	{
		return m_userId;
	}
	void SetChatwithId(USERID uid)
	{
		m_userId = uid;
	}
};

// CChatTab

class CChatTab : public CEnTabCtrl
{
	DECLARE_DYNAMIC(CChatTab)

public:
	CChatTab();
	virtual ~CChatTab();

	CHARFORMAT getCharFormat();
	void setCharFormat( CHARFORMAT cf );
	void loadCharFormat();
	void saveCharFormat();

	//����ĳ������������Ϣ
	void notifyWritingMessage( __int64 receiverId, __int64 senderId, bool bFlag );
	// �����ĳ�˵�����Ի���
	int addChatwith(USERID uid, CString strName, BOOL bShow = FALSE);
	// �ر���ĳ�˵�����Ի���
	void closeChatwith(USERID uid);
	// ���������Ϣ
	void addChatMsg(USERID with, CString name, CString msg, BOOL bPublic);
	// �����ʾ��Ϣ
	void addMessage( string msg );
	// �������촰�ڵķָ���λ��
	int getSplitterPosition();
	void setSplitterPosition( int nPos );
	// �ڱ�ǩ����ӻ�ر���Ƶ����
	void createVideoBgDlg();
	CVideoBgDlg* getVideoBgDlg();
	void removeVideoBgTab();
	void addVideoBgTab();
	// �ڱ�ǩ����ӻ�رհװ崰��
	void createWhiteboardDlg();
	CWhiteboardDlg* getWhiteboardDlg();
	void removeWhiteboardTab();
	void addWhiteboardTab();

private:
	// ��ʾ��ǰ��ǩҳ��Ӧ�Ĵ���
	void setCurSelWnd( int nIndex );
	// ɾ����ʾ����
	void delAlert(USERID uid);
	// ���ñ�ǩ���ͼƬ
	void setItemImage(int nItem, int nImage);
	// ��ʾ������Ϣ��
	void addAlert(int n, USERID with);
	// �Ƿ��Ѵ�����ʾ
	BOOL isAlertExist(USERID uid);
	// ����id�ҵ���Ӧ�ı�ǩ������
	int findItemIndexById(USERID uid);
	// ����id�ҵ���Ӧ��CTabItem
	CTabItem* findTabItemById(USERID uid, int nType);
	// ����id�ҵ���Ӧ�����촰��
	CChatDlg* findChatDlgById(USERID uid);
	// �������
	void adjustTabItemIndex( int nStartAfter );
	// ��Ӻ�ɾ����ǩ
	int insertItem( int nIndex, CString sText, int nImage, LPARAM lParam );
	void deleteItem( int nIndex );

private:
	// ���еı�ǩҳ�Ӵ���
	vector<CTabItem*> m_ChildWnds;
	// ��ʾ����
	CPtrList m_AlerterList;
    // Ҫ���رյ�item�����
	int m_nToBeClosed;
	// ��������
	CHARFORMAT m_cfChat;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCloseChatDlg();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};


