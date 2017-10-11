#ifndef CONFERENCE_USER_MGR_H
#define CONFERENCE_USER_MGR_H

class ConferenceUser;

class ConferenceUserMgr {

private:

    // ������Ա�б�
    typedef map<USERID, ConferenceUser*> ConferenceUserMap;
    ConferenceUserMap m_users;

public:
    ConferenceUserMgr();
    ~ConferenceUserMgr();

public:
	unsigned int getCount(){ return m_users.size(); };
	// ������Աid
	void getConferenceUserIds(vector<__int64>* v, bool bIncludingVirtualUser = false);

	// ָ���û����������û�id
	static void getVirtualConferenceUserIds(USERID userId, int count, vector<__int64>* v);
	
	// ָ�������û�����channel
	static LONG getVirtualConferenceUserChannel(USERID userId);

	// �����û�id��channel�õ�����id
	static USERID getVirtualUserId(USERID userId, LONG handler);

	// ��������id�õ��û�id
	static USERID getRealIdByVirtualId(USERID virtualId);

	// ������Ա
    void addConferenceUser(ConferenceUser* pUser);

    // ������Ա
    ConferenceUser* getConferenceUserByID(USERID userId);

    // �ж���Ա�Ƿ��ڱ�������
    bool isUserInConference(USERID  userId);

    // ɾ����Ա
    void deleteConferenceUser(USERID userId);
};

#endif

