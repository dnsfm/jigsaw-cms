// UI\MainFrm\UserInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "UserInfoDlg.h"
#include ".\userinfodlg.h"
#include "..\..\Model\LServer.h"
#include "userdefinedmessage.h"

// CUserInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CUserInfoDlg, CDialogEx)
CUserInfoDlg::CUserInfoDlg(LServer* pServer, CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserInfoDlg::IDD, pParent)
{
	m_pServer = pServer;
}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control( pDX, IDC_APPLY_BTN, m_btnApply );
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_APPLY_BTN, OnBnClickedApplyBtn)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHANGEPASSWORD, OnBnClickedChangepassword)
END_MESSAGE_MAP()


// CUserInfoDlg ��Ϣ�������

void CUserInfoDlg::OnBnClickedApplyBtn()
{
	CString str;
	if( !sendChangeUserInfo( str ) )
	{
		AfxMessageBox( str );
	}
	else
	{
		AfxMessageBox( "�޸���Ϣ�ɹ���" );
	}
}

void CUserInfoDlg::OnCancel()
{
	CDialogEx::OnCancel();
}

void CUserInfoDlg::OnOK()
{
	CString str;
	if( !sendChangeUserInfo( str ) )
	{
		AfxMessageBox( str );
		return;
	}
	else
	{
		AfxMessageBox( "�޸���Ϣ�ɹ���" );
	}
	CDialogEx::OnOK();
}

BOOL CUserInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	( (CEdit*)GetDlgItem(IDC_FIRSTNAME) )->LimitText( 200 );
//	( (CEdit*)GetDlgItem(IDC_LASTNAME) )->LimitText( 200 );
	( (CEdit*)GetDlgItem(IDC_EMAIL) )->LimitText( 200 );
	( (CEdit*)GetDlgItem(IDC_PASSWORD) )->LimitText( 200 );
	( (CEdit*)GetDlgItem(IDC_NEWPASSWORD) )->LimitText( 200 );
	( (CEdit*)GetDlgItem(IDC_CONFIRMNEWPASSWORD) )->LimitText( 200 );

	DBUser userInfo = m_pServer->getSelfInfo();
	GetDlgItem( IDC_USERNAME )->SetWindowText( userInfo.strName.c_str() );
	GetDlgItem( IDC_FIRSTNAME )->SetWindowText( userInfo.strFirstName.c_str() );
//	GetDlgItem( IDC_LASTNAME )->SetWindowText( userInfo.strLastName.c_str() );
	GetDlgItem( IDC_EMAIL )->SetWindowText( userInfo.strEmail.c_str() );

	m_btnApply.setBitmaps( IDB_BUTTON, IDB_BUTTON, IDB_BUTTON, IDB_BUTTONDISABLE );
	CRect rc;
	GetClientRect( &rc );
	m_btnOK.MoveWindow( rc.right - 240, rc.bottom - 32, 74, 22 );
	m_btnCancel.MoveWindow( rc.right - 160, rc.bottom - 32, 74, 22 );
	m_btnApply.MoveWindow( rc.right - 80, rc.bottom - 32, 74, 22 );

	this->m_sDescription = "�鿴/�޸ĸ�����Ϣ";

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CUserInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if( pWnd->GetDlgCtrlID() == IDC_STATIC_PWD
		|| pWnd->GetDlgCtrlID() == IDC_STATIC_NEWPWD
		|| pWnd->GetDlgCtrlID() == IDC_STATIC_CONFIRMPWD
		|| pWnd->GetDlgCtrlID() == IDC_USERNAME
		|| pWnd->GetDlgCtrlID() == IDC_CHANGEPASSWORD )
	{
		pDC->SetTextColor( m_crText );
		pDC->SetBkMode( TRANSPARENT );
		hbr = m_brush;
	}
	return hbr;
}

void CUserInfoDlg::OnBnClickedChangepassword()
{
	BOOL bVisible = ((CButton*)GetDlgItem(IDC_CHANGEPASSWORD))->GetCheck();
	GetDlgItem(IDC_PASSWORD)->ShowWindow( bVisible );
	GetDlgItem(IDC_NEWPASSWORD)->ShowWindow( bVisible );
	GetDlgItem(IDC_CONFIRMNEWPASSWORD)->ShowWindow( bVisible );
	GetDlgItem(IDC_STATIC_PWD)->ShowWindow( bVisible );
	GetDlgItem(IDC_STATIC_NEWPWD)->ShowWindow( bVisible );
	GetDlgItem(IDC_STATIC_CONFIRMPWD)->ShowWindow( bVisible );
}

BOOL CUserInfoDlg::validateUserInfo( CString& message )
{
	if( ((CButton*)GetDlgItem(IDC_CHANGEPASSWORD))->GetCheck() )
	{
		CString sPassword = m_pServer->getPassword().c_str();
		CString str;
		GetDlgItem(IDC_PASSWORD)->GetWindowText( str );
		if( sPassword != str )
		{
			message = "�������������";
			return FALSE;
		}
		GetDlgItem(IDC_NEWPASSWORD)->GetWindowText( sPassword );
		GetDlgItem(IDC_CONFIRMNEWPASSWORD)->GetWindowText( str );
		if( sPassword != str )
		{
			message = "ȷ���������������";
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CUserInfoDlg::sendChangeUserInfo( CString& message )
{
	if( !validateUserInfo( message ) )
		return FALSE;

	DBUser userInfo;
	userInfo.id = m_pServer->getId();
	CString str;
    GetDlgItem( IDC_USERNAME )->GetWindowText( str );
	userInfo.strName = str.GetString();
	GetDlgItem( IDC_FIRSTNAME )->GetWindowText( str );
	userInfo.strFirstName = str.GetString();
//	GetDlgItem( IDC_LASTNAME )->GetWindowText( str );
//	userInfo.strLastName = str.GetString();
	GetDlgItem( IDC_EMAIL )->GetWindowText( str );
	userInfo.strEmail = str.GetString();
	string password = m_pServer->getPassword();
	if( ((CButton*)GetDlgItem(IDC_CHANGEPASSWORD))->GetCheck() )
	{
		GetDlgItem( IDC_NEWPASSWORD )->GetWindowText( str );
		password = str.GetString();
	}

	DBUser oldInfo = m_pServer->getSelfInfo();
	if( oldInfo.strEmail == userInfo.strEmail 
		&& oldInfo.strFirstName == userInfo.strFirstName
//		&& oldInfo.strLastName == userInfo.strLastName
		&& password == m_pServer->getPassword() )
	{
		message = "û����Ϣ���޸ģ�";
		return FALSE;
	}
	if( m_pServer->getStatus() != SERVER_LOGIN )
	{
		message = "����û�е�¼�����ȵ�¼���������޸ĸ�����Ϣ��";
		return FALSE;
	}
	m_pServer->cmdChangeUserInfo( userInfo, password );
	return TRUE;
}
