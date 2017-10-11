#pragma once

#include "../../message/MatrixC/MatrixCLib/MessageTarget.h"

class SMsgHandler;

class SMsgReader : public LyvcMessage::MessageTarget
{
public:
	//���캯��
	SMsgReader(LyvcMessage::MatrixC* pMatrixC, SMsgHandler* pMsgHandler);
	~SMsgReader(void);

	bool create() 
    {
        return true;
    }

	void destroy()
    {
        return;
    }

private:
	//��ȡ���̺�����¼�������handler����
	void readKeyEvent(LyvcMessage::BaseMessage* pMessage);
	void readMouseEvent(LyvcMessage::BaseMessage* pMessage);

private:
	//����ͻ��˴����¼��Ķ���ָ�룬ָ��������SMsgHandler��LyvcDesktopServer
	SMsgHandler* m_pMsgHandler;
};
