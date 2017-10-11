#pragma once
#include "../pub/linkbutton.h"

// CStatusDlg �Ի���

class CStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatusDlg)

public:
	CStatusDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatusDlg();

// �Ի�������
	enum { IDD = IDD_STATUS_DLG };


public:
	// ��ʾ����
	CString			m_sDisplayName;

private:
	// �����ϵ�˰�ť
	CLinkButton		m_btnAddContact;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnOK() {};
	virtual void OnCancel() {};

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedAddcontactBtn();
	afx_msg void OnPaint();
};
