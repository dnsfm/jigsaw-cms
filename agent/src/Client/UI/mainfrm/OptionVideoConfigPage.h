#pragma once

#include "..\pub\linkbutton.h"

// COptionVideoConfigPage �Ի���

class COptionVideoConfigPage : public CDialog
{
	DECLARE_DYNAMIC(COptionVideoConfigPage)

public:
	COptionVideoConfigPage(CWnd* pParent = NULL);
	virtual ~COptionVideoConfigPage();

	void setReadOnly( BOOL bReadOnly );
	BOOL apply();
	// �Ի�������
	enum { IDD = IDD_OPTION_VIDEOCONFIG_DLG };

private:
	void writeIni();
	BOOL checkValidateData();
	BOOL m_bReadOnly;
	CBrush m_brush;
	CLinkButton m_btn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnOK() { };
	virtual void OnCancel() { };
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedDefaultBtn();
	afx_msg void OnEnChangeFps();
	afx_msg void OnEnChangeKeyframe();
	afx_msg void OnCbnSelchangeComboVideosize();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
