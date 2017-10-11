#pragma once


class ClientNotifier;

namespace LyvcMessage
{
	class MatrixC;
};

class DesktopClient
{
public:
	virtual ~DesktopClient(void);

public:
	static DesktopClient* getInstance();

	virtual void start(LyvcMessage::MatrixC* pMatrixC) = 0;
	virtual void stop() = 0;

	virtual void addClient(__int64 uid, std::string name, ClientNotifier* pClientNotifier) = 0;
	virtual void addNotifier(__int64 uid, ClientNotifier* notifier) = 0;
	virtual void remClient(__int64 uid) = 0;
	virtual void startControl(__int64 uid) = 0;
	virtual void stopControl(__int64 uid) = 0;

	// �Ƿ��ڹۿ�ĳ���û�������
	virtual bool isWatchingUser(__int64 uid) = 0;

	// ���նԷ����ݹ����������ź�����
	virtual void receiveDesktopPacket(char* buffer, int len, __int64 uid) = 0;

	// �ҳ���ǰ�ۿ������������ϲ���Ǹ�
	virtual __int64 getTopDesktopClientId() = 0;


protected:
	DesktopClient(void);
};
