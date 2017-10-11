// D:\lyvc\src\Client\UI\mainfrm\AddContactGroup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "AddContactGroup.h"
#include ".\addcontactgroup.h"


// CAddContactGroup �Ի���

IMPLEMENT_DYNAMIC(CAddContactGroup, CDialogEx)
CAddContactGroup::CAddContactGroup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddContactGroup::IDD, pParent)
{
	m_sTitle = "";
	m_sGroupName = "";
}

CAddContactGroup::~CAddContactGroup()
{
}

void CAddContactGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddContactGroup, CDialogEx)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CAddContactGroup ��Ϣ�������

void CAddContactGroup::setTitle(CString sTitle)
{
	m_sTitle = sTitle;
}

void CAddContactGroup::setDescription(CString sDescription)
{
	m_sDescription = sDescription;
}

CString CAddContactGroup::getGroupName()
{
	return m_sGroupName;
}

void CAddContactGroup::OnBnClickedOk()
{
	GetDlgItemText(IDC_GROUPNAME, m_sGroupName);
	if( m_sGroupName.Trim() == "" )
		return;
		
	OnOK();
}

BOOL CAddContactGroup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->SetWindowText(m_sTitle);
	this->SetDlgItemText(IDC_STATIC, m_sDescription);

	((CEdit*)GetDlgItem(IDC_GROUPNAME))->LimitText(200);
	GetDlgItem(IDC_GROUPNAME)->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
