// TestVideoCodecXvid.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "TestVideoCodecXvid.h"
#include "TestVideoCodecXvidDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestVideoCodecXvidApp

BEGIN_MESSAGE_MAP(CTestVideoCodecXvidApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestVideoCodecXvidApp ����

CTestVideoCodecXvidApp::CTestVideoCodecXvidApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CTestVideoCodecXvidApp ����

CTestVideoCodecXvidApp theApp;


// CTestVideoCodecXvidApp ��ʼ��

BOOL CTestVideoCodecXvidApp::InitInstance()
{
	CWinApp::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CTestVideoCodecXvidDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
