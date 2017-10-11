#pragma once
#include "MatrixCLib/MessageTarget.h"
#include "MatrixCLib/message/BaseMessage.h"

using namespace LyvcMessage;

class HelloTarget :
    public MessageTarget
{
public:
    HelloTarget(MatrixC* pMatrixC);
    ~HelloTarget(void);

    // ���øú�����ɳ�ʼ������
	virtual bool create()
    {
        return true;
    }

    // ���øú������������
	virtual void destroy()
    {
        return;
    }

public:
    void LoginHandler(BaseMessage* pMessage);

};
