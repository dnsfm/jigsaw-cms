#pragma once

#include "..\pub\linkbutton.h"
#include "..\pub\dialogex.h"

class YuntaiMgr;
// CYuntaiDlg �Ի���

class CYuntaiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYuntaiDlg)

public:
	CYuntaiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYuntaiDlg();

	void setYuntaiMgr(YuntaiMgr* pMgr);
	void addYuntaiHolder( __int64 uid, string name, int nCommPort );

private:
	void stopControl();
	int getCurrentCommPort();
	int getCurentControlAddress();

	YuntaiMgr* m_pYuntaiMgr;
	BOOL m_bMovingUp;
	BOOL m_bMovingDown;
	BOOL m_bMovingLeft;
	BOOL m_bMovingRight;
	BOOL m_bZoomIn;
	BOOL m_bZoomOut;

    int m_nCurrentCommPort;
	int m_nCurrentAddress;
	// �Ի�������
	enum { IDD = IDD_YUNTAI_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnLeft();
	afx_msg void OnBnClickedBtnRight();
	afx_msg void OnBnClickedBtnZoomin();
	afx_msg void OnBnClickedBtnZoomout();
	afx_msg void OnCbnSelchangeComboControllist();
	afx_msg void OnCbnSelchangeComboSerialport();
};
