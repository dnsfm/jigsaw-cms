#pragma once

#include "..\pub\DialogEx.h"

// CMsnDelContactDlg �Ի���

class CMsnDelContactDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMsnDelContactDlg)

public:
	CMsnDelContactDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMsnDelContactDlg();

// �Ի�������
	enum { IDD = IDD_MSN_DELCONTACT_DLG };
	BOOL m_bHide;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMsnHidecontact();
	afx_msg void OnBnClickedMsnDelcontact();
};
