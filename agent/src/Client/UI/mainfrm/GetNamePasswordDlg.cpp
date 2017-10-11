// UI\MainFrm\GetNamePasswordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "GetNamePasswordDlg.h"
#include ".\getnamepassworddlg.h"


// GetNamePasswordDlg �Ի���

IMPLEMENT_DYNAMIC(GetNamePasswordDlg, CDialogEx)
GetNamePasswordDlg::GetNamePasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GetNamePasswordDlg::IDD, pParent)
{
	m_sUsername = "";
	m_sPassword = "";
	m_bRememberme = FALSE;
}

GetNamePasswordDlg::~GetNamePasswordDlg()
{
}

void GetNamePasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text( pDX, IDC_USERNAME, m_sUsername );
	DDX_Text( pDX, IDC_PASSWORD, m_sPassword );
	DDX_Check( pDX, IDC_REMEMBERME, m_bRememberme );
}


BEGIN_MESSAGE_MAP(GetNamePasswordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// GetNamePasswordDlg ��Ϣ�������

BOOL GetNamePasswordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->m_sDescription = "��������Ŀ��������û��������룺";
	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void GetNamePasswordDlg::OnBnClickedOk()
{
	UpdateData();
	CString str = this->m_sUsername;
	str.Trim();
	if( str == "" )
	{
		AfxMessageBox( "�������û�����㡰ȡ������ťȡ�����롣" );
		return;
	}
	OnOK();
}

HBRUSH GetNamePasswordDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if( pWnd->GetDlgCtrlID() == IDC_REMEMBERME )
	{
		pDC->SetTextColor( m_crText );
		pDC->SetBkMode( TRANSPARENT );
		hbr = m_brush;
	}
	return hbr;
}
