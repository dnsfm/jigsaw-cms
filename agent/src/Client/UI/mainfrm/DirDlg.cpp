// ui\DirDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FLVCC.h"
#include "DirDlg.h"

// CDirDlg �Ի���

IMPLEMENT_DYNAMIC(CDirDlg, CDialog)
CDirDlg::CDirDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDirDlg::IDD, pParent)
{
}

CDirDlg::~CDirDlg()
{
}

void CDirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIR_TREE, m_TreeCtrl);
}


BEGIN_MESSAGE_MAP(CDirDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_DIR_TREE, OnTvnSelchangedDirTree)
END_MESSAGE_MAP()


// CDirDlg ��Ϣ�������

BOOL CDirDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_TreeCtrl.DisplayTree(NULL);
	m_TreeCtrl.SetSelPath(m_sPath);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDirDlg::OnTvnSelchangedDirTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	m_sPath = m_TreeCtrl.GetFullPath(pNMTreeView->itemNew.hItem);

	*pResult = 0;
}
