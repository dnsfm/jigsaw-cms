// testMirandaDlg.h : ͷ�ļ�
//

#pragma once


// CtestMirandaDlg �Ի���
class CtestMirandaDlg : public CDialog
{
// ����
public:
	CtestMirandaDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTMIRANDA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	void sendCmdToMiranda( DWORD dwCmdType );
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLogoutBtn();
	afx_msg void OnBnClickedExitBtn();
	afx_msg void OnBnClickedSetaccountandpasswordBtn();
};
