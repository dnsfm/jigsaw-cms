#ifndef MATRIX_C_H
#define MATRIX_C_H

#include "MessageTarget.h"

namespace LyvcMessage {

    class MatrixC {

    public:

        // ��ȡʵ��
        static MatrixC* getInstance();

        // �ͷ�ʵ��
        static void releaseInstance(MatrixC* pMatrixC);

        // Э��ͷ��
        static const char* LYVC_MESSAGE_HEADER;

    public:

        // ��Ϣϵͳ��ʼ��
        virtual BOOL Create(const char* hostIp, int port) = 0;

        // ��Ϣϵͳֹͣ
        virtual void Destroy() = 0;

        // ע��/ɾ�� һ����Ϣ����ĺ���
        virtual void registerMessageHandler( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler) = 0;
        virtual void removeMessageHandler( int messageId, MessageTarget* pMessageTarget, PMSG_HANDLER pHandler) = 0;

        // ɾ��ĳ������ע���ȫ����Ϣ������
        virtual void removeObjectMessageHandler(MessageTarget* pMessageTarget) = 0;

        // ע�����⴦����
        // ����Ϣϵͳ�����쳣����Socket���ӶϿ�ʱ�����ô˺���
        virtual void registerExceptionHandler(MessageTarget* pMessageTarget, PMSG_HANDLER pHandler) = 0;
        virtual void removeExceptionHandler() = 0;

        // ������Ϣ
        virtual void sendMessage(BaseMessage* pBaseMessage) = 0;

		// ��ȡ��ǰ���ڴ�����Ϣ��ID
		// �������ΪMultiConferenceMatrixC���ӣ���Ҫ���ֲ�C++�ľ�̬ȱ��
		virtual int getCurrentMessageId() = 0;

		// ��ȡ��ǰ���ӵķ�����IP��ַ
		virtual string getRemoteIP() = 0;

	public:
		// ���õ�ǰ�û���id
		void setDefaultSenderId( __int64 uid ) { m_senderId = uid; };

		__int64 m_senderId;
    };

};


#endif
