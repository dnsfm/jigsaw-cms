#pragma once

#include "..\pub\DialogEx.h"

// CAddContactGroup �Ի���

class CAddContactGroup : public CDialogEx
{
	DECLARE_DYNAMIC(CAddContactGroup)

public:
	CAddContactGroup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddContactGroup();

// �Ի�������
	enum { IDD = IDD_ADDCONTACTGROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CString m_sTitle;
	CString m_sGroupName;

public:
	void setTitle(CString sTitle);
	void setDescription(CString sDescription);
	CString getGroupName();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
