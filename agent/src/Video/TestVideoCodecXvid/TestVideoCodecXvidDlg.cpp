// TestVideoCodecXvidDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestVideoCodecXvid.h"
#include "TestVideoCodecXvidDlg.h"
#include "../VideoConfig/VideoConfig.h"
#include "../VideoCapture/VideoCaptureMgr.h"
#include "../VideoCodecXvid/VideoCodec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestVideoCodecXvidDlg �Ի���


CTestVideoCodecXvidDlg::CTestVideoCodecXvidDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestVideoCodecXvidDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestVideoCodecXvidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestVideoCodecXvidDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


HWND CTestVideoCodecXvidDlg::AdjustVideoWindow(int ControlId)
{
	CRect rect;
	CWnd* pStatic = GetDlgItem(ControlId);
	pStatic->GetWindowRect(&rect);
	rect.bottom = rect.top + VideoConfig::getHeight();
	rect.right = rect.left + VideoConfig::getWidth();
	ScreenToClient(rect);
	pStatic->MoveWindow(&rect);
	return pStatic->GetSafeHwnd();
}

// CTestVideoCodecXvidDlg ��Ϣ�������

BOOL CTestVideoCodecXvidDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // Move video window
	this->m_hVideoWndOriginal = AdjustVideoWindow(IDC_VIDEO_ORIGINAL);
	this->m_hVideoWndEncode = AdjustVideoWindow(IDC_VIDEO_ENCODE);

    //
    // Init new codec
    //
    if(!VideoCodec::init())
    {
		TRACE("Failed to init 1.1.0 codec.\n");
        return -1;
    }

    if(!m_encoder.create(
                VideoConfig::DEFAULT_WIDTH,
                VideoConfig::DEFAULT_HEIGHT,
                VideoConfig::DEFAULT_FRAME_RATE,
				50000))
    {
		TRACE("Failed to create 1.1.0 encoder.\n");
        return -1;
    }

    if(!m_decoder.create(VideoConfig::DEFAULT_WIDTH, VideoConfig::DEFAULT_HEIGHT))
    {
		TRACE("Failed to create 1.1.0 decoder.\n");
        return -1;
    }
	TRACE("Initialize 1.1.0 codec successfully.");

	// Start capture
	if( !VideoCaptureMgr::create(CTestVideoCodecXvidDlg::Callback, (void*)this, NULL))
	{
		TRACE("Failed to create device.\n");
		return -1;
	}
	
	VideoCaptureMgr::startCapture();
	TRACE("Start capture successfully.\n");

	return TRUE;
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestVideoCodecXvidDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CTestVideoCodecXvidDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestVideoCodecXvidDlg::Callback(void* pObject, LPVIDEOHDR lpVHdr)
{
	CTestVideoCodecXvidDlg* _this = (CTestVideoCodecXvidDlg*)pObject;

    // Draw original
	_this->m_DrawDIBOriginal.DrawVideo(
            _this->m_hVideoWndOriginal,
            (char*)lpVHdr->lpData,
            const_cast<BITMAPINFOHEADER*>(&VideoConfig::DEFAULT_BITMAP_INFO_HEADER));

    // Encode the data
    int nLength = ENCODED_VIDEO_BUFFER_LENGTH;
    bool key = false;
    if(!_this->m_encoder.encode(
            lpVHdr->lpData,
            lpVHdr->dwBytesUsed,
            _this->m_videoData,
            &nLength,
            &key))
	{
		TRACE("Encode failed.\n");
		return;
	}
    if( key )
    {
        TRACE1("Key Frame length = %d\n", nLength);
    }
    else
    {
        TRACE1("Frame length = %d\n", nLength);
    }

    memset(lpVHdr->lpData, 0, lpVHdr->dwBytesUsed);

	// Decode the data
    _this->m_decoder.decode(
            _this->m_videoData,
            nLength,
            lpVHdr->lpData,
            lpVHdr->dwBytesUsed);

    // Draw encoded data
	_this->m_DrawDIBEncode.DrawVideo(
            _this->m_hVideoWndEncode,
            (char*)lpVHdr->lpData,
            const_cast<BITMAPINFOHEADER*>(&VideoConfig::DEFAULT_BITMAP_INFO_HEADER));
}


void CTestVideoCodecXvidDlg::OnOK()
{
	VideoCaptureMgr::stopCapture();
	VideoCaptureMgr::destroy();

    m_encoder.destroy();
    m_decoder.destroy();

	CDialog::OnOK();
}

