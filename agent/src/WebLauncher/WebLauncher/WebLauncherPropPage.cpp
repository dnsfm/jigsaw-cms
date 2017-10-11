// WebLauncherPropPage.cpp : CWebLauncherPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "WebLauncher.h"
#include "WebLauncherPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CWebLauncherPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CWebLauncherPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CWebLauncherPropPage, "WEBLAUNCHER.WebLauncherPropPage.1",
	0x37aea53f, 0x2c6a, 0x4a06, 0xb5, 0x91, 0x0, 0x51, 0x76, 0x98, 0xb6, 0x47)



// CWebLauncherPropPage::CWebLauncherPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CWebLauncherPropPage ��ϵͳע�����

BOOL CWebLauncherPropPage::CWebLauncherPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_WEBLAUNCHER_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CWebLauncherPropPage::CWebLauncherPropPage - ���캯��

CWebLauncherPropPage::CWebLauncherPropPage() :
	COlePropertyPage(IDD, IDS_WEBLAUNCHER_PPG_CAPTION)
{
}



// CWebLauncherPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CWebLauncherPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CWebLauncherPropPage ��Ϣ�������
