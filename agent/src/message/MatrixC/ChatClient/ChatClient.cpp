// ChatClient.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "Chat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatClientApp

BEGIN_MESSAGE_MAP(CChatClientApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChatClientApp ����

CChatClientApp::CChatClientApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CChatClientApp ����

CChatClientApp theApp;


// CChatClientApp ��ʼ��

BOOL CChatClientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

    char globalBuffer[MAX_PATH];
    ::memset(globalBuffer, 0, MAX_PATH);
	::GetModuleFileName(NULL, globalBuffer, MAX_PATH);
    size_t length = strlen(globalBuffer);
    globalBuffer[length - 3 ] = 'i';
    globalBuffer[length - 2 ] = 'n';
    globalBuffer[length - 1 ] = 'i';

    char buffer[1024];
    ::GetPrivateProfileString("Server", "IP", "127.0.0.1", buffer, 1024, globalBuffer);
    int nPort = ::GetPrivateProfileInt("Server", "Port", 1000, globalBuffer);

    pMatrixC = MatrixC::getInstance();
    if(!pMatrixC->Create(buffer, nPort))
    {
        char buffer2[1024];
        _snprintf(buffer2, 1024, "Can't not connect to %s:%d", buffer, nPort);
        AfxMessageBox(buffer2);
        return FALSE;
    }

    CChatClientDlg dlg;
	m_pMainWnd = &dlg;

    Chat chat(pMatrixC);

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
