// UI\MainFrm\MsnDelContactDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "MsnDelContactDlg.h"
#include ".\msndelcontactdlg.h"


// CMsnDelContactDlg �Ի���

IMPLEMENT_DYNAMIC(CMsnDelContactDlg, CDialogEx)
CMsnDelContactDlg::CMsnDelContactDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMsnDelContactDlg::IDD, pParent)
{
	this->m_sDescription = "ɾ����ϵ��";
	m_bHide = TRUE;
}

CMsnDelContactDlg::~CMsnDelContactDlg()
{
}

void CMsnDelContactDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMsnDelContactDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MSN_HIDECONTACT, OnBnClickedMsnHidecontact)
	ON_BN_CLICKED(IDC_MSN_DELCONTACT, OnBnClickedMsnDelcontact)
END_MESSAGE_MAP()


// CMsnDelContactDlg ��Ϣ�������

HBRUSH CMsnDelContactDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if( pWnd->GetDlgCtrlID() == IDC_MSN_HIDECONTACT || pWnd->GetDlgCtrlID() == IDC_MSN_DELCONTACT )
	{
		pDC->SetBkMode( TRANSPARENT );
		hbr = this->m_brush;
	}
	return hbr;
}

BOOL CMsnDelContactDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CButton*)GetDlgItem(IDC_MSN_HIDECONTACT))->SetCheck(TRUE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMsnDelContactDlg::OnBnClickedMsnHidecontact()
{
	this->m_bHide = TRUE;
}

void CMsnDelContactDlg::OnBnClickedMsnDelcontact()
{
	this->m_bHide = FALSE;
}
