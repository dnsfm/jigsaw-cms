// TestVideoCodecDlg.h : ͷ�ļ�
//

#pragma once

class CVideoCodecMgr;

#include "..\DrawDIB\DrawDIB.h"

// CTestVideoCodecDlg �Ի���
class CTestVideoCodecDlg : public CDialog
{
public:

    // ����
	CTestVideoCodecDlg(CWnd* pParent = NULL);

    // �Ի�������
	enum { IDD = IDD_TESTVIDEOCODEC_DIALOG };

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    // Video Call back
	static void Callback(void* pObject, LPVIDEOHDR lpVHdr);

private:

	CDrawDIB m_DrawDIBOriginal;
	HWND m_hVideoWndOriginal;

	CDrawDIB m_DrawDIBEncode;
	HWND m_hVideoWndEncode;
	CVideoCodecMgr	*m_pVideoEncoder;

    static const int ENCODED_VIDEO_BUFFER_LENGTH = 60000;
    unsigned char m_videoData[ENCODED_VIDEO_BUFFER_LENGTH];

    HWND AdjustVideoWindow(int ControlId);
};

