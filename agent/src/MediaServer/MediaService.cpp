#include "stdafx.h"
#include "mediaservice.h"
#include "ConferenceServerCommandTarget.h"
#include "common/common/Log/Log.h"
#include "message/MatrixC/MatrixCLib/MatrixC.h"
#include "common/common/PathHelper/PathHelper.h"

//ȫ�ֵķ���������ֻ�ܶ���һ��
MediaService theApp;

int MediaService::start()
{
    // ��ȡ����������ĵ�ַ��˿�
    const char* iniFileName = PathHelper::getIniFileFullName();
    char buffer[64];
    ::GetPrivateProfileString("LinkServer", "IPAddress", "127.0.0.1", buffer, sizeof(buffer), iniFileName);
    string linkServerIp(buffer);
    int linkServerPort = ::GetPrivateProfileInt("LinkServer", "Port", 4000, iniFileName);

    // ������Ϣ����
    LyvcMessage::MatrixC* pMatrixC = LyvcMessage::MatrixC::getInstance();
    if( !pMatrixC->Create(linkServerIp.c_str(), linkServerPort))
    {
        LyvcMessage::MatrixC::releaseInstance(pMatrixC);
        FVS_DEBUG("Unable to create MatrixC\n");
        return -1;
    }

    // ��ʼ��ý�������
    ConferenceServerCommandTarget* pCommandTarget = new ConferenceServerCommandTarget(pMatrixC);
    if( !pCommandTarget->create())
    {
        FVS_DEBUG("Unable to create Conference Service");
        return -1;
    }

    // ������Ϣѭ��
	m_hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    BOOL fQuit = FALSE;
	MSG msg;
    while(!fQuit)
    {
        DWORD dwResult = MsgWaitForMultipleObjectsEx(1, &m_hStopEvent, INFINITE, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
        switch(dwResult)
        {
        case WAIT_OBJECT_0:
            fQuit = TRUE;
            break;

        case WAIT_OBJECT_0 + 1:
            while( ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                if( msg.message == WM_QUIT)
                {
                    fQuit = TRUE;
                }
                else
                {
		            TranslateMessage(&msg);
		            DispatchMessage(&msg);
                }
            }
            break;

        }  // End of switch

    } // End of loop

    // ����ý�������
    pCommandTarget->destroy();
    delete pCommandTarget;

    // ������Ϣϵͳ
    pMatrixC->Destroy();
    LyvcMessage::MatrixC::releaseInstance(pMatrixC);
    pMatrixC = NULL;

	// �˳�
	FVS_DEBUG0("Media Server quit.\n");
    return 0;
}

int MediaService::stop()
{
	SetEvent(m_hStopEvent);
    return 0;
}

