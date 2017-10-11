#pragma once

#include "message/MatrixC/MatrixCLib/MessageTarget.h"

class CContactDlg;
class Contact;
class ContactGroup;
class LServer;

class ContactMgr : public LyvcMessage::MessageTarget 
{
public:
	ContactMgr( LyvcMessage::MatrixC* pMatrixC, LServer* pServer );
	~ContactMgr();

	bool create() { return true; };
	void destroy() { };

    // ���������õ���
	ContactGroup* getContactGroupByName( string name, bool bIsCommon = false );

	// ������ϵ��id�õ�email
	string getEmailById( __int64 contactId );

	// ����id�õ�realname
	string getRealnameById( __int64 contactId );

	// ����״̬�õ���ϵ��
	void getContacts( vector<Contact*>& v, int status );

	// �õ�����˽����ϵ����
	void getPrivateGroupNames( vector<string>& v );

    // ��ȡDefault���ID
    __int64 getDefaultGroupId();

	// �������ڵ��ȡ��ϵ��
    Contact* getContactByTreeItem( HTREEITEM hItem );

    // �������ڵ��ȡ��
    ContactGroup* getContactGroupByTreeItem( HTREEITEM hItem );

    // ������ϵ�˶Ի���
	void setContactDlg( CContactDlg* pContactDlg );

	// �ж��Ƿ���˽����ϵ��
	bool isContactByEmail( string email );
	bool isContactById( __int64 uid );

	// �ж��Ƿ����ָ�����ֵ���
	bool isGroupExist(__int64 groupId, string name, bool bIsCommon = false );

	// �ж��Ƿ����ָ�����ֵ���
	bool isGroupExists(ContactGroup* pGroup, string name);

	// �Ƿ�����ϵ�˹���Ա
	BOOL isContactAdmin();

//��Ϣ����
public:
	// ���������ϵ��
	void cmdAddContact( Contact* pContact, ContactGroup* pGroup );

	// ���������Ϊ��ϵ��
	void cmdApplyContact(__int64 uid, string myName, __int64 groupId);

	// ��������
	void cmdSendLeaveword(__int64 contactId, string words, string myName);

    // ����Email������ϵ��
    void cmdSearchContact(string email);

    // ����ͬ������
    void cmdAgreeContact(__int64 contactId, string name, __int64 groupId);

    // ���;ܾ�����
    void cmdRejectContact(__int64 contactId, string name);

    // ���ʹ�����ɾ��һ����ϵ��
    void cmdRemoveContact( Contact* pContact );

    // ����ɾ��һ����
    void cmdRemoveGroup( ContactGroup* pGroup );

    // �������һ����
    void cmdAddGroup(string groupName, __int64 groupId);

    // ����������һ����
    void cmdRenameGroup( ContactGroup* pGroup, string newName );

    // ���ͽ���ϵ�˴�һ�����Ƶ���һ����
    void cmdMoveContactToGroup( Contact* pContact, ContactGroup* pToGroup );

	// ���͸���˽����ϵ��,
	// 1) receiverId = 0,ʹ��ϵ�˹���Ա��������ϵ�˻����Ϊ��ϵ��;
	// 2) recieverId != 0, bIsGroupId = false, ʹ��ϵ�˹���Ա��������ϵ����receiverId�û���Ϊ��ϵ��
	// 3) recieverId != 0, bIsGroupId = true, ʹ��ϵ�˹���Ա��������ϵ����receiverId���µ���ϵ�˻����Ϊ��ϵ��
	void cmdCopyContact( __int64 receiverId = 0, bool bIsGroupId = false );

// ��Ϣ����
public:    
    void UserDetail(LyvcMessage::BaseMessage* pMessage);
    void DefaultGroupId(LyvcMessage::BaseMessage* pBaseMessage);
    void ApplyContact(LyvcMessage::BaseMessage* pBaseMessage);
    void AddGroup(LyvcMessage::BaseMessage* pBaseMessage);
    void AddContact(LyvcMessage::BaseMessage* pBaseMessage);
    void AgreeContact(LyvcMessage::BaseMessage* pBaseMessage);
    void RejectContact(LyvcMessage::BaseMessage* pBaseMessage);
    void UserNotFoundByEmail(LyvcMessage::BaseMessage* pBaseMessage);
    void RemoveContact(LyvcMessage::BaseMessage* pBaseMessage);
    void UpdateContactStatus(LyvcMessage::BaseMessage* pBaseMessage);
	void Leaveword(LyvcMessage::BaseMessage* pBaseMessage);
	void SearchContactResult(LyvcMessage::BaseMessage* pBaseMessage);
	void UserChannelBroken(LyvcMessage::BaseMessage* pBaseMessage);
	void SetContactAdmin(LyvcMessage::BaseMessage* pBaseMessage);
	void ConferenceNotice(LyvcMessage::BaseMessage* pMessage);
	void SystemMessage(LyvcMessage::BaseMessage* pMessage);
	//�����Ϣ������
	void MoveContactToGroup(LyvcMessage::BaseMessage* pMessage);	//�ƶ���
	void ChangeGroupName(LyvcMessage::BaseMessage* pMessage);		//�޸�����
//	void RemoveContact(LyvcMessage::BaseMessage* pMessage);			//ɾ���û�

public:
    CContactDlg* m_pContactDlg;

private:
	// ���ڷ�����
	LServer* m_pServer;
	// ������Լ�Ϊ��ϵ�˵��û�
	list<__int64> m_ApplyList;

    // ��Ӧ����ϵ�˶Ի�������
//    CContactDlg* m_pContactDlg;

 	// ��ϵ�˺���,��ContactDlg�����ؼ��ϵĽڵ��Ӧ
	typedef map<HTREEITEM, ContactGroup*>	ContactGroupMap;
	typedef map<HTREEITEM, Contact*>		ContactMap;
	ContactGroupMap m_ContactGroups;
	ContactMap		m_Contacts;
	
	// �յ�����������
	int m_nReceivedLeavewords;

	// ��ϵ�˹���Ա��־
	BOOL m_bContactAdmin;

	// Ĭ����id
	__int64 m_DefaultGroupId;

private:
	// ������ϵ��״̬
	void setContactStatus( Contact* pContact, int nStatus );
	// ɾ����
	void removeContactGroup( ContactGroup* pGroup );
	// ɾ����ϵ��
	void removeContact( Contact* pContact ); 
	// ������id������������
	ContactGroup* findContactGroup( __int64 groupId, string groupName, bool bIsCommon );
	// ������id������������
	ContactGroup* searchContactGroup( __int64 groupId, string groupName, bool bIsCommon );
	// ����id��email������ϵ��
	Contact* findContact( __int64 contactId, string email, bool bIsCommon, bool bIgnoreIfCommon = false );
};
