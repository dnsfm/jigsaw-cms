#pragma once

#include "..\pub\DialogEx.h"

// CContactListDlg �Ի���

class CContactListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CContactListDlg)

public:
	CContactListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CContactListDlg();

// �Ի�������
	enum { IDD = IDD_CONTACT_LIST_DLG };

public:
	//��ѡ���û���id
	vector<USERID> m_selectedUserIds;
	//Ҫ��ʾ���û�id���û���
	vector<USERID> m_UserIds;
	vector<string> m_UserNames;
	//�Ի������
	CString m_strTitle;
	//��ʾ��Ϣ
	CString m_strMessage;
	CRect m_showRect;

private:
	void clearList();
	void fillList();
	
protected:
	CBrush m_brush;
	CListCtrl m_ListCtrl;
	CImageList m_ImageList;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnBnClickedCheckall();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
