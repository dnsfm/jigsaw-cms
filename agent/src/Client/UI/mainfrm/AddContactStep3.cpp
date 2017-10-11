// ui\mainfrm\AddContactStep3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "AddContactStep3.h"
#include ".\addcontactstep3.h"
#include "AddContactWizard.h"


// CAddContactStep3 �Ի���

IMPLEMENT_DYNAMIC(CAddContactStep3, CPropertyPage)
CAddContactStep3::CAddContactStep3()
	: CPropertyPage(CAddContactStep3::IDD)
{
}

CAddContactStep3::~CAddContactStep3()
{
}

void CAddContactStep3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddContactStep3, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAddContactStep3 ��Ϣ�������

BOOL CAddContactStep3::OnSetActive()
{
	CAddContactWizard* pWizard = (CAddContactWizard*) GetParent();
	pWizard->setWindowRect( 2 );
	pWizard->m_btnBack.EnableWindow(FALSE);
	pWizard->m_btnNext.ShowWindow(FALSE);
	pWizard->m_btnFinish.ShowWindow(TRUE);
	pWizard->m_btnFinish.EnableWindow();
	pWizard->m_btnCancel.SetWindowText("�����һ��");

	return CPropertyPage::OnSetActive();
}


void CAddContactStep3::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect( &rc );
	CAddContactWizard* pWizard = (CAddContactWizard*) GetParent();
	pWizard->drawHead( &dc, rc, "" );
	// ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}

BOOL CAddContactStep3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_brush.CreateSolidBrush( RGB(240, 245, 250) );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CAddContactStep3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	if( pWnd->GetDlgCtrlID() == IDC_STATIC )
	{
		pDC->SetTextColor( RGB(0, 0, 0) );
		pDC->SetBkMode( TRANSPARENT );
		hbr = m_brush;
	}
	return hbr;
}
