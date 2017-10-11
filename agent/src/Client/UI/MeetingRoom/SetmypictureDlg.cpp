// UI\MeetingRoom\SelectFaceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "SetmypictureDlg.h"
#include ".\setmypicturedlg.h"
#include "FileTransferDlg.h"

// CSetmypictureDlg �Ի���

IMPLEMENT_DYNAMIC(CSetmypictureDlg, CDialogEx)
CSetmypictureDlg::CSetmypictureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetmypictureDlg::IDD, pParent)
{
	m_bDisplayNow = false;
}

CSetmypictureDlg::~CSetmypictureDlg()
{
}

void CSetmypictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control( pDX, IDC_RESET, m_btnReset );
}


BEGIN_MESSAGE_MAP(CSetmypictureDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SELECTFILE_BTN, OnBnClickedSelectfileBtn)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_RESET, OnBnClickedReset)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSetmypictureDlg ��Ϣ�������

void CSetmypictureDlg::OnBnClickedSelectfileBtn()
{
	CFileDialog fdlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, "ͼƬ�ļ�(*.jpg;*.jpeg;*.bmp;*.gif)|*.jpg;*.jpeg;*.bmp;*.gif|", this);
	int nRet = fdlg.DoModal();
	if(nRet == IDOK)
	{
		ULONGLONG dwLength = CFileTransferDlg::getFileLength( fdlg.GetPathName() );
		if( dwLength > 45*1024 )
		{
			MessageBox( "��ѡ����ļ�������ѡ�񲻳�����45 KB����С���ļ���" );
			return;
		}
		m_videoWindow.m_img.Load( fdlg.GetPathName() );
		if( !m_videoWindow.m_img.IsValidImage() )
		{
			MessageBox( "��ѡ��Ĳ�����Ч��ͼ���ļ���������ѡ��" );
			return;
		}
		m_fileName = fdlg.GetPathName();
		GetDlgItem(IDC_PICTUREPATH)->SetWindowText( m_fileName );
		m_videoWindow.InvalidateRect( NULL );
	}
}

void CSetmypictureDlg::OnPaint()
{
	CDialogEx::OnPaint();
}

BOOL CSetmypictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rc;
	GetDlgItem( IDC_PREVIEW )->GetWindowRect( &rc );
	ScreenToClient( &rc );
	GetDlgItem( IDC_PREVIEW )->MoveWindow( rc.left, rc.top, 180, 154 );
	rc.left = rc.left + 2;
	rc.right = rc.left + 176;
	rc.top = rc.top + 7;
	rc.bottom = rc.top + 144;

	m_videoWindow.Create( "", WS_VISIBLE|WS_CLIPCHILDREN, CRect(), this, IDC_VIDEO_WINDOW );
	m_videoWindow.MoveWindow(rc);
	char buf[256];
	::GetPrivateProfileString( "DISPLAY_PICTURE", "file", "", buf, 256, m_sIniFileName );
	m_fileName = buf;
	m_videoWindow.m_img.Load( m_fileName );
	if( m_videoWindow.m_img.IsValidImage() )
	{
		GetDlgItem(IDC_PICTUREPATH)->SetWindowText( m_fileName );
	}
	else
	{
       	FCWin32::LoadImageBitmapRes( m_videoWindow.m_img, MAKEINTRESOURCE( IDB_VIDEOBG ) );
	}
	BOOL bShowPicture = ::GetPrivateProfileInt( "DISPLAY_PICTURE", "show", 0, m_sIniFileName );
	((CButton*)GetDlgItem(IDC_DISPLAYMYPICTURE))->SetCheck( bShowPicture );

	m_btnReset.setBitmaps( IDB_BUTTON, IDB_BUTTON, IDB_BUTTON, IDB_BUTTONDISABLE );
	GetClientRect( &rc );
	m_btnReset.MoveWindow( 8, rc.bottom - 32, 74, 22 );
	this->m_sDescription = "������ĸ��Ի�ͼƬ��Ŀǰ֧�ִ�С������45KB��BMP��JPG��GIF��ʽ\n��ͼ���ļ���������176*144��С��JPG��GIf�ļ���";

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSetmypictureDlg::OnBnClickedOk()
{
	::WritePrivateProfileString( "DISPLAY_PICTURE", "file", m_fileName, m_sIniFileName );
	m_bDisplayNow = ( ((CButton*)GetDlgItem(IDC_DISPLAYMYPICTURE))->GetCheck() == BST_CHECKED ) ? true : false;
	::WritePrivateProfileString( "DISPLAY_PICTURE", "show", m_bDisplayNow?"1":"0", m_sIniFileName );
	OnOK();
}

void CSetmypictureDlg::OnBnClickedReset()
{
	m_fileName = "";
	GetDlgItem(IDC_PICTUREPATH)->SetWindowText( "" );
	((CButton*)GetDlgItem(IDC_DISPLAYMYPICTURE))->SetCheck( BST_UNCHECKED );
	FCWin32::LoadImageBitmapRes( m_videoWindow.m_img, MAKEINTRESOURCE( IDB_VIDEOBG ) );
	m_videoWindow.InvalidateRect( NULL );
}

HBRUSH CSetmypictureDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if( pWnd->GetDlgCtrlID() == IDC_DISPLAYMYPICTURE
		|| pWnd->GetDlgCtrlID() == IDC_SELECTFILE_BTN
		|| pWnd->GetDlgCtrlID() == IDC_PICTUREPATH )
	{
		pDC->SetTextColor( m_crText );
		pDC->SetBkMode( TRANSPARENT );
		hbr = m_brush;
	}
	return hbr;
}
