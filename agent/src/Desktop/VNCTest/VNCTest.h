// VNCTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CVNCTestApp:
// �йش����ʵ�֣������ VNCTest.cpp
//

class CVNCTestApp : public CWinApp
{
public:
	CVNCTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVNCTestApp theApp;
