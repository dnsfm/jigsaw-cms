#pragma once
#include "..\pub\dirtreectrl.h"

// CDirDlg �Ի���

class CDirDlg : public CDialog
{
	DECLARE_DYNAMIC(CDirDlg)

public:
	CDirDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDirDlg();
	CString m_sPath;
// �Ի�������
	enum { IDD = IDD_DIR_DLG };

protected:

	CDirTreeCtrl m_TreeCtrl;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedDirTree(NMHDR *pNMHDR, LRESULT *pResult);
};
