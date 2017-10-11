#pragma once

#include "message/MatrixC/MatrixCLib/MessageTarget.h"
#include "Desktop/LyvcDesktopClient/ClientNotifier.h"

class RunningConference;
class DesktopClient;
class DesktopServer;
class Notifier;
class TransModel;

class DesktopManager : public LyvcMessage::MessageTarget 
{
public:
	DesktopManager(
        LyvcMessage::MatrixC* pMatrixC,   // ��Ϣϵͳ
		RunningConference* pConference,   // �������
		TransModel* pTransModel);         // ý�崫������
	~DesktopManager(void);

	bool create();
	void destroy();

	// ֹͣ�ṩ���湲��
	void stopDesktopServer();

//��Ϣ����
public:
	//���湲��
    void ApplyDesktop(LyvcMessage::BaseMessage* pBaseMessage);//����
	void AgreeDesktop(LyvcMessage::BaseMessage* pBaseMessage);//ͬ������
	void RejectDesktop(LyvcMessage::BaseMessage* pBaseMessage);//�ܾ�
	void InviteDesktop(LyvcMessage::BaseMessage* pBaseMessage);//����
	void AgreeInviteDesktop(LyvcMessage::BaseMessage* pBaseMessage);//ͬ������
	void RejectInviteDesktop(LyvcMessage::BaseMessage* pBaseMessage);//�ܾ�����
	void StopReceiveDesktop(LyvcMessage::BaseMessage* pBaseMessage);//�����ָֹͣ���ͻ��˹ۿ�����
	void StopSendDesktop(LyvcMessage::BaseMessage* pBaseMessage);//�ͻ�������ֹͣ�˹ۿ�����
    void DesktopClientRequestUpdate(LyvcMessage::BaseMessage* pBaseMessage); //�ͻ�������ʼ����

    //Զ�̿���
    void ApplyControlDesktop(LyvcMessage::BaseMessage* pBaseMessage);//����
	void AgreeControlDesktop(LyvcMessage::BaseMessage* pBaseMessage);//ͬ��
	void RejectControlDesktop(LyvcMessage::BaseMessage* pBaseMessage);//�ܾ�
	void StopSendControlDesktop(LyvcMessage::BaseMessage* pBaseMessage);//������ջؿ���
	void StopReceiveControlDesktop(LyvcMessage::BaseMessage* pBaseMessage);//�ͻ��˷�������

    void UserQuitConference(LyvcMessage::BaseMessage* pBaseMessage);
    void UserChannelBroken(LyvcMessage::BaseMessage* pBaseMessage); //ĳ���ͻ��������˳�

//��Ϣ����
public:
	//���湲��
	void cmdApplyDesktop(USERID userId);
	void cmdAgreeDesktop(USERID userId);
	void cmdRejectDesktop(USERID userId);
	void cmdInviteDesktop(USERID userId);
	void cmdAgreeInviteDesktop(USERID userId);
	void cmdRejectInviteDesktop(USERID userId);
	void cmdStopReceiveDesktop(USERID userId);
	void cmdStopSendDesktop(USERID userId);

	//Զ�̿���
	void cmdApplyControlDesktop(USERID userId);
	void cmdAgreeControlDesktop(USERID userId);
	void cmdRejectControlDesktop(USERID userId);
	void cmdStopSendControlDesktop(USERID userId);//�ͻ��˷�������
	void cmdStopReceiveControlDesktop();//������ջؿ���

public:
	//�Ƿ����������û�
	BOOL canInviteDesktop( __int64 uid );

	//�Ƿ����ֹͣ���û��ۿ��ҵ�����
	BOOL canStopSendDesktopToUser( __int64 uid = 0 );
	
	//�Ƿ��������û�����ۿ�
	BOOL canApplyDesktop( __int64 uid );

	//�Ƿ����ֹͣ�ۿ����û�
	BOOL canStopReceiveDesktopFromUser( __int64 uid = 0 );

	//�Ƿ�����������
	BOOL canApplyControlDesktop( __int64 uid = 0 );

	//�Ƿ����ֹͣ����
	BOOL canStopSendControlDesktopToUser( __int64 uid = 0 );

	//�Ƿ����ֹͣ���ܿ���
	BOOL canStopReceiveControlDesktopFromUser( __int64 uid = 0 );

	//��ǰ�ۿ����������д��������û�id,Ϊ0û��
	__int64 getTopDesktopClientId();

private:
	//�Ƿ���������
	BOOL isUserInApplyList(__int64 uid);

	//�Ƿ���������
	BOOL isUserInInviteList(__int64 uid);

	//�Ƿ��ڿ��Լ�
	BOOL isUserInClientList(__int64 uid);

	//�Լ��Ƿ��ڿ��Է�
	BOOL isUserInServerList(__int64 uid);

	//�Լ��Ƿ��ڿ��ƶԷ�
	BOOL isControlUser(__int64 uid);

	//�Ƿ��û�����
	BOOL isControledByUser(__int64 uid);

private:
	// ý�崫������
	TransModel* m_pTransModel;
	// ���ڻ���
	RunningConference*	m_pConference;
	// ���ڹۿ��Լ���Ļ���û�
	list<USERID> m_DesktopClientList;
	// �Լ����ڹۿ����û�
	list<USERID> m_DesktopServerList;
	// ���ڿ����Լ���Ļ���û�
	USERID m_ControlBy;
	// �Լ����ڿ��Ƶ��û�
	list<USERID> m_UnderControlList;
	// �Լ���������ۿ����û�
	list<USERID> m_ApplyList;
	// �Լ�����������Ƶ��û�
	list<USERID> m_ApplyControlList;
	// �Լ���������ۿ����û�
	list<USERID> m_InviteList;
	// ��������ۿ��Լ����û��б�
	list<USERID> m_ApplyMeList;
	// ���������Լ��ۿ����û��б�
	list<USERID> m_InviteMeList;
	// ������������Լ����û��б�
	list<USERID> m_ApplyControlMeList;

	Notifier* m_notifier;
};

class Notifier : public ClientNotifier
{
public:
	virtual void clientClosed(__int64 uid);

	void setManager(DesktopManager* manager);

private:
	DesktopManager* m_manager;	
};

