#pragma once

#include "..\pub\DialogEx.h"

// CMsnAccountDlg �Ի���

class CMsnAccountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMsnAccountDlg)

public:
	CMsnAccountDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMsnAccountDlg();
	BOOL m_bReadOnly;
	CString m_sAccount;
	CString m_sPassword;

// �Ի�������
	enum { IDD = IDD_MSNACCOUNT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
