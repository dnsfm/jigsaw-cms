// D:\Lyvc\src\Client\UI\MainFrm\AddContactStep2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "AddContactStep2.h"
#include ".\addcontactstep2.h"
#include "AddContactWizard.h"
#include "UserDefinedMessage.h"

// CAddContactStep2 �Ի���

IMPLEMENT_DYNAMIC(CAddContactStep2, CPropertyPage)
CAddContactStep2::CAddContactStep2()
	: CPropertyPage(CAddContactStep2::IDD)
{
	m_uid = 0;
}

CAddContactStep2::~CAddContactStep2()
{
	m_uid = 0;
}

void CAddContactStep2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddContactStep2, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAddContactStep2 ��Ϣ�������

LRESULT CAddContactStep2::OnWizardBack()
{
	//GetDlgItem(IDC_SEARCH_RESULT)->SetWindowText("���û��Ѿ��������ϵ���У�");
	this->m_sText = "���û��Ѿ��������ϵ���У�";
	this->InvalidateRect( NULL );
	//GetDlgItem(IDC_SEARCH_RESULT)->ShowWindow(TRUE);

	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
	GetDlgItem(IDC_NAME)->ShowWindow(FALSE);
	GetDlgItem(IDC_EMAIL)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATUS)->ShowWindow(FALSE);

	return CPropertyPage::OnWizardBack();
}

BOOL CAddContactStep2::OnSetActive()
{
	CAddContactWizard* pWizard = (CAddContactWizard*) GetParent();
	pWizard->setWindowRect( 1 );
	pWizard->m_btnBack.EnableWindow(TRUE);
	pWizard->m_btnNext.EnableWindow(FALSE);
	//GetDlgItem(IDC_SEARCH_RESULT)->SetWindowText(m_sText);
	return CPropertyPage::OnSetActive();
}

void CAddContactStep2::userNotFound(CString s)
{
	CAddContactWizard* pWizard = (CAddContactWizard*) GetParent();
	pWizard->m_btnBack.EnableWindow();
	pWizard->m_btnNext.EnableWindow(FALSE);

	//GetDlgItem(IDC_SEARCH_RESULT)->SetWindowText(s);
	this->m_sText = s;
	this->InvalidateRect( NULL );
	//GetDlgItem(IDC_SEARCH_RESULT)->ShowWindow(TRUE);

	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
	GetDlgItem(IDC_NAME)->ShowWindow(FALSE);
	GetDlgItem(IDC_EMAIL)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATUS)->ShowWindow(FALSE);
}

void CAddContactStep2::userInfo(string realName, string email, int status, __int64 uid)
{
	CAddContactWizard* pWizard = (CAddContactWizard*) GetParent();
	pWizard->m_btnBack.EnableWindow();
	pWizard->m_btnNext.EnableWindow();

	//GetDlgItem(IDC_SEARCH_RESULT)->SetWindowText("��ϵ����Ϣ��");
	this->m_sText = "��ϵ����Ϣ��";
	this->InvalidateRect( NULL ); 
    GetDlgItem(IDC_NAME)->SetWindowText(realName.c_str());
	GetDlgItem(IDC_EMAIL)->SetWindowText(email.c_str());
	if (status == CONTACT_ONLINE)
	{
		GetDlgItem(IDC_STATUS)->SetWindowText("����");
	}
	else
	{
		GetDlgItem(IDC_STATUS)->SetWindowText("�ѻ�");
	}

	GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(TRUE);
	GetDlgItem(IDC_NAME)->ShowWindow(TRUE);
	GetDlgItem(IDC_EMAIL)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATUS)->ShowWindow(TRUE);

	m_uid = uid;
}

LRESULT CAddContactStep2::OnWizardNext()
{
	CAddContactWizard* pWizard = (CAddContactWizard*) GetParent();
	if( !pWizard->m_btnNext.IsWindowEnabled() )
		return -1;
	if( pWizard->applyContact(m_uid) )
	{
		m_uid = 0;
		return CPropertyPage::OnWizardNext();
	}
	else
	{
		m_uid = 0;
		this->userNotFound("�˹��ܵ�ǰ�����á�");
		return -1;
	}
}

void CAddContactStep2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect( &rc );
	CAddContactWizard* pWizard = (CAddContactWizard*) GetParent();
	pWizard->drawHead( &dc, rc, m_sText );
	// ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}

HBRUSH CAddContactStep2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	if( pWnd->GetDlgCtrlID() == IDC_STATIC1
		|| pWnd->GetDlgCtrlID() == IDC_STATIC2
		|| pWnd->GetDlgCtrlID() == IDC_STATIC3
		|| pWnd->GetDlgCtrlID() == IDC_NAME
		|| pWnd->GetDlgCtrlID() == IDC_EMAIL
		|| pWnd->GetDlgCtrlID() == IDC_STATUS )
	{
		pDC->SetTextColor( RGB(0, 0, 0) );
		pDC->SetBkMode( TRANSPARENT );
		hbr = m_brush;
	}
	return hbr;
}

BOOL CAddContactStep2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
    m_brush.CreateSolidBrush( RGB(240, 245, 250) );
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
