#include "stdafx.h"
#include "resource.h"
#include "RichEditCtrlEx.h"
#include ".\richeditctrlex.h"
#include "chatdlg.h"
#include "ChatTab.h"
#include "RoomMainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_RICH_UNDO                    101
#define ID_RICH_CUT                     102
#define ID_RICH_COPY                    103
#define ID_RICH_PASTE                   104
#define ID_RICH_CLEAR                   105
#define ID_RICH_SELECTALL               106
#define ID_RICH_SETFONT                 107

int strcchr(const char *in, int chr)
{
	int ret = 0;
	while (*in++)
		if (*(in - 1) == chr) ret++;
	return ret;
}

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEx
IMPLEMENT_DYNAMIC(CRichEditCtrlEx, CRichEditCtrl);

CRichEditCtrlEx::CRichEditCtrlEx() : CRichEditCtrl()
{
	memset(&m_cfDefault, 0, sizeof(m_cfDefault));
	m_cfDefault.cbSize = sizeof(CHARFORMAT);
	m_cfDefault.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE | CFM_ITALIC | CFM_SIZE | CFM_STRIKEOUT | CFM_UNDERLINE;
	m_cfDefault.crTextColor = RGB(0, 0, 0);
	_tcscpy(m_cfDefault.szFaceName, _T("����"));
	m_cfDefault.bPitchAndFamily = FF_SWISS;
	m_cfDefault.yHeight = 210; 

	m_bEditable = FALSE;
}

CRichEditCtrlEx::~CRichEditCtrlEx()
{
}

void CRichEditCtrlEx::AppendText(CHARFORMAT *pfmt, const char *text)
{
	int len = GetTextLengthEx(GTL_NUMCHARS,1200);

	SetSel(len, len);
	ReplaceSel(text);

	int end = GetTextLengthEx(GTL_NUMCHARS,1200);
	SetSel(len, end-2);

	if (pfmt)
	{
		SetSelectionCharFormat(*pfmt);
	}

	SetSel(end, end);

	HideSelection(TRUE, FALSE);
	LineScroll(strcchr(text, '\n'));
}

BEGIN_MESSAGE_MAP(CRichEditCtrlEx, CRichEditCtrl)
	ON_COMMAND(ID_RICH_COPY, OnCopy)
	ON_COMMAND(ID_RICH_CUT, OnCut)
	ON_COMMAND(ID_RICH_PASTE, OnPaste)
	ON_COMMAND(ID_RICH_SELECTALL, OnSelectall)
	ON_COMMAND(ID_RICH_UNDO, OnUndo)
	ON_COMMAND(ID_RICH_CLEAR, OnClear)
	ON_COMMAND(ID_RICH_SETFONT, OnSelectfont)

	ON_WM_CHAR()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEx message handlers

void CRichEditCtrlEx::OnRButtonDown(UINT nFlags, CPoint point)
{
	//����Ϊ����
	SetFocus();
	//����һ������ʽ�˵�
	CMenu popmenu;
	popmenu.CreatePopupMenu();
	//��Ӳ˵���Ŀ
	if(m_bEditable)
	{
		popmenu.AppendMenu(0, ID_RICH_UNDO, "����");
		popmenu.AppendMenu(0, MF_SEPARATOR);
		popmenu.AppendMenu(0, ID_RICH_CUT, "����");
	}
	popmenu.AppendMenu(0, ID_RICH_COPY, "����");
	if(m_bEditable)
	{
		popmenu.AppendMenu(0, ID_RICH_PASTE, "ճ��");
		popmenu.AppendMenu(0, ID_RICH_CLEAR, "���");
		popmenu.AppendMenu(0, MF_SEPARATOR);
	}
	popmenu.AppendMenu(0, ID_RICH_SELECTALL, "ȫѡ");
	if(m_bEditable)
	{
		popmenu.AppendMenu(0, MF_SEPARATOR);
		popmenu.AppendMenu(0, ID_RICH_SETFONT, "ѡ������");
	}
	//��ʼ���˵���
	UINT nUndo=(CanUndo() ? 0 : MF_GRAYED );
	popmenu.EnableMenuItem(ID_RICH_UNDO, MF_BYCOMMAND|nUndo);

	UINT nSel=((GetSelectionType()!=SEL_EMPTY) ? 0 : MF_GRAYED) ;
	popmenu.EnableMenuItem(ID_RICH_CUT, MF_BYCOMMAND|nSel);
	popmenu.EnableMenuItem(ID_RICH_COPY, MF_BYCOMMAND|nSel);
	popmenu.EnableMenuItem(ID_RICH_CLEAR, MF_BYCOMMAND|nSel);
	
	UINT nPaste=(CanPaste() ? 0 : MF_GRAYED) ;
	popmenu.EnableMenuItem(ID_RICH_PASTE, MF_BYCOMMAND|nPaste);

	//��ʾ�˵�
	CPoint pt;
	GetCursorPos(&pt);
	popmenu.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	popmenu.DestroyMenu();

	//CRichEditCtrl::OnRButtonUp(nFlags, point);
}

