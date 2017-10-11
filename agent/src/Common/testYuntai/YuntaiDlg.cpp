// D:\lyvc\src\Client\UI\MeetingRoom\YuntaiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testYuntai.h"
#include "YuntaiDlg.h"
#include ".\yuntaidlg.h"

#include "YuntaiMgr.h"

// CYuntaiDlg �Ի���

IMPLEMENT_DYNAMIC(CYuntaiDlg, CDialog)
CYuntaiDlg::CYuntaiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYuntaiDlg::IDD, pParent)
{
	m_bUp = TRUE;
	m_bDown = TRUE;
	m_bLeft = TRUE;
	m_bRight = TRUE;
	m_bUpleft = TRUE;
	m_bUpright = TRUE;
	m_bDownleft = TRUE;
	m_bDownright = TRUE;
}

CYuntaiDlg::~CYuntaiDlg()
{
}

void CYuntaiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CYuntaiDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_UP, OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_LEFT, OnBnClickedBtnLeft)
	ON_BN_CLICKED(IDC_BTN_RIGHT, OnBnClickedBtnRight)
	ON_BN_CLICKED(IDC_BTN_FOCUSIN, OnBnClickedBtnFocusin)
	ON_BN_CLICKED(IDC_BTN_FOCUSOUT, OnBnClickedBtnFocusout)
END_MESSAGE_MAP()

void CYuntaiDlg::create(CWnd* pParent)
{
	this->Create(IDD_YUNTAI_DLG, pParent);
}

void CYuntaiDlg::setYuntaiMgr(YuntaiMgr* pMgr)
{
	this->m_pYuntaiMgr = pMgr;
}

// CYuntaiDlg ��Ϣ�������

BOOL CYuntaiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CYuntaiDlg::OnBnClickedBtnUp()
{

	if(m_bUp)
	{
		this->m_pYuntaiMgr->moveUp();
		GetDlgItem(IDC_BTN_UP)->SetWindowText("ֹͣ");
		GetDlgItem(IDC_BTN_DOWN)->SetWindowText("����");
		GetDlgItem(IDC_BTN_LEFT)->SetWindowText("����");
		GetDlgItem(IDC_BTN_RIGHT)->SetWindowText("����");
		m_bDown = TRUE;
		m_bLeft = TRUE;
		m_bRight = TRUE;
	}
	else
	{
		this->m_pYuntaiMgr->stopMoveUp();
		GetDlgItem(IDC_BTN_UP)->SetWindowText("����");
	}
	m_bUp = !m_bUp;
}

void CYuntaiDlg::OnBnClickedBtnDown()
{
	if(m_bDown)
	{
		this->m_pYuntaiMgr->moveDown();
		GetDlgItem(IDC_BTN_DOWN)->SetWindowText("ֹͣ");
		GetDlgItem(IDC_BTN_UP)->SetWindowText("����");
		GetDlgItem(IDC_BTN_LEFT)->SetWindowText("����");
		GetDlgItem(IDC_BTN_RIGHT)->SetWindowText("����");
		m_bUp = TRUE;
		m_bLeft = TRUE;
		m_bRight = TRUE;
	}
	else
	{
		this->m_pYuntaiMgr->stopMoveDown();
		GetDlgItem(IDC_BTN_DOWN)->SetWindowText("����");
	}
	m_bDown = !m_bDown;
}

void CYuntaiDlg::OnBnClickedBtnLeft()
{
		if(m_bLeft)
		{
			this->m_pYuntaiMgr->moveLeft();
			GetDlgItem(IDC_BTN_LEFT)->SetWindowText("ֹͣ");
			GetDlgItem(IDC_BTN_UP)->SetWindowText("����");
			GetDlgItem(IDC_BTN_DOWN)->SetWindowText("����");
			GetDlgItem(IDC_BTN_RIGHT)->SetWindowText("����");
			m_bUp = TRUE;
			m_bDown = TRUE;
			m_bRight = TRUE;
		}
		else
		{
			this->m_pYuntaiMgr->stopMoveLeft();
			GetDlgItem(IDC_BTN_LEFT)->SetWindowText("����");
		}
		m_bLeft = !m_bLeft;
}

void CYuntaiDlg::OnBnClickedBtnRight()
{
		if(m_bRight)
		{
			this->m_pYuntaiMgr->moveRight();
			GetDlgItem(IDC_BTN_RIGHT)->SetWindowText("ֹͣ");
			GetDlgItem(IDC_BTN_UP)->SetWindowText("����");
			GetDlgItem(IDC_BTN_DOWN)->SetWindowText("����");
			GetDlgItem(IDC_BTN_LEFT)->SetWindowText("����");
			m_bUp = TRUE;
			m_bDown = TRUE;
			m_bLeft = TRUE;
		}
		else
		{
			this->m_pYuntaiMgr->stopMoveRight();
			GetDlgItem(IDC_BTN_RIGHT)->SetWindowText("����");
		}
		m_bRight = !m_bRight;
}

void CYuntaiDlg::OnBnClickedBtnFocusin()
{
	this->m_pYuntaiMgr->focusIn();
}

void CYuntaiDlg::OnBnClickedBtnFocusout()
{
	this->m_pYuntaiMgr->focusOut();
}

