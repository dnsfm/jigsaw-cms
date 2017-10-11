#ifndef CONFERENCE_USER_H
#define CONFERENCE_USER_H

#include "model/DBUser.h"

class RunningConference;


class ConferenceUser {

protected:
	DBUser  m_baseInfo;                  // �û�������Ϣ
	__int64 m_nRoleID;                   // �û��ڻ����еĽ�ɫID
	int m_nUserType;					 // �û�����
	int m_nUserChannelNum;
	LONG m_nUserChannel;

public:

	// �û�����
	static const int NormalUser = 0;
	static const int LocalVirtualUser = 1;
	static const int RemoteVirtualUser = 2;


    // ȡ���û�ID
	USERID getId()const {return m_baseInfo.id;};	

    // ȡ���û��ʻ����� 
	string getName()const {return m_baseInfo.strName;};

    // ȡ���û���ʵ����
	string getRealName(){return m_baseInfo.getRealName();};
	
    // ȡ���û�Email��ַ
	string getEmail()const {return m_baseInfo.strEmail;};

    // ȡ��/�����û���ɫID
    __int64	getRoleID()const { return m_nRoleID;};
    void setRoleId(__int64 nRoleId) { m_nRoleID = nRoleId;};
	
	// ȡ��/�����û�����
	int getUserType()const {return m_nUserType;};
	void setUserType(int nUserType) { m_nUserType = nUserType;};

	int getUserChannelNum()const {return m_nUserChannelNum;};
	void setUserChannelNum(int userChannelNum) { m_nUserChannelNum = userChannelNum;};

	LONG getUserChannel()const {return m_nUserChannel;};
	void setUserChannel(LONG userChannel) { m_nUserChannel = userChannel;};

public:
	ConferenceUser(const DBUser& s);
    ~ConferenceUser();

	BOOL operator == (const ConferenceUser& r) const
	{
		return m_baseInfo.id == r.getId();
	};

};
#endif //CONFUSER_H
