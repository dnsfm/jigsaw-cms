#pragma once

#include "..\pub\DialogEx.h"

// CSortAttendersDlg �Ի���
class CAttenderListDlg;

class CSortAttendersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSortAttendersDlg)

public:
	CSortAttendersDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSortAttendersDlg();

	void deleteUser(string name, __int64 uid);

	// �Ի�������
	enum { IDD = IDD_SORTATTENDERS_DLG };
	CAttenderListDlg* m_pAttenderListDlg;

private:
	void fillListBox(bool bSortByName = false);
	vector<string> m_attenderNames;
	vector<__int64> m_attenderIds;

	CLinkButton m_btnDown, m_btnUp, m_btnSortByName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedUpBtn();
	afx_msg void OnBnClickedDownBtn();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedSortbynameBtn();
};
