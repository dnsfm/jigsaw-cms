#pragma once

#include "FvsmUser.h"
#include "WinsockWrapper/WinsockWrapper/UdpSocket.h"

class UDPForward
{
private:	

    //ϵͳ�����е��û�
    typedef		map<__int64, FvsmUser*> FvsmUserMap;	
	FvsmUserMap	m_allUsers;

    //ʹ��һ��ȫ�ֹؼ���������ý��ת����ϵ����
	CRITICAL_SECTION	m_cs;

    // ����ý�����ݵ�UDP Socket
	CUDPSocket	m_udpSocket;

    // UDP �߳̾��
	HANDLE	m_hUSockThread;

    // UDP Running flag
    BOOL m_bUDPRuningFlag;

    // ý������̺߳���
	static unsigned int WINAPI UdpSockThreadProc(LPVOID lpParameter);

public:

    UDPForward();
    ~UDPForward();

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

    // ���û�֮������ý�巢�͹�ϵ
	void addMediaRelation(__int64 from, __int64 to, int type);

    // ɾ���û�֮���ý�巢�͹�ϵ
    void removeMediaRelation(__int64 from, __int64 to, int type);	

private:

    // ��ȡ�ڲ���ĳ���û������û���ҵ��򷵻�null
    FvsmUser* getUser(__int64 userid);

    // ����ĳ���û���ý��ת����ϵ�Լ�ý������,ת��UDP����
    void forwardData(FvsmUser* pUser, char* buffer, int nLen, int dataType);
};

