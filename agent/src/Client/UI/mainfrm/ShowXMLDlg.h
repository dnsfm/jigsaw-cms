#pragma once


// CShowXMLDlg �Ի���

class CShowXMLDlg : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CShowXMLDlg)

public:
	CShowXMLDlg( CWnd* pParent = NULL );   // ��׼���캯��
	CShowXMLDlg( CString sURL, CString sTitle, CWnd* pParent = NULL );
	virtual ~CShowXMLDlg();
// ��д
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	HRESULT STDMETHODCALLTYPE ShowContextMenu(DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved);

// �Ի�������
	enum { IDD = IDD_SHOWXML_DLG, IDH = IDR_HTML_SHOWXMLDLG };

	void setWindowSize( int cx, int cy ) { m_cx = cx; m_cy = cy; };
protected:
	int m_cx, m_cy;

	HICON m_hIcon;
	CString m_sURL;
	CString m_sTitle;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
