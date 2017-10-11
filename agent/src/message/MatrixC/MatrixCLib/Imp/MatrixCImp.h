#ifndef MAXTRIX_C_IMP
#define MAXTRIX_C_IMP

#include "MatrixC.h"
#include "MessageHandlerItem.h"
#include "PendingMessageHandlerItem.h"

namespace LyvcMessage {

    class IOManager;
    class MatrixCImp : public MatrixC {

    private:

        // Exception Handler
        MessageHandlerItem m_exceptionHandler;

        // Store Message Handler
        typedef std::list<MessageHandlerItem> MessageHandlerList;
	    typedef std::map<int, MessageHandlerList*> MessageMap;
        MessageMap m_messageMap;

        // Indicate if we are in the message handler
        bool m_inMessageHandler;

        // Pending message handler
        typedef std::list<PendingMessageHandlerItem> PendingMessageHandlerList;
        PendingMessageHandlerList m_addList;
        PendingMessageHandlerList m_removeList;
        std::list<MessageTarget*> m_removeObjectList;

        // IO Manager
        IOManager* m_pIOManager;

		// Current dispatched message id
		int m_currentMessageId;

		// Remote server ip
		string m_remoteIP;

    public:
        MatrixCImp();
        ~MatrixCImp();


    public:

        // ��Ϣϵͳ��ʼ��
        virtual BOOL Create(const char* hostIp, int port);

        // ��Ϣϵͳֹͣ
        virtual void Destroy();

        // ע��һ����Ϣ����ĺ���
        virtual void registerMessageHandler( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);
        virtual void removeMessageHandler( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);

        // ɾ��ĳ������ע���ȫ����Ϣ������
        virtual void removeObjectMessageHandler(MessageTarget* pMessageTarget);

        // ע�����⴦����
        // ����Ϣϵͳ�����쳣����Socket���ӶϿ�ʱ�����ô˺���
        virtual void registerExceptionHandler(MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);
        virtual void removeExceptionHandler();

        // ������Ϣ
        virtual void sendMessage(BaseMessage* pBaseMessage);

 		virtual int getCurrentMessageId();
		virtual string getRemoteIP();

	private:
        // ע��һ����Ϣ����ĺ���
        void registerMessageHandlerImpl( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);
        void removeMessageHandlerImpl( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);

        // ɾ��ĳ������ע���ȫ����Ϣ������
        void removeObjectMessageHandlerImpl(MessageTarget* pMessageTarget);

    private:

        // IOManager ���ֵĻص�����
        static void ioManagerCallbackProc(void* pObject, const char* pBuffer, int nLength);
    };
};

#endif
