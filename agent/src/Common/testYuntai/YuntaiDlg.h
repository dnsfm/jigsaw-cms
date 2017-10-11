#pragma once

class YuntaiMgr;
// CYuntaiDlg �Ի���

class CYuntaiDlg : public CDialog
{
	DECLARE_DYNAMIC(CYuntaiDlg)

public:
	CYuntaiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYuntaiDlg();

	void create(CWnd* pParent);
	void setYuntaiMgr(YuntaiMgr* pMgr);

private:
	YuntaiMgr* m_pYuntaiMgr;
	BOOL m_bUp;
	BOOL m_bDown;
	BOOL m_bLeft;
	BOOL m_bRight;
	BOOL m_bUpleft;
	BOOL m_bUpright;
	BOOL m_bDownleft;
	BOOL m_bDownright;
// �Ի�������
	enum { IDD = IDD_YUNTAI_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnLeft();
	afx_msg void OnBnClickedBtnRight();
	afx_msg void OnBnClickedBtnFocusin();
	afx_msg void OnBnClickedBtnFocusout();
	virtual BOOL OnInitDialog();
};
