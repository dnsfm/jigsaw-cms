#include "MatrixCLib/MessageTarget.h"

class Chat : public LyvcMessage::MessageTarget 
{
public:
   	Chat(LyvcMessage::MatrixC* pMatrixC);
    void broadcast(LyvcMessage::BaseMessage* pBaseMessage);

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

};
