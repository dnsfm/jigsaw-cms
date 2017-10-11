#pragma once

#include "Audio\Mixer\Mixer.h"
#include "UI\pub\VolumeBar.h"

#include "ChatTab.h"
#include "AttenderListDlg.h"
#include "UI\pub\LinkButton.h"

#define VIEW_MODE_NORMAL	9999
#define VIEW_MODE_VGA		1
#define VIEW_MODE_DIALOG	2
#define VIEW_MODE_CIF		4
#define VIEW_MODE_QCIF		16

class CVideoBgDlg;
class CWhiteboardDlg;

// CRoomView ������ͼ
class CRoomView : public CDialog
{
	DECLARE_DYNCREATE(CRoomView)

public:
	CRoomView(CWnd* pParent = NULL);           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CRoomView();

	CAttenderListDlg* getAttenderListDlg();
	CChatTab* getChatTab();
	CVideoBgDlg* getVideoBgDlg();
	CWhiteboardDlg* getWhiteboardDlg();
	void showAttenderListDlg(BOOL bShow = TRUE);
	void setDualMoniterDisplay();
	void setSendMyVideoFlag( BOOL bSend );
	void setButtonStatus();

	// ��������
	void SetVolume(int v, int type);
	// ��Ƶ����
	void setViewMode( int nMode );
	int getViewMode();

	// �Ƿ�˫��ʾ����ʾ
	BOOL			m_bDualMoniterDisplay;
	// �Ƿ���ʾ������Ա
	BOOL			m_bShowUserList;
	enum { IDD = IDD_ROOM_VIEW };

private:
	CChatTab			m_ChatTab;
	CAttenderListDlg	m_AttenderListDlg;
	CImageList			m_ImageList;
	CLinkButton			m_btnShowAttenderList;
	CLinkButton			m_btnScrollUp;
	CLinkButton			m_btnScrollDown;
	CLinkButton			m_btnInvite;
	CLinkButton			m_btnSendFile;
	CLinkButton			m_btnSendVideo;
	CLinkButton			m_btnApplyDesktop;
	CLinkButton			m_btnWhiteboard;
	CLinkButton			m_btnSort;
	CBrush				m_brush;

	//�������ڿؼ�
	CSliderCtrl		m_sliMic;
	CSliderCtrl		m_sliPlay;
	CLinkButton		m_btnWaveOutMute;
	CLinkButton		m_btnMicMute;
	CVolumeBar		m_VolumeMic;
	CVolumeBar		m_VolumeWave;

	Mixer           m_mixerWaveIn;
	Mixer           m_mixerWaveOut;


	// ������˷粻֧�־�����������ǽ���˷���������Ϊ0��ģ�⾲��
	// m_dwMicV���ڱ��澲������֮ǰ��˷������
	bool			m_bMicMute;
	DWORD			m_dwMicV;

	// �Ƿ����Լ�����Ƶ�ź�
	BOOL			m_bSendMyVideo;

	// ��ǰ��Ƶ��ʾ����
	int				m_nViewMode;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnCancel() { };
	virtual void OnOK() { };

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedShowattenderlistBtn();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedScrolldownBtn();
	afx_msg void OnBnClickedScrollupBtn();

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LRESULT OnMixerChange(WPARAM wparam,LPARAM lparam);
	afx_msg void OnBnClickedMicMute();
	afx_msg void OnBnClickedWaveoutMute();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedInvite();
	afx_msg void OnBnClickedSendfile();
	afx_msg void OnBnClickedSendvideo();
	afx_msg void OnBnClickedApplydesktop();
	afx_msg void OnBnClickedWhiteboard();
	afx_msg void OnBnClickedSortBtn();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};


