#pragma once

#include "..\pub\DialogEx.h"

class LServer;
class RegisterUserMgr;
// CRegisterUserDlg �Ի���

class CRegisterUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterUserDlg)

public:
	CRegisterUserDlg(LServer* pServer, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegisterUserDlg();

// �Ի�������
	enum { IDD = IDD_USERREGISTER_DLG };

protected:
	LServer* m_pServer;
	RegisterUserMgr* m_pRegisterMgr;

	CString m_sUsername;
	CString m_sPassword;
	CString m_sConfirmPassword;
	CString m_sLastName;
	CString m_sFirstName;
	CString m_sEmail;
	BOOL m_bLoginAfterRegister;

	BOOL validateRegisterInfo();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnRegisterUserResponse( WPARAM wParam, LPARAM lParam );
	virtual void OnCancel();
};
