#pragma once

#include "..\pub\DialogEx.h"

// CVideoQualityDlg �Ի���

class CVideoQualityDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoQualityDlg)

public:
	CVideoQualityDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVideoQualityDlg();

// �Ի�������
	enum { IDD = IDD_VIDEOQUALITY_DLG };

protected:
	BOOL apply();

	CLinkButton m_btnApply;
	int m_nFrameRate;
	int m_nKeyFrame;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedApply();
};
