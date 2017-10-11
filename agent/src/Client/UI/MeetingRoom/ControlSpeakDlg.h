#pragma once


// CControlSpeakDlg �Ի���

class CControlSpeakDlg : public CDialog
{
	DECLARE_DYNAMIC(CControlSpeakDlg)

public:
	CControlSpeakDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CControlSpeakDlg();

	// �����Ա
	void addConferenceUser( __int64 uid, string name );

	// ɾ����Ա
	void deleteConferenceUser( __int64 uid );

	// �������뷢�Եı�־
	void setApplySpeak( __int64 uid );

	// �����Ƿ����ڷ��Եı�־
	void setSpeaker( __int64 uid, BOOL bFlag = TRUE );

	// �Ի�������
	enum { IDD = IDD_CONTROLSPEAK_DLG };

private:
    void setListItemImage( int nIndex, int nImage );

private:
	CImageList	m_ImageList;
	CListCtrl m_ListCtrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnDestroy();
	afx_msg void OnBnClickedAppointspeakerBtn();
	afx_msg void OnBnClickedStopspeakerBtn();
};
