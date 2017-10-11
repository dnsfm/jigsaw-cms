#pragma once

class TCPUser;
class AcceptThread;

class TCPForward
{
public:

    TCPForward();
    ~TCPForward();

public:

    // ��ʼ����
    BOOL start(int port);

    // ֹͣ����
    void stop();

public:

    //����һ���û�
	void addUser(__int64 userId);

    //ɾ��һ���û�
	void removeUser(__int64 userid);

    // ���û�֮�������������ݷ��͹�ϵ
	void addDesktopRelation(__int64 from, __int64 to);

    // ɾ���û�֮����������ݷ��͹�ϵ
    void removeDesktopRelation(__int64 from, __int64 to);

    // ���û�֮�����Ӱװ����ݷ��͹�ϵ
	void addWhiteboardRelation(__int64 userId, __int64 confId);

    // ɾ���û�֮��İװ����ݷ��͹�ϵ
    void removeWhiteboardRelation(__int64 userId, __int64 confId);

private:

    // Accept connection thread
    AcceptThread* m_pAcceptThread;

    // Route table
	CRITICAL_SECTION m_cs;

	// User id and socket map.
	typedef std::map<__int64, TCPUser*> TCPUserMap;
	TCPUserMap m_users;

	// User id and all peer who share his desktop.
	typedef std::map<__int64, list<__int64>*> TCPUserRelationMap;
	TCPUserRelationMap m_desktopRelations;
	TCPUserRelationMap m_whiteboardRelations;

	friend AcceptThread;
	friend TCPUser;
};
