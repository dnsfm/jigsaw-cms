#include <string>
using namespace std;

#include "MatrixCLib/message/BaseMessage.h"
#include "MatrixCLib/MessageTarget.h"
using namespace LyvcMessage;

class ExceptionTarget :
    public MessageTarget
{
public:
    ExceptionTarget(MatrixC* pMatrixC);
    ~ExceptionTarget(void);

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

    void ExceptionHandler(BaseMessage* pMessage);
};
