#ifndef MESSAGE_TARGET_H
#define MESSAGE_TARGET_H

namespace LyvcMessage {

class MessageTarget;
class BaseMessage;
class MatrixC;

typedef void (MessageTarget::*PMSG_HANDLER)(BaseMessage* pMessage);

class MessageTarget
{
protected:
    // Pointer to underlying message facility
    MatrixC* m_pMatrixC;

public:
    MessageTarget(MatrixC* pMatrixC)
    {
        m_pMatrixC = pMatrixC;
    }

public:

    // ���øú�����ɳ�ʼ������
	virtual bool create() = 0;

    // ���øú������������
	virtual void destroy() = 0;

}; // class

}; // namespace

#endif
