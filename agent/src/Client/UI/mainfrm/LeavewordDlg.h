#pragma once

#include "..\pub\DialogEx.h"

// CLeavewordDlg �Ի���

class CLeavewordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLeavewordDlg)

public:
	CLeavewordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLeavewordDlg();

// �Ի�������
	enum { IDD = IDD_LEAVEWORD_DLG };

	CString m_strLeaveword;
	CRect   m_showRect;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