///��������
void CRichEditCtrlEx::OnSelectfont() 
{
	CHARFORMAT cf;
	LOGFONT lf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	memset(&lf, 0, sizeof(LOGFONT));
	//�ж��Ƿ�ѡ��������
	BOOL m_bSelect = (GetSelectionType() != SEL_EMPTY) ? TRUE : FALSE;
	if (m_bSelect)
	{
		GetSelectionCharFormat(cf);
	}
	else
	{
		GetDefaultCharFormat(cf);
	}
	//�õ������������
	BOOL bIsBold = cf.dwEffects & CFE_BOLD;
	BOOL bIsItalic = cf.dwEffects & CFE_ITALIC;
	BOOL bIsUnderline = cf.dwEffects & CFE_UNDERLINE;
	BOOL bIsStrickout = cf.dwEffects & CFE_STRIKEOUT;
	//��������
	lf.lfCharSet = cf.bCharSet;
	lf.lfHeight = cf.yHeight/15;
	lf.lfPitchAndFamily = cf.bPitchAndFamily;
	lf.lfItalic = bIsItalic;
	lf.lfWeight = (bIsBold ? FW_BOLD : FW_NORMAL);
	lf.lfUnderline = bIsUnderline;
	lf.lfStrikeOut = bIsStrickout;
	sprintf(lf.lfFaceName, cf.szFaceName);
	
	CFontDialog dlg(&lf,CF_SCREENFONTS,0,GetParentOwner());
	dlg.m_cf.Flags = dlg.m_cf.Flags | CF_EFFECTS;	
	dlg.m_cf.rgbColors = cf.crTextColor;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCharFormat(cf);//�����ѡ���������
		if (m_bSelect) 
			SetSelectionCharFormat(cf);	//Ϊѡ���������趨��ѡ����
		else
			SetWordCharFormat(cf);	//Ϊ��Ҫ����������趨����
	
		SetDefaultCharFormat(cf);

		( ( CChatTab* )( m_pParent->GetParent() ) )->setCharFormat( cf );
	}
}

////����RTF��ʽ���ַ���
CString CRichEditCtrlEx::GetRTF()
{
	CString sRTF = "";
	EDITSTREAM es;
	es.dwError = 0;
	es.pfnCallback = RTFFormatToCString;		// Set the callback
	es.dwCookie = (DWORD) &sRTF;	// so sRTF receives the string
	StreamOut(SF_RTF, es);			// Call CRichEditCtrl::StreamOut to get the string.
	return sRTF;
}

void CRichEditCtrlEx::SetRTF(CString strRTF)
{
	int begin = GetTextLengthEx(GTL_NUMCHARS, 1200);

	EDITSTREAM es;
	es.dwError = 0;
	es.pfnCallback = CStringFormatToRTF;
	es.dwCookie = (DWORD) &strRTF;
	StreamIn(SF_RTF|SFF_SELECTION, es);	// Do it.

	int end = GetTextLengthEx(GTL_NUMCHARS, 1200);
	SetSel(begin, end);
	PARAFORMAT2 pf;
	pf.cbSize = sizeof(PARAFORMAT2);
	pf.dwMask = PFM_STARTINDENT;
	pf.dxStartIndent = 210;
	this->SetParaFormat( pf );
}

