// TestVideoCodecXvid.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CTestVideoCodecXvidApp:
// �йش����ʵ�֣������ TestVideoCodecXvid.cpp
//

class CTestVideoCodecXvidApp : public CWinApp
{
public:
	CTestVideoCodecXvidApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestVideoCodecXvidApp theApp;
