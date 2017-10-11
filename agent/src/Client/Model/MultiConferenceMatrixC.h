#pragma once

/*
 *  ����ʹ�ø����װԭʼ��MatrixC����
 *  ������conferenceId���ڻ����ҵĸ�����
 *  Ϣ����ģ����з���.
 *
 *  ͨ����ģ�鷢�ͳ�ȥ��ÿһ����Ϣ����Я��
 *  conferenceId��Ϣ��
 *
 *  ��ģ���յ���Ϣ֮�������жϸ���Ϣ�Ƿ�
 *  ������Ļ���ID�����������ǣ�����������Ϣ
 */

#include "Message/MatrixC/MatrixCLib/MatrixC.h"
#include "Message/MatrixC/MatrixCLib/MessageHandlerItem.h"
using namespace LyvcMessage;

struct PendingMessageHandlerItem {

    int messageId;
    MessageTarget* pMessageTarget;
    PMSG_HANDLER pMessageHandler;

    PendingMessageHandlerItem() {
        messageId = 0;
        pMessageTarget = NULL;
        pMessageHandler = NULL;
    }
};

class MultiConferenceHandlerStub;

class MultiConferenceMatrixC : public LyvcMessage::MatrixC {

private:

    // Real matrix
    MatrixC* m_pMatrixC;

    // Conference id of this matrix
    __int64 m_conferenceId;

    // Stub handler
    MultiConferenceHandlerStub* m_pMultiConferenceHandlerStub;

    // �Ѿ���ʵ�ʵ�MatrixC��ע�����Ϣ��ŵ��б�
    list<int> m_RegisteredMessageList;

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

public:
    MultiConferenceMatrixC(MatrixC* pMatrixC, __int64 conferenceId);
    ~MultiConferenceMatrixC();

public:

    // ��Ϣϵͳ��ʼ��
    virtual BOOL Create(const char* hostIp, int port);

    // ��Ϣϵͳֹͣ
    virtual void Destroy();

    // ע��/ɾ��һ����Ϣ����ĺ���
	virtual void registerMessageHandler( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);
    virtual void removeMessageHandler( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);

    // ɾ��ĳ������ע���ȫ����Ϣ������
    virtual void removeObjectMessageHandler(MessageTarget* pMessageTarget);

    // ע�����⴦����
    // ����Ϣϵͳ�����쳣����Socket���ӶϿ�ʱ�����ô˺���
    // ʵ���Ͽͻ��˵��쳣������LServerͳһ���У�������ǲ�ʵ�֣�Ҳ���������ǵĿͻ�������Щ����
    virtual void registerExceptionHandler(MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);
    virtual void removeExceptionHandler();

    // ������Ϣ
    virtual void sendMessage(BaseMessage* pBaseMessage);

	// ��ȡ��ǰ���ڴ������ϢID
	virtual int getCurrentMessageId();

	// ��ȡ��ǰ���ӵķ�����IP��ַ
	virtual string getRemoteIP();

	friend MultiConferenceHandlerStub;

private:
    void registerMessageHandlerImpl( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);
    void removeMessageHandlerImpl( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler);
    void removeObjectMessageHandlerImpl(MessageTarget* pMessageTarget);
};

