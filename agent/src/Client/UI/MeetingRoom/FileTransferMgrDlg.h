#pragma once

// CFileTransferMgrDlg �Ի���
class CFileTransferDlg;
class CImageTabWnd;
class FileTransferMgr;

class CFileTransferMgrDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileTransferMgrDlg)

public:
	CFileTransferMgrDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileTransferMgrDlg();

// �Ի�������
	enum { IDD = IDD_FILETRANSFERMGRDLG };

	//��ȡ�ļ�����Ի���
	CFileTransferDlg* getSendFileDlg();
	CFileTransferDlg* getRecvFileDlg();
	void setFileTransferMgr(FileTransferMgr* pFileTransferMgr);
	void selectFileToSend(vector<__int64> ids);
	void applySendFile( CString fileName, vector<__int64> ids );
	void showRecvFileDlg();

private:
	CFileTransferDlg*	m_pSendFileDlg;//�ļ����ͶԻ���
	CFileTransferDlg*	m_pRecvFileDlg;
	CImageTabWnd*		m_pImageTab;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnClose();
};
