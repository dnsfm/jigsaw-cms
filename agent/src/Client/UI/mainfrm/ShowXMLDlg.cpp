// D:\Lyvc\src\Client\UI\mainfrm\ShowXMLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "ShowXMLDlg.h"


// CShowXMLDlg �Ի���

IMPLEMENT_DYNCREATE(CShowXMLDlg, CDHtmlDialog)

CShowXMLDlg::CShowXMLDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CShowXMLDlg::IDD, CShowXMLDlg::IDH, pParent)
{
}

CShowXMLDlg::CShowXMLDlg(CString sURL, CString sTitle, CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CShowXMLDlg::IDD, CShowXMLDlg::IDH, pParent)
{
	m_cx = 700;
	m_cy = 500;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sURL = sURL;
	m_sTitle = sTitle;
}

CShowXMLDlg::~CShowXMLDlg()
{
}

void CShowXMLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CShowXMLDlg::OnInitDialog()
{
	SetHostFlags(DOCHOSTUIFLAG_NO3DBORDER);
	CDHtmlDialog::OnInitDialog();
	SetWindowText(m_sTitle);
	Navigate( m_sURL, navNoReadFromCache|navNoWriteToCache );
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	this->MoveWindow( 0, 0, m_cx, m_cy );
	this->CenterWindow();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CShowXMLDlg, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CShowXMLDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CShowXMLDlg ��Ϣ�������

HRESULT CShowXMLDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

HRESULT CShowXMLDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

HRESULT STDMETHODCALLTYPE CShowXMLDlg::ShowContextMenu(DWORD /*dwID*/, POINT *ppt, IUnknown* /*pcmdtReserved*/, IDispatch* /*pdispReserved*/)
{
	return S_OK;
}
