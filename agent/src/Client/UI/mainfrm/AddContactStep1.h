#pragma once


// CAddContactStep1 �Ի���

class CAddContactStep1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CAddContactStep1)

public:
	CAddContactStep1();
	virtual ~CAddContactStep1();

// �Ի�������
	enum { IDD = IDD_ADD_CONTACT_STEP1_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	afx_msg void OnPaint();
};