////StreamOut�Ļص�����
DWORD CALLBACK CRichEditCtrlEx::RTFFormatToCString(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CString *psEntry = (CString*) dwCookie;
	///�����ݴ����һ����ʱ������
	CString tmpEntry = "";
	tmpEntry = (CString) pbBuff;
	//��ʵ����Ч�����ݷ���
	*psEntry += tmpEntry.Left(cb);
	return 0;
}

////StreamIn�Ļص����� *pcb��ʵ��������ֽ���,cb��һ�����������ֽ���
DWORD CALLBACK CRichEditCtrlEx::CStringFormatToRTF(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	CString *pstr = (CString *) dwCookie;
	////��Ҫ��ŵ�RichEdit�����ݳ���С��һ���ܴ�ŵ���󳤶�,��
	////һ�������뵽RichEdit��
	if (pstr->GetLength() < cb)
	{
		*pcb = pstr->GetLength();
		memcpy(pbBuff, (LPCSTR) *pstr, *pcb);
		pstr->Empty();
	}
	////�����������̫��,��һ������cb�ֽڵ�RichEdit��
	///StreamIn�صݹ�����������
	else
	{
		*pcb = cb;
		memcpy(pbBuff, (LPCSTR) *pstr, *pcb);
		*pstr = pstr->Right(pstr->GetLength() - cb);
	}
	return 0;
}

void CRichEditCtrlEx::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 13)
	{
		int len = GetWindowTextLength();
		m_pParent->OnBnClickedSend();
	}
	else
	{
        CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
		m_pParent->sendWritingMessageFlag();
	}
}

void CRichEditCtrlEx::Init(BOOL bEditable, CChatDlg* pParent)
{
	m_bEditable = bEditable;
	m_pParent = pParent;
	if( this->m_bEditable )
	{
		CHARFORMAT cf = ((CChatTab*)(m_pParent->GetParent()))->getCharFormat();
		if( SetDefaultCharFormat( cf ) )
		{
			SetWordCharFormat( cf );
			m_cfDefault = cf;
		}
		else
		{
			SetDefaultCharFormat( m_cfDefault );
			SetWordCharFormat( m_cfDefault );
			((CChatTab*)(m_pParent->GetParent()))->setCharFormat( m_cfDefault );
		}
	}
	else
	{
		SetDefaultCharFormat( m_cfDefault );
		SetWordCharFormat( m_cfDefault );
	}
	//this->SetBackgroundColor(FALSE, RGB(217, 235, 255));
}

BOOL CRichEditCtrlEx::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_F4 )
		{
			::PostMessage( GetParentOwner()->GetSafeHwnd(), pMsg->message, pMsg->wParam, pMsg->lParam );
			return TRUE;
		}
	}

	return CRichEditCtrl::PreTranslateMessage(pMsg);
}

void CRichEditCtrlEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
	m_pParent->sendWritingMessageFlag();
}

void CRichEditCtrlEx::OnCut() 
{ 
	Cut();
	m_pParent->sendWritingMessageFlag();
}

void CRichEditCtrlEx::OnPaste() 
{ 
	Paste(); 
	m_pParent->sendWritingMessageFlag();
}

void CRichEditCtrlEx::OnUndo() 
{ 
	Undo(); 
	m_pParent->sendWritingMessageFlag();
}

void CRichEditCtrlEx::OnClear() 
{ 
	Clear(); 
	m_pParent->sendWritingMessageFlag();
}

void CRichEditCtrlEx::OnDropFiles(HDROP hDropInfo)
{
	char buff[MAX_PATH];
	UINT nCount = DragQueryFile( hDropInfo, 0xFFFFFFFF, buff, sizeof(buff) );
	for( int i = 0; i < nCount; i++ )
	{
		DragQueryFile( hDropInfo, i, buff, MAX_PATH );
		TRACE1( "drag filename: %s\n", buff );
		((CMeetingRoomFrame*)GetParentOwner())->dragFileToSend( buff, m_pParent->m_ChatWithId );
	}

	CRichEditCtrl::OnDropFiles(hDropInfo);
}
