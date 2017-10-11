// testMirandaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testMiranda.h"
#include "testMirandaDlg.h"
#include ".\testmirandadlg.h"

#include "..\include\m_commands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CtestMirandaDlg �Ի���


CtestMirandaDlg::CtestMirandaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestMirandaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestMirandaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestMirandaDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_LOGOUT_BTN, OnBnClickedLogoutBtn)
	ON_BN_CLICKED(IDC_EXIT_BTN, OnBnClickedExitBtn)
	ON_BN_CLICKED(IDC_SETACCOUNTANDPASSWORD_BTN, OnBnClickedSetaccountandpasswordBtn)
END_MESSAGE_MAP()


// CtestMirandaDlg ��Ϣ�������

BOOL CtestMirandaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestMirandaDlg::OnPaint() 
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
HCURSOR CtestMirandaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtestMirandaDlg::OnBnClickedOk()
{
	sendCmdToMiranda( MIRANDA_MSN_LOGIN );
	return;
    STARTUPINFO si = { sizeof(si) };            
    PROCESS_INFORMATION processInfo;
    //m_hEvent = CreateEvent( NULL, TRUE, FALSE, _T("miranda_event"));
	TCHAR szCommandline[] = _T( "D:\\miranda-im-v0.6.8-src\\miranda\\bin7\\Debug Unicode\\miranda32.exe miranda_event" );
    if( CreateProcess(NULL, szCommandline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &processInfo) ) 
    {
        CloseHandle( processInfo.hProcess );
        CloseHandle( processInfo.hThread );            
    }

}

void CtestMirandaDlg::OnBnClickedLogoutBtn()
{
	sendCmdToMiranda( MIRANDA_MSN_LOGOUT );
}

void CtestMirandaDlg::OnBnClickedExitBtn()
{
	sendCmdToMiranda( MIRANDA_EXIT );
}

void CtestMirandaDlg::OnBnClickedSetaccountandpasswordBtn()
{
	sendCmdToMiranda( MIRANDA_MSN_SET_ACCOUNT_AND_PASSWORD );
}

void CtestMirandaDlg::sendCmdToMiranda( DWORD dwCmdType )
{
	CWnd* pWnd = FindWindow(NULL, "Miranda IM");
	COPYDATASTRUCT MyCDS;
	MyCDS.dwData = dwCmdType;          // function identifier
	MyCDS.cbData = sizeof( SET_ACCOUNT_AND_PASSWORD );  // size of data
	SET_ACCOUNT_AND_PASSWORD cmd;
	switch ( dwCmdType )
	{
	case MIRANDA_EXIT:
	case MIRANDA_MSN_LOGIN:
	case MIRANDA_MSN_LOGOUT:
	case MIRANDA_QQ_LOGIN:
	case MIRANDA_QQ_LOGOUT:
		break;
	case MIRANDA_MSN_SET_ACCOUNT_AND_PASSWORD:
	case MIRANDA_QQ_SET_ACCOUNT_AND_PASSWORD:
		{
			lstrcpy( cmd.szAccount, "johnwang__1977@hotmail.com" );
			lstrcpy( cmd.szPassword, "123456" );
			break;
		}
	default:
		return;
	}

	MyCDS.lpData = &cmd;           // data structure
	BOOL b = ::SendMessage( pWnd->GetSafeHwnd(), WM_COPYDATA, (WPARAM) GetSafeHwnd(), (LPARAM) (LPVOID) &MyCDS );
	if( !b )
	{
		TRACE1( "send command %d to miranda failed!\n", dwCmdType );
	}
}
