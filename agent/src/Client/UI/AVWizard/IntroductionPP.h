#pragma once


// CIntroductionPP �Ի���

class CIntroductionPP : public CPropertyPage
{
	DECLARE_DYNAMIC(CIntroductionPP)

public:
	CIntroductionPP();
	virtual ~CIntroductionPP();

    // �Ի�������
	enum { IDD = IDD_PROPPAGE_INTRO };

protected:
	CBrush m_brush;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

    virtual BOOL OnSetActive();
    virtual BOOL OnKillActive();
	afx_msg void OnPaint();
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
