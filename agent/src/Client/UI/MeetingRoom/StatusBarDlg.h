#pragma once

#include "..\MainFrm\AdvertizeDlg.h"

// CStatusBarDlg �Ի���

class CStatusBarDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatusBarDlg)

public:
	CStatusBarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatusBarDlg();
	void setStayTime( CString str );
	void setConfUserNum( CString str );

// �Ի�������
	enum { IDD = IDD_STATUSBAR_DLG };
	CString m_adUrl;

protected:
	CAdvertizeDlg m_dlgAd;
	CBrush m_brush;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK() { };
	virtual void OnCancel() { };
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
