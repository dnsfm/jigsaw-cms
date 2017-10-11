#pragma once

#include "..\..\message\MatrixC\MatrixCLib\MessageTarget.h"

class LServer;
class CRegisterUserDlg;

class RegisterUserMgr : public LyvcMessage::MessageTarget
{
public:
	RegisterUserMgr( LServer* pServer, CRegisterUserDlg* pRegisterDlg );
	~RegisterUserMgr(void);

	bool create();
	void destroy();

// ��Ϣ����
public:
	// ע�����û�
	void cmdRegisterUser( string userName, string lastName, string firstName, string email, string password, string domain);

//��Ϣ����
public:
	void RegisterUserResponse(LyvcMessage::BaseMessage* pMessage);

private:
	LServer* m_pServer;
	CRegisterUserDlg* m_pRegisterDlg;

};
