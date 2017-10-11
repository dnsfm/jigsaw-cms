// UI\MainFrm\MsnAccountDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "MsnAccountDlg.h"
#include ".\msnaccountdlg.h"


// CMsnAccountDlg �Ի���

IMPLEMENT_DYNAMIC(CMsnAccountDlg, CDialogEx)
CMsnAccountDlg::CMsnAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMsnAccountDlg::IDD, pParent)
{
	this->m_sDescription = "���õ��ʺź������ڱ��ε�¼ע�����´ε�¼ʱ��Ч��"; 
	m_bReadOnly = FALSE;
}

CMsnAccountDlg::~CMsnAccountDlg()
{
}

void CMsnAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text( pDX, IDC_MSNACCOUNT, m_sAccount );
	DDX_Text( pDX, IDC_MSNPASSWORD, m_sPassword );
}


BEGIN_MESSAGE_MAP(CMsnAccountDlg, CDialogEx)
END_MESSAGE_MAP()


// CMsnAccountDlg ��Ϣ�������

BOOL CMsnAccountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData( FALSE );
	((CEdit*)GetDlgItem(IDC_MSNACCOUNT))->SetReadOnly( m_bReadOnly );
	((CEdit*)GetDlgItem(IDC_MSNPASSWORD))->SetReadOnly( m_bReadOnly );

	((CEdit*)GetDlgItem(IDC_MSNACCOUNT))->LimitText( 126 );
	((CEdit*)GetDlgItem(IDC_MSNPASSWORD))->LimitText( 126 );
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMsnAccountDlg::OnOK()
{
	UpdateData();
	CDialogEx::OnOK();
}
