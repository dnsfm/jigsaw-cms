// testMiranda.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CtestMirandaApp:
// �йش����ʵ�֣������ testMiranda.cpp
//

class CtestMirandaApp : public CWinApp
{
public:
	CtestMirandaApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtestMirandaApp theApp;
