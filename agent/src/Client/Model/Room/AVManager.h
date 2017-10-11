#pragma once

class TransModel;
class CMeetingRoomFrame;
class UserVideoList;
class ConferenceUserMgr;

#include "message/MatrixC/MatrixCLib/MessageTarget.h"

class AVManager : public LyvcMessage::MessageTarget {

private:

    // ��ǰ�û�ID
	__int64 m_userId;

	// ��ǰ����ID
	__int64 m_conferenceId;

	// �����ҽ���
    CMeetingRoomFrame* m_pRoom;

    // ����ģ��
    TransModel* m_pTransModel;

    // ��ǰ�û�������������ԱID�б�
	list<USERID> m_AudioReceiveList;

    // ���ڽ��յ�ǰ�û���Ƶ�źŵ���ԱID�б�
	list<USERID> m_AudioSendList;

    // ��ǰ�û������տ�����ԱID�б�
	list<USERID> m_VideoReceiveList;

    // ���ڽ��յ�ǰ�û���Ƶ�źŵ���ԱID�б�
	list<USERID> m_VideoSendList;

	// �������������Ա
	list<USERID> m_AudioApplyList;

	// �����ͼ�����Ա
	list<USERID> m_VideoApplyList;

	// ����������ʾĳ���û�����Ƶ, ������Ҫ����
    // Э�鴫�ݲ�������ȷ����ʾ,��������ݽṹ���
    // �û�ID�ʹ��ھ���Ķ�Ӧ��
    map<USERID, HWND> m_userVideoWindowMap;

	map<USERID, list<USERID>* > m_VideoSendListMap;

	//�Ƿ����ڿ�����ѹ����Ƶ
	bool m_bTKLVideo[4];

public:

	AVManager(
		__int64 userId,                   // ��ǰ�û�ID
		__int64 conferenceId,             // ��ǰ����ID
		CMeetingRoomFrame* pRoom,         // �����ҽ���
        LyvcMessage::MatrixC* pMatrixC,   // ��Ϣϵͳ
        TransModel* pTransModel);         // ý���źŴ�������
	~AVManager();

	bool m_bIsInstantConf;

    bool create();
    void destroy();

	// ��ѹ�����ɼ��õ�����Ƶ���ݺͱ�����Ƶ����֮�佨������
	void initCompressionCardVideoWindow();


	/*
	 * ��Ϊͼ��Ҫ�ڱ��ش�����ʾ���������Ŀ��Ʒ�Ϊ�������֣�
	 * �Ƿ��ͺ��Ƿ�׽����һ��Ҫ����������һЩ��
	 */

    // ��ʼ������Ƶ�ź�
	void StartAudioSend();

    // ֹͣ������Ƶ�ź�
    void EndAudioSend();

    // ��ʼ��Ƶ��׽
    void StartVideoCapture();

    // ֹͣ��Ƶ��׽
    void EndVideoCapture();

    // ��ʼ������Ƶ�ź�
	void StartVideoSend(__int64 videoSenderID);

    // ֹͣ������Ƶ�ź�
	void EndVideoSend(__int64 videoSenderID);


    // ��ʼ����ĳ���û����͵���Ƶ�ź�
    void StartAudioRecv(USERID userId);

    // ֹͣ����ĳ���û����͵���Ƶ�ź�
    void EndAudioRecv(USERID userId);

    // ��ʼ����ĳ���û����͵���Ƶ�ź�
    void StartVideoRecv(USERID userId, HWND hVideoWnd, int nwidth, int nheight);

    // ֹͣ����ĳ���û����͵���Ƶ�ź�
    void EndVideoRecv(USERID userId);

public:
	void getApplyAndStopVideoList( list<__int64>& applyList, list<__int64>& stopList);
	void getApplyAndStopAudioList( list<__int64>& applyList, list<__int64>& stopList);

	// ��ʼ�ۿ�ĳ�ˣ��ṩ���߲����Ľӿ�
    void StartReceiveVideoFromUser(USERID userId, HWND hWnd);

    // ֹͣ�ۿ�ĳ�ˣ��ṩ���߲����Ľӿ�
    void StopReceiveVideoFromUser(USERID userId);

    // ��ʼ����ĳ�ˣ��ṩ���߲����Ľӿ�
    void StartReceiveAudioFromUser(USERID userId);

    // ֹͣ����ĳ�ˣ��ṩ���߲����Ľӿ�
    void StopReceiveAudioFromUser(USERID userId);

    // �Ƿ�������ĳ��
    bool isReceiveAudio(USERID userId);

    // �Ƿ����տ�ĳ��
    bool isReceiveVideo(USERID userId);

public:
    
    // Message Handler
    void ApplyAudio(LyvcMessage::BaseMessage* pBaseMessage);
    void RejectAudio(LyvcMessage::BaseMessage* pBaseMessage);
    void AgreeAudio(LyvcMessage::BaseMessage* pBaseMessage);
    void StopSendAudio(LyvcMessage::BaseMessage* pBaseMessage);
    void StopReceiveAudio(LyvcMessage::BaseMessage* pBaseMessage);
    void ApplyVideo(LyvcMessage::BaseMessage* pBaseMessage);
    void RejectVideo(LyvcMessage::BaseMessage* pBaseMessage);
    void AgreeVideo(LyvcMessage::BaseMessage* pBaseMessage);
    void StopSendVideo(LyvcMessage::BaseMessage* pBaseMessage);
    void StopReceiveVideo(LyvcMessage::BaseMessage* pBaseMessage);
    void UserChannelBroken(LyvcMessage::BaseMessage* pBaseMessage);
    void UserQuitConference(LyvcMessage::BaseMessage* pBaseMessage);

private:

	void AVManager::ProcessApplyVideo(_int64 recevierId);

private:

    // ��������
    void cmdApplyAudio(USERID userId);

    // ͬ������
    void cmdAgreeAudio(USERID userId);

    // �ܾ�����
    void cmdRejectAudio(USERID userId);

    // ֹͣ��������
    void cmdStopReceiveAudio(USERID userId);

    // ֹͣ��������
    void cmdStopSendAudio(USERID userId);

    // ����ͼ��
    void cmdApplyVideo(USERID userId);

    // ͬ��ͼ��
    void cmdAgreeVideo(USERID userId, USERID videoSenderId);

    // �ܾ�ͼ��
    void cmdRejectVideo(USERID userId);

    // ֹͣ����ͼ��
    void cmdStopReceiveVideo(USERID userId);

    // ֹͣ����ͼ��
    void cmdStopSendVideo(USERID videoSenderId, USERID receiverId);

public:
	static HWND localVideoWindow;

};

