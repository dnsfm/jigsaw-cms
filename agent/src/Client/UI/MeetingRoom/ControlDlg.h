#pragma once

#include "..\pub\DialogEx.h"

// CControlDlg �Ի���

class CControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CControlDlg)

public:
	CControlDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CControlDlg();

	void addConferenceUser( __int64 uid, string name, bool bVirtualUser = false );
	void deleteConferenceUser( __int64 uid );
	void setViewAsConsultingMode();

	// �Ի�������
	enum { IDD = IDD_CONTROL_DLG };

private:
	CListCtrl						m_ListUser;
	CListCtrl						m_ListVideo;
	CListCtrl						m_ListListen;
	int								m_nNumberOfVideo;
	CLinkButton						m_btnApply, m_btnStopAnswer, m_btnAnswer;

protected:
	// ���õ�ǰ����ʾ����Ƶ����
	void setVideoNumber( int nVideo );
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnOK() {};

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedSelectAllChk();
	afx_msg void OnBnClickedSelectAllChk2();
	afx_msg void OnBnClickedSelectAllChk3();
	afx_msg void OnDestroy();
	afx_msg void OnNMClickLookvideoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkLookvideoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickLookvideoList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedViewVga();
	afx_msg void OnBnClickedViewTwo();
	afx_msg void OnBnClickedViewCif();
	afx_msg void OnBnClickedViewQcif();
	afx_msg void OnBnClickedViewNormal();
	afx_msg void OnBnClickedBtnAnswer();
	afx_msg void OnBnClickedBtnStopanswer();
	afx_msg void OnBnClickedBtnApply();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
};
