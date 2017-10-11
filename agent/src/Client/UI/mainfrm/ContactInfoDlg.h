#pragma once

#include "..\pub\DialogEx.h"

// CContactInfoDlg �Ի���

class CContactInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CContactInfoDlg)

public:
	CContactInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CContactInfoDlg();

// �Ի�������
	enum { IDD = IDD_CONTACT_INFO_DLG };

	CString m_sName;
	CString m_sEmail;
	CString m_sStatus;
	CString m_sGroup;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
