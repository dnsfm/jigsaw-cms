#pragma once

// WebLauncherCtrl.h : CWebLauncherCtrl ActiveX �ؼ����������

// CWebLauncherCtrl : �й�ʵ�ֵ���Ϣ������� WebLauncherCtrl.cpp��

class CWebLauncherCtrl : public COleControl
{
	DECLARE_DYNCREATE(CWebLauncherCtrl)

// ���캯��
public:
	CWebLauncherCtrl();

// ��д
public:

// ʵ��
protected:
	~CWebLauncherCtrl();

	DECLARE_OLECREATE_EX(CWebLauncherCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CWebLauncherCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CWebLauncherCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CWebLauncherCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispidExpertId = 8,		dispidConferenceMode = 7,		dispidPort = 6,		dispidServerIP = 5,		dispidPassword = 4,		dispidUserName = 3,		dispidConferenceId = 2,		dispidstartConference = 1L
	};

	LONG startConference(void);
protected:
	LONGLONG m_ConferenceId;
	CString m_UserName;
	CString m_Password;
	CString m_ServerIP;
	LONG m_Port;
	LONG m_ConferenceMode;
	LONGLONG m_ExpertId;
};

