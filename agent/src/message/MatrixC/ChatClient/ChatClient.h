// ChatClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������
#include "MatrixCLib/MatrixC.h"
using namespace LyvcMessage;


// CChatClientApp:
// �йش����ʵ�֣������ ChatClient.cpp
//

class CChatClientApp : public CWinApp
{
public:
	CChatClientApp();
    MatrixC* pMatrixC;

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChatClientApp theApp;
