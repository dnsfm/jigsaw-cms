// UI\MainFrm\AdvertizeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Flvcc.h"
#include "AdvertizeDlg.h"
#include ".\advertizedlg.h"
#include "AdBGDlg.h"

// CAdvertizeDlg �Ի���

IMPLEMENT_DYNCREATE(CAdvertizeDlg, CDHtmlDialog)

CAdvertizeDlg::CAdvertizeDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CAdvertizeDlg::IDD, CAdvertizeDlg::IDH, pParent)
{
	m_sUrl = "";
}

CAdvertizeDlg::~CAdvertizeDlg()
{
}

void CAdvertizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CAdvertizeDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CAdvertizeDlg, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CAdvertizeDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CAdvertizeDlg ��Ϣ�������

HRESULT CAdvertizeDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

HRESULT CAdvertizeDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

HRESULT STDMETHODCALLTYPE CAdvertizeDlg::ShowContextMenu(DWORD /*dwID*/, POINT *ppt, IUnknown* /*pcmdtReserved*/, IDispatch* /*pdispReserved*/)
{
	return S_OK;
}

void CAdvertizeDlg::OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl)
{
	CDHtmlDialog::OnDocumentComplete(pDisp, szUrl);
	if( m_sUrl != "" )
	{
		CAdBGDlg* pDlg = (CAdBGDlg*) GetParent();
		pDlg->showAdDlg();
	}
}
