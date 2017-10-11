#pragma once

class CTCPSocket  
{
public:
	CTCPSocket();
	virtual ~CTCPSocket();

	// �������ķ�ʽ�������ݣ����ǳ��ִ��󣬷���֤����ȫ������
	BOOL Send(const char *pBuf,int iLen)const;

	// �������ķ�ʽ�������ݣ�һ�����յ����ݣ��������ݷ��ظ������ߣ�
	// ����֤���ܵ������ݵ��ڻ������ĳ���
	int Receive(char *pBuf, int iLen);

	// �������ķ�ʽ�������ݣ�ֱ����ȡ������������������Ȼ�󷵻�
	BOOL ReceiveBlock(char* pBuf, int iLen);

	SOCKET GetSocket();
	BOOL Create();
	BOOL Destroy();
	BOOL IsSocket();
	BOOL Connect(UINT uSocketPort, const char *pszSockAddr);

protected:
	SOCKET m_Socket;
};
