#pragma once

#include "..\pub\DialogEx.h"

// GetNamePasswordDlg �Ի���

class GetNamePasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GetNamePasswordDlg)

public:
	GetNamePasswordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GetNamePasswordDlg();

// �Ի�������
	enum { IDD = IDD_GETNAMEPASSWORD_DLG };
	CString m_sUsername;
	CString m_sPassword;
	BOOL m_bRememberme;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
