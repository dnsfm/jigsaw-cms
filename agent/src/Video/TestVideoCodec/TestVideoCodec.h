// TestVideoCodec.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CTestVideoCodecApp:
// �йش����ʵ�֣������ TestVideoCodec.cpp
//

class CTestVideoCodecApp : public CWinApp
{
public:
	CTestVideoCodecApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestVideoCodecApp theApp;
