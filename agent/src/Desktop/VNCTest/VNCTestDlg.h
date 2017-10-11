// VNCTestDlg.h : ͷ�ļ�
//

#pragma once

class DesktopServer;
class DesktopClient;
using namespace std;

namespace LyvcMessage
{
    class MatrixC;
};

// CVNCTestDlg �Ի���
class CVNCTestDlg : public CDialog
{
// ����
public:
	CVNCTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VNCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedCapture();

	HANDLE DDBToDIB(CBitmap &bitmap, DWORD dwCompression, CPalette *pPal);
	BOOL WriteDIB(LPTSTR szFile, HANDLE hDIB);
	void SaveRectToBmp(CRect rect);
	void OnTest(); 


private:
	//���湲������
	DesktopServer* m_desktopServer;
	//���湲��ͻ���
	DesktopClient* m_desktopClient;
	//��Ϣ�����շ�ϵͳ
    LyvcMessage::MatrixC* m_pMatrixC;

public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	//��������ͻ���
	afx_msg void OnBnClickedStartclient();
	//ֹͣ����ͻ���
	afx_msg void OnBnClickedStopclient();
	//������������
	afx_msg void OnBnClickedStartserver();
	//ֹͣ��������
	afx_msg void OnBnClickedStopserver();

	//��ʼ����Ϣ�����շ�
	BOOL initMsgMatrix(CString IP, int port);
	void releaseMsgMatrix();

	afx_msg void OnBnClickedControl();
	afx_msg void OnBnClickedUncontrol();
	afx_msg void OnBnClickedRestart();
};
