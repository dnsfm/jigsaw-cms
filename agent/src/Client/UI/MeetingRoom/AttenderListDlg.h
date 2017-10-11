#pragma once

class CAttenderDlg;
class ConferenceUser;
class CSortAttendersDlg;
// CAttenderListDlg �Ի���

#define VIDEO_HEIGHT				146
#define VIDEO_WINDOW_TITLE_HEIGHT	22
#define VIDEO_WINDOW_HEIGHT			168
#define VIDEO_WINDOW_WIDTH			180

class CAttenderListDlg : public CDialog
{
	DECLARE_DYNAMIC(CAttenderListDlg)

public:
	CAttenderListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAttenderListDlg();

	enum { IDD = IDD_ATTENDERLIST_DLG };

	// �ж��Ƿ���������̨
	bool hasYuntai();
	//���ô�������̨
	void setYuntaiHolder( __int64 uid );
	// ��Ӳλ���Ա
	void addConferenceUser(ConferenceUser* pConfUser, bool bSelf = false);
	// �Ƴ��λ���Ա
	void deleteConferenceUser(__int64 uid);
	// ��õ�ǰ�λ�����
	int getConfUserCount();
	// ��ʾ������ĳ����Ƶ����
	void showVideoWindow(__int64 uid, bool bShow = true);
	// ����id��ȡ��Ƶ����
	HWND getVideoWindowById(__int64 uid);
	// ��ȡ������Ƶ����
	HWND getLocalVidwoWindow();
	// ���¹���
	void scrollDown();
	void scrollUp();
	// ��ֻ�������λ��˵������,�������һ���˵�id
	__int64 getAnotherUserId();
	// ���������λ��˵�λ��
	void swapConfUser(__int64 prevId, __int64 nextId);
	// �������Լ�
	void getAttendersIdAndNameForSort( vector<string>* names, vector<__int64>* ids );
	void setIsListenFlag( bool bIsListen, __int64 uid );
	void sortAttenders();
	void sortAttenders( vector<__int64>& ids );
	// ���ڵ�����ʾ
	void popupAttenderDlg( __int64 uid );
	void popUp( CAttenderDlg* pDlg, bool bPopup = true );
	int getUnpopupAttenderDlg( CAttenderDlg** ppDlg, int nCount );
	void popbackAllVideoDlg();

	// ����id���ĳ�˵���ʾ����
	CAttenderDlg* getAttenderDlgById(__int64 uid);

private:
	// �Ƿ�������¹���
	BOOL canScrollDown();
	BOOL canScrollUp();
	// ���²��ִ���
	void reLayout(bool bFromTopToBottom, POSITION posStartAt, POSITION posEndBefore, int nOffset);
	// �õ���ǰ�б��һ����ʾ�Ļ�����Ա�������б��е�λ��
	POSITION getFirstViewPosition();
	int getBottom();
	int getTop();

private:
	// �λ���Ա�����б�
	CPtrList		m_AttenderDlgs;
	// �Լ��Ĵ���
	CAttenderDlg*	m_pSelfDlg;
	// ����
	CSortAttendersDlg*	m_pSortDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnCancel() {};
	virtual void OnOK() {};

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk() {};
	afx_msg void OnBnClickedCancel() {};
};
