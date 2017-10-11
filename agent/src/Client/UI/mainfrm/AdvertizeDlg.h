#pragma once

// CAdvertizeDlg �Ի���

class CAdvertizeDlg : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CAdvertizeDlg)

public:
	CAdvertizeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdvertizeDlg();
	CString m_sUrl;

// ��д
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	HRESULT STDMETHODCALLTYPE ShowContextMenu(DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved);

// �Ի�������
	enum { IDD = IDD_ADVERTIZE_DLG, IDH = IDR_HTML_ADVERTIZEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual void OnCancel() { };
	virtual void OnOK() { };

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
	virtual void OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl);
};
