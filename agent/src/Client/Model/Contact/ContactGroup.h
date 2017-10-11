#pragma once

class Contact;

class ContactGroup
{
public:
	ContactGroup( __int64 id, string name, bool bIsCommon, ContactGroup* pParent )
	{
		m_Id		= id;
		m_sName		= name;
		m_bIsCommon = bIsCommon;
		m_pParent	= pParent;
	};
	// �Ƿ��ǹ�����ϵ����
	bool					m_bIsCommon;
	// ��id
    __int64					m_Id;
	// ����
    string					m_sName;
	// ��Ӧ�����ڵ�
	HTREEITEM				m_hItem;
	// ����
	ContactGroup*			m_pParent;
	// ���е���ϵ��
    vector<Contact*>		m_Contacts;
	// ����
	vector<ContactGroup*>	m_subGroups;
};
