// testYuntai.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CtestYuntaiApp:
// �йش����ʵ�֣������ testYuntai.cpp
//

class CtestYuntaiApp : public CWinApp
{
public:
	CtestYuntaiApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtestYuntaiApp theApp;
