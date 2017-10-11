// UI\MainFrm\RegisterUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "RegisterUserDlg.h"
#include ".\registeruserdlg.h"
#include "MainFrm.h"
#include "UserDefinedMessage.h"
#include "..\..\Model\LServer.h"
#include "..\..\Model\RegisterUserMgr.h"

// CRegisterUserDlg �Ի���

IMPLEMENT_DYNAMIC(CRegisterUserDlg, CDialogEx)
CRegisterUserDlg::CRegisterUserDlg( LServer* pServer, CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegisterUserDlg::IDD, pParent)
{
	m_pServer = pServer;
	m_pRegisterMgr = NULL;
}

CRegisterUserDlg::~CRegisterUserDlg()
{
}

void CRegisterUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text( pDX, IDC_USERNAME, m_sUsername );
	DDX_Text( pDX, IDC_PASSWORD, m_sPassword );
	DDX_Text( pDX, IDC_CONFIRMPASSWORD, m_sConfirmPassword );
	DDX_Text( pDX, IDC_LASTNAME, m_sLastName );
	DDX_Text( pDX, IDC_FIRSTNAME, m_sFirstName );
	DDX_Text( pDX, IDC_EMAIL, m_sEmail );
	DDX_Check( pDX, IDC_LOGIN_AFTER_REGISTER, m_bLoginAfterRegister );
}


BEGIN_MESSAGE_MAP(CRegisterUserDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_REGISTERUSER_RESPONSE, OnRegisterUserResponse)
END_MESSAGE_MAP()


// CRegisterUserDlg ��Ϣ�������

BOOL CRegisterUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	( (CEdit*)GetDlgItem(IDC_USERNAME) )->LimitText( 16 );
	( (CEdit*)GetDlgItem(IDC_FIRSTNAME) )->LimitText( 100 );
	( (CEdit*)GetDlgItem(IDC_LASTNAME) )->LimitText( 100 );
	( (CEdit*)GetDlgItem(IDC_EMAIL) )->LimitText( 200 );
	( (CEdit*)GetDlgItem(IDC_PASSWORD) )->LimitText( 12 );
	( (CEdit*)GetDlgItem(IDC_CONFIRMPASSWORD) )->LimitText( 12 );

	this->m_sDescription = "ע�����û�������д��������ע����Ϣ��";

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CRegisterUserDlg::OnOK()
{
	UpdateData();
	if( !validateRegisterInfo() )
	{
		return;
	}
	if( this->m_pRegisterMgr == NULL )
	{
		m_pRegisterMgr = new RegisterUserMgr( m_pServer, this );
		if( !m_pRegisterMgr->create() )
		{
			delete m_pRegisterMgr;
			m_pRegisterMgr = NULL;
			AfxMessageBox( "�޷����ӷ����������Ժ����ԡ�" );
			return;
		}
	}
	m_pRegisterMgr->cmdRegisterUser( m_sUsername.GetString(), m_sLastName.GetString(), 
		m_sFirstName.GetString(), m_sEmail.GetString(), m_sPassword.GetString(), m_pServer->getIP() );
}

HBRUSH CRegisterUserDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if( pWnd->GetDlgCtrlID() == IDC_LOGIN_AFTER_REGISTER )
	{
		pDC->SetTextColor( m_crText );
		pDC->SetBkMode( TRANSPARENT );
		hbr = m_brush;
	}
	return hbr;
}

LRESULT CRegisterUserDlg::OnRegisterUserResponse( WPARAM wParam, LPARAM lParam )
{
	string* pMsg = (string*)lParam;
	CString msg = (*pMsg).c_str();
	delete pMsg;
	if( wParam )
	{
		AfxMessageBox( "ע��ɹ���" );
		if( this->m_bLoginAfterRegister )
		{
			if( m_pServer->getStatus() != SERVER_LOGOUT )
			{
				((CMainFrame*)GetParent())->OnLogoutServer(m_pServer);
			}
			m_pServer->setUserName( m_sUsername.GetString() );
			m_pServer->setPassword( m_sPassword.GetString() );
			((CMainFrame*)GetParent())->OnLoginServer( m_pServer );
		}
		OnCancel();
	}
	else
	{
		AfxMessageBox( "ע��ʧ�ܣ�ԭ���ǣ�" + msg );
	}
	return 0;
}

BOOL CRegisterUserDlg::validateRegisterInfo()
{
	for( int i = 0; i < m_sUsername.GetLength(); i++ )
	{
		char ch = m_sUsername.GetAt(i);
		if( ch < 48 || ( ch > 57 && ch < 97 ) || ch > 122 )
		{
            AfxMessageBox( "�û���Ӧ����СдӢ����ĸ�Ͱ��������ֵ���ϣ����������롣" );
			return FALSE;
		}
	}
	if( m_sUsername.GetLength() < 4 || m_sUsername.GetLength() > 16 )
	{
		AfxMessageBox( "�û�������Ӧ����4-16���ַ�֮�䣬���������롣" );
		return FALSE;
	}
	if( m_sPassword.GetLength() < 6 || m_sPassword.GetLength() > 16 )
	{
		AfxMessageBox( "���볤��Ӧ����6-16���ַ�֮�䣬���������롣" );
		return FALSE;
	}
	else if( m_sLastName.GetLength() == 0 || m_sFirstName.GetLength() == 0 
		    || m_sEmail.GetLength() == 0 || m_sPassword.GetLength() == 0 )
	{
		AfxMessageBox( "����ѡ���Ϊ�գ����������롣" );
		return FALSE;
	}
	if( m_sPassword != m_sConfirmPassword )
	{
		AfxMessageBox( "ȷ�����������벻ƥ�䣬���������롣" );
		return FALSE;
	}
	return TRUE;
}

void CRegisterUserDlg::OnCancel()
{
	if( this->m_pRegisterMgr )
	{
		m_pRegisterMgr->destroy();
		delete m_pRegisterMgr;
	}
	CDialogEx::OnCancel();
}
