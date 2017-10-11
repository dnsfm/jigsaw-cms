#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"       // main symbols

class CooperationManager;

class CFLVCCApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// ��ȡ�����ļ����ļ���
	char* getIniFilename();

	// ��ȡ�ͻ�������ģ�͵Ķ���ָ��
	CooperationManager* getCooperationManager();
	
	afx_msg  void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	// �����ļ����ļ���
	char m_IniFileName[MAX_PATH];

	// �ͻ��˵�����ģ��
    CooperationManager*  m_cooperationManager;

};

inline CFLVCCApp *GetApp()
{
	return (CFLVCCApp *)AfxGetApp();
}
