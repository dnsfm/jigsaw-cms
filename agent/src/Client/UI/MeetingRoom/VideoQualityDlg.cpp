// UI\MeetingRoom\VideoQualityDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "VideoQualityDlg.h"
#include ".\videoqualitydlg.h"
#include "RoomMainFrm.h"

// CVideoQualityDlg �Ի���

IMPLEMENT_DYNAMIC(CVideoQualityDlg, CDialogEx)
CVideoQualityDlg::CVideoQualityDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVideoQualityDlg::IDD, pParent)
{
}

CVideoQualityDlg::~CVideoQualityDlg()
{
}

void CVideoQualityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text( pDX, IDC_FRAMERATE, m_nFrameRate );
	DDX_Text( pDX, IDC_KEYFRAME, m_nKeyFrame );
	DDX_Control( pDX, IDC_APPLY, m_btnApply );
}


BEGIN_MESSAGE_MAP(CVideoQualityDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_APPLY, OnBnClickedApply)
END_MESSAGE_MAP()


// CVideoQualityDlg ��Ϣ�������

BOOL CVideoQualityDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	( (CEdit*)GetDlgItem( IDC_FRAMERATE ) )->LimitText( 2 );
	( (CEdit*)GetDlgItem( IDC_KEYFRAME ) )->LimitText( 3 );

	char buf[33];
	::GetPrivateProfileString( "MEDIA_CONFIG", "video_quality", "", buf, sizeof(buf), GetApp()->getIniFilename() );
	GetDlgItem( IDC_FRAMERATE )->SetWindowText(buf);
	::GetPrivateProfileString( "MEDIA_CONFIG", "max_key_interval", "", buf, sizeof(buf), GetApp()->getIniFilename() );
	GetDlgItem( IDC_KEYFRAME )->SetWindowText(buf);

	m_btnApply.setBitmaps( IDB_BUTTON, IDB_BUTTON, IDB_BUTTON, IDB_BUTTONDISABLE );
	CRect rc;
	GetClientRect( &rc );
	m_btnOK.MoveWindow( rc.right - 240, rc.bottom - 32, 74, 22 );
	m_btnCancel.MoveWindow( rc.right - 160, rc.bottom - 32, 74, 22 );
	m_btnApply.MoveWindow( rc.right - 80, rc.bottom - 32, 74, 22 );

	this->m_sDescription = "��ʾ�� ����ϲ�������Ӧ��С֡�ʻ�ؼ�֡����Ի��\n�Ϻõ���Ƶ������ȡֵ��Χ֡��1-25���ؼ�֡���1-500��";
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CVideoQualityDlg::OnOK()
{
	if( apply() )
        CDialogEx::OnOK();
}

HBRUSH CVideoQualityDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if( pWnd->GetDlgCtrlID() == IDC_ERRORNUMBER )
	{
		pDC->SetTextColor( m_crText );
		pDC->SetBkMode( TRANSPARENT );
		hbr = m_brush;
	}
	return hbr;
}

void CVideoQualityDlg::OnBnClickedApply()
{
	apply();
}

BOOL CVideoQualityDlg::apply()
{
	UpdateData();
	if( m_nFrameRate < 1 || m_nFrameRate > 25 || m_nKeyFrame < 1 || m_nKeyFrame > 500 )
	{
		GetDlgItem( IDC_ERRORNUMBER )->SetWindowText( "���������ֵ��" );
		return FALSE;
	}
	else
	{
		GetDlgItem( IDC_ERRORNUMBER )->SetWindowText( "���óɹ���" );
		((CMeetingRoomFrame*)GetParent())->setFrameRateAndKeyFrameInterval( m_nFrameRate, m_nKeyFrame );
		CString s;
		GetDlgItem( IDC_FRAMERATE )->GetWindowText(s);
		::WritePrivateProfileString("MEDIA_CONFIG", "video_quality", s, GetApp()->getIniFilename());
		GetDlgItem( IDC_KEYFRAME )->GetWindowText(s);
		::WritePrivateProfileString("MEDIA_CONFIG", "max_key_interval", s, GetApp()->getIniFilename());
		return TRUE;
	}
}