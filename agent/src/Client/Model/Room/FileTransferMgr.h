#pragma once

#include "message\matrixc\matrixclib\messagetarget.h"

class CMeetingRoomFrame;
class RunningConference;

#define WM_SEND_NEXT_FILE WM_USER + 128

class FileTransferTask
{
public:
	FileTransferTask() { m_bCanSend = false; m_uid = 0; };

	__int64 m_uid; 	       // ���ͻ������id
    string m_fileName; 	   // �����ļ���(����·��)
	__int64 m_fileLength;  // �ļ�����
	bool m_bCanSend;       // �Ƿ���Է���
	string m_storeName;    // ����·��

	FileTransferTask& operator=(const FileTransferTask& ftt)
	{
		m_uid = ftt.m_uid;
		m_fileName = ftt.m_fileName;
		m_fileLength = ftt.m_fileLength;
		m_bCanSend = ftt.m_bCanSend;
		m_storeName = ftt.m_storeName;
		return *this;
	}
};


class FileTransferMgr :	public LyvcMessage::MessageTarget
{
public:
	FileTransferMgr(LyvcMessage::MatrixC* pMatrixC, CMeetingRoomFrame* pRoom, RunningConference* pConferenc);
	~FileTransferMgr(void);

	bool create();
	void destroy();

	void sendNextFile();
	void recvNextFile();
	void exitSendFileThread();

	//��Ϣ����
	void applySendFile(__int64 receiverId, string fileName, __int64 fileLength);
	void rejectReceiveFile(__int64 receiverId, string fileName);
	void agreeReceiveFile(__int64 receiverId, string fileName, __int64 fileLength);
	void stopSendFile(__int64 receiverId, string fileName);
	void stopReceiveFile(__int64 receiverId, string fileName);
	void requestSendFile(__int64 receiverId, string fileName);

	//��Ϣ����
	void ApplySendFile(LyvcMessage::BaseMessage* pBaseMessage);
	void RejectReceiveFile(LyvcMessage::BaseMessage* pBaseMessage);
	void AgreeReceiveFile(LyvcMessage::BaseMessage* pBaseMessage);
	void StopSendFile(LyvcMessage::BaseMessage* pBaseMessage);
	void StopReceiveFile(LyvcMessage::BaseMessage* pBaseMessage);
	void SendFileData(LyvcMessage::BaseMessage* pBaseMessage);
	void RequestSendFile(LyvcMessage::BaseMessage* pBaseMessage);
	void UserChannelBroken(LyvcMessage::BaseMessage* pBaseMessage);
	void UserQuitConference(LyvcMessage::BaseMessage* pBaseMessage);

	// ȡ�ñ����ڻ����н��յ��ļ����ļ���·��(����������\����)
	static const string getIncomeFileSavePosition();

private:
	// ���ڷ����ļ����ݵ��߳�
	static UINT WINAPI sendFileThreadProc(LPVOID lpParameter);

private:
	CMeetingRoomFrame* m_pRoom;
	RunningConference* m_pConference;

	//���Ͷ���
	vector<FileTransferTask> m_sendList;
	//���ն���
	vector<FileTransferTask> m_recvList;
	//�������Լ������ļ��Ķ���
	vector<FileTransferTask> m_applyList;

	HANDLE m_hEvent;
	unsigned int m_nThreadId;
	HANDLE m_hSendThread;

	FileTransferTask m_curSendTask;
	FileTransferTask m_curRecvTask;
	bool m_bStopCurrentSend;
	bool m_bIsReceiving;
	bool m_bExitSendThread;
	bool m_bIsSending;
};
