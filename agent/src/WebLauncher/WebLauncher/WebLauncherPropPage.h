#pragma once

// WebLauncherPropPage.h : CWebLauncherPropPage ����ҳ���������


// CWebLauncherPropPage : �й�ʵ�ֵ���Ϣ������� WebLauncherPropPage.cpp��

class CWebLauncherPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CWebLauncherPropPage)
	DECLARE_OLECREATE_EX(CWebLauncherPropPage)

// ���캯��
public:
	CWebLauncherPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_WEBLAUNCHER };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

