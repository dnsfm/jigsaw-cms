// testYuntaiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testYuntai.h"
#include "testYuntaiDlg.h"
#include ".\testyuntaidlg.h"

#include "YuntaiDlg.h"
#include "YuntaiMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestYuntaiDlg �Ի���



CtestYuntaiDlg::CtestYuntaiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestYuntaiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestYuntaiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestYuntaiDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CtestYuntaiDlg ��Ϣ�������

BOOL CtestYuntaiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestYuntaiDlg::OnPaint() 
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
HCURSOR CtestYuntaiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtestYuntaiDlg::OnBnClickedOk()
{
	YuntaiMgr* pMgr = new YuntaiMgr();
	if( !pMgr->init() )
	{
		AfxMessageBox( "Open serial port 1 failed!" );
		return;
	}

	CYuntaiDlg dlg;
	dlg.setYuntaiMgr( pMgr );
	dlg.DoModal();

	delete pMgr;
}
