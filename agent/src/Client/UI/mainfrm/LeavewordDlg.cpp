// LeavewordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "LeavewordDlg.h"
#include ".\leaveworddlg.h"


// CLeavewordDlg �Ի���

IMPLEMENT_DYNAMIC(CLeavewordDlg, CDialogEx)
CLeavewordDlg::CLeavewordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLeavewordDlg::IDD, pParent)
{
	m_strLeaveword = "";
	m_showRect = CRect(0, 0, 0, 0);
}

CLeavewordDlg::~CLeavewordDlg()
{
}

void CLeavewordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeavewordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CLeavewordDlg ��Ϣ�������

void CLeavewordDlg::OnBnClickedOk()
{
	this->GetDlgItem(IDC_LEAVEWORD)->GetWindowText(m_strLeaveword);
	if(m_strLeaveword.Trim().GetLength() == 0)
	{
		AfxMessageBox("�������ݲ���Ϊ�գ�");
	}
	else
	{
        OnOK();
	}
}

BOOL CLeavewordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if(m_showRect.top > 0)
		this->MoveWindow(m_showRect);
	this->m_sDescription = "����������ı����������������ݣ�����ȷ������ť���͡�";
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
