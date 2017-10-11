#pragma once

#include <queue>
using namespace std;

class CDrawObject;
class CWhiteboardDlg;
class CWhiteboardText;

// CWhiteboard �Ի���

class CWhiteboard : public CDialog
{
	DECLARE_DYNAMIC(CWhiteboard)

public:
	CWhiteboard(CWnd* pParent, UINT nID, UINT nBoardNum);   // ��׼���캯��
	virtual ~CWhiteboard();
	// �յ����ڰװ��ϻ��Ķ���
    void appendDraw( CDrawObject* pObject );
	void setTextFontAndColor(LOGFONT lf, COLORREF color);
	void hideTextWindow();
	void saveToFile( CString strFile );

private:
	CWhiteboardText*	m_pTrackText;
	BOOL			m_bShowText;
	UINT			m_nDrawTimerId;
	UINT			m_nBoardNum;
    CWhiteboardDlg* m_pParent;
	// �װ��С
	CSize			m_boardSize;
	CBrush			m_brush;
	// ���Ƶ�����
	HBITMAP			m_hBitmap;
	// �Ƿ���ʾ����
	bool			m_bShowgrid;
	// ��ǰ���Ƶ�ͼ��
	CDrawObject*	m_usrCurrentObject;
	// ��Ҫ���Ƶ�ͼ�ζ���
    queue<CDrawObject*> m_drawObjects;

    // ���浱ǰ���Ƶ�����
	void SaveCurrentDraw( CDrawObject* pDrawObject );
	// ��ʾ����
	void ShowGrid();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void OnOK() { };
	virtual void OnCancel() { };
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
