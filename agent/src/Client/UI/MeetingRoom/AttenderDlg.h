#pragma once

#include "..\pub\linkbutton.h"
#include "VideoShowWnd.h"

class ConferenceUser;
class CMeetingRoomFrame;

class CAttenderDlg : public CDialog
{
	DECLARE_DYNAMIC(CAttenderDlg)

public:
	CAttenderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAttenderDlg();

	//���ô��˵���ʾͼƬ
	void setUserPicture( string fileName );
	// ����/�ջ���ʾ
    void popUp();
	// ��û���Ƶ�źŵĴ��ھ��
	HWND getVideoHwnd();
	// ���òλ�����Ϣ
	void setConferenceUser(ConferenceUser* pConfUser);
	// ����û�id������
	__int64 getUserId();
    string getName();
	// �����Ƿ��������ı�־
	void setIsListenFlag( bool bIsListen );
	void resetIndex();

// �Ի�������
	enum { IDD = IDD_ATTENDER_DLG };

private:
	CMeetingRoomFrame* getRoomFrame();
	void DrawTitle(CBitmap *pBitmap, CDC *pDC, CRect rc);

public:
	bool			m_bIfHasYuntai;
	// �Ƿ���ʾ��Ƶ����
	bool			m_bShowVideoWindow;
	// �Ƿ����Լ�
	bool			m_bIsSelf;
	// �Ƿ񵯳�
	bool			m_bIsPopup;
	int				m_nIndex;
    
private:
	// ����/ֹͣ�������˵İ�ť
	CLinkButton			m_btnListen;
	// �λ�����Ϣ
	ConferenceUser*		m_pConfUser;
	// ��Ƶ����
	CVideoShowWnd		m_videoWindow;
	// ��ѹ������ʱ�򱾵ػ���Ƶ�Ĵ���
	CStatic				m_localVirtualVideoWindow;
	CBrush				m_brush;
	CWnd*				m_pParent;
	int					m_nLeftMargin;
	int					m_nTopMargin;
	bool				m_bIsFullScreen;
	int					m_nCurrentVideoSize;

private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnOK() {};
	virtual void OnCancel() {};

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	afx_msg void OnLookVideo();
	afx_msg void OnStopLook();
	afx_msg void OnChat();
	afx_msg void OnInviteDesktop();
	afx_msg void OnApplyDesktop();
	afx_msg void OnStopDesktopSend();
	afx_msg void OnStopDesktopReceive();
	afx_msg void OnApplyControl();
	afx_msg void OnStopControl();
	afx_msg void OnStopReceiveControl();
	afx_msg void OnReceiveAudio();
	afx_msg void OnStopAudio();
	afx_msg void OnSendFile();
	afx_msg void OnBnClickedListenBtn();
	afx_msg void OnTopmost();
	afx_msg void OnFullscreen();
	afx_msg void OnQcif();
	afx_msg void OnCif();
	afx_msg void OnVga();
	afx_msg void OnYuntaicontrol();
public:
	afx_msg void OnViewPopup();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnApplyContact();
	afx_msg void OnVideoqualityGood();
	afx_msg void OnVideoqualityNormal();
	afx_msg void OnVideoqualityBad();
	afx_msg void OnSetmypicture();
	afx_msg void OnKickuser();
	afx_msg void OnDeleteconfuser();
};
