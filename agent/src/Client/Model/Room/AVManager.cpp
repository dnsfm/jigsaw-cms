#include "stdafx.h"
#include "FLVCC.h"
#include "AVManager.h"
#include "Model/Room/RunningConference.h"
#include "UI/MeetingRoom/RoomMainFrm.h"
#include "Transfer/TransModel.h"
#include "Video/VideoConfig/VideoConfig.h"
#include "Video/VideoCapture/TklSdk.h"
#include "ConferenceUserMgr.h"
#include "Model/CooperationManager.h"
#include "..\..\..\Common\Common\Base64Coder\Base64Coder.h"

#include "message/MatrixC/MatrixCLib/MatrixC.h"
#include "message/MatrixC/MatrixCLib/message/ApplyAudio.h"
#include "message/MatrixC/MatrixCLib/message/AgreeAudio.h"
#include "message/MatrixC/MatrixCLib/message/RejectAudio.h"
#include "message/MatrixC/MatrixCLib/message/StopSendAudio.h"
#include "message/MatrixC/MatrixCLib/message/StopReceiveAudio.h"
#include "message/MatrixC/MatrixCLib/message/ApplyVideo.h"
#include "message/MatrixC/MatrixCLib/message/AgreeVideo.h"
#include "message/MatrixC/MatrixCLib/message/RejectVideo.h"
#include "message/MatrixC/MatrixCLib/message/StopSendVideo.h"
#include "message/MatrixC/MatrixCLib/message/StopReceiveVideo.h"
#include "message/MatrixC/MatrixCLib/message/UserQuitConference.h"
#include "message/MatrixC/MatrixCLib/message/UserChannelBroken.h"

#pragma message ("Desktop�ڵ���transModel��ʱ��û��ʹ�����ü���, AVManagerҲ���Կ�����ô��")
#pragma message ("�������Ա�����������ü���")

HWND AVManager::localVideoWindow = NULL;

AVManager::AVManager(
		__int64 userId,
		__int64 conferenceId,
		CMeetingRoomFrame* pRoom,
        LyvcMessage::MatrixC* pMatrixC,
        TransModel* pTransModel) : LyvcMessage::MessageTarget(pMatrixC)
{
    this->m_userId = userId;
    this->m_conferenceId = conferenceId;
    this->m_pRoom = pRoom;
    this->m_pTransModel = pTransModel;
	m_bIsInstantConf = false;

    // ע����Ϣ������
    m_pMatrixC->registerMessageHandler(LyvcMessage::ApplyAudio::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::ApplyAudio));
    m_pMatrixC->registerMessageHandler(LyvcMessage::AgreeAudio::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::AgreeAudio));
    m_pMatrixC->registerMessageHandler(LyvcMessage::RejectAudio::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::RejectAudio));
    m_pMatrixC->registerMessageHandler(LyvcMessage::StopSendAudio::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::StopSendAudio));
    m_pMatrixC->registerMessageHandler(LyvcMessage::StopReceiveAudio::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::StopReceiveAudio));
    m_pMatrixC->registerMessageHandler(LyvcMessage::ApplyVideo::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::ApplyVideo));
    m_pMatrixC->registerMessageHandler(LyvcMessage::AgreeVideo::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::AgreeVideo));
    m_pMatrixC->registerMessageHandler(LyvcMessage::RejectVideo::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::RejectVideo));
    m_pMatrixC->registerMessageHandler(LyvcMessage::StopSendVideo::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::StopSendVideo));
    m_pMatrixC->registerMessageHandler(LyvcMessage::StopReceiveVideo::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::StopReceiveVideo));
    m_pMatrixC->registerMessageHandler(LyvcMessage::UserChannelBroken::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::UserChannelBroken));
    m_pMatrixC->registerMessageHandler(LyvcMessage::UserQuitConference::id, this, static_cast<LyvcMessage::PMSG_HANDLER>(AVManager::UserQuitConference));
}

AVManager::~AVManager()
{
	// ɾ����Ϣ������
    m_pMatrixC->removeObjectMessageHandler(this);
}

bool AVManager::create()
{
    // ��ʼ��Ƶ��׽
    this->StartVideoCapture();

    // ��ʼ��ʾ������Ƶ
    m_pTransModel->addLocalVideoWindow( m_pRoom->getLocalVideoWindow(), m_conferenceId);
	localVideoWindow = m_pRoom->getLocalVideoWindow();
	return true;
}


// RunningConference::JoinConferenceResponse() call this function

void AVManager::initCompressionCardVideoWindow()
{
	for(int i = 0; i < 4; i++)
	{
		m_bTKLVideo[i] = false;
	}
}

void AVManager::destroy()
{
    // ֹͣ��ʾ������Ƶ
    m_pTransModel->removeLocalVideoWindow( m_conferenceId);

	vector<__int64> v;
	ConferenceUserMgr::getVirtualConferenceUserIds(this->m_userId, ::GetApp()->getCooperationManager()->getTKLChannelNumber(), &v);
	// ֹͣ�ۿ�����ѹ����Ƶ
	for( UINT i = 0; i < v.size(); i++ )
	{
		if( m_bTKLVideo[i] == true )
		{
			this->EndVideoRecv(v.at(i));
		}
	}

	// ֹͣ��Ƶ����
	if( this->m_AudioSendList.size() > 0 )
	{
		this->EndAudioSend();
	}

    // ֹͣ��Ƶ����
	if( this->m_VideoSendList.size() > 0 )
	{
		this->EndVideoSend(this->m_userId);
	}

    // �����������ڽ��������������ˣ�֪ͨ������������ٷ���
    list<USERID>::iterator it = this->m_AudioSendList.begin();
    while( it != this->m_AudioSendList.end())
    {
        this->cmdStopSendAudio(*it);
        it++;
    }

    // �����������ڽ�������ͼ����ˣ�֪ͨ������������ٷ���
    it = this->m_VideoSendList.begin();
    while( it != this->m_VideoSendList.end())
    {
		this->cmdStopSendVideo(this->m_userId, *it);
        it++;
    }

    // ���������������ڽ����������ˣ�֪ͨ�����������Transmodel��������
    it = this->m_AudioReceiveList.begin();
    while( it != this->m_AudioReceiveList.end() )
    {
        this->cmdStopReceiveAudio(*it);
        this->EndAudioRecv(*it);
        it++;
    }

    // ���������������ڽ���ͼ����ˣ�֪ͨ�����������Transmodel�����տ�
    it = this->m_VideoReceiveList.begin();
    while( it != this->m_VideoReceiveList.end() )
    {
        this->cmdStopReceiveVideo(*it);
        this->EndVideoRecv(*it);
        it++;
    }

 	for(int i = 0;i < v.size();i++){
		map<USERID, list<USERID>* >::iterator mapit = m_VideoSendListMap.find(v.at(i));
		list<USERID>* tempList;
		if(mapit != m_VideoSendListMap.end()){
			tempList = mapit->second;
			// ֹͣ��Ƶ����
			if(tempList->size() > 0){
				this->EndVideoSend(v.at(i));
			}
			// �����������ڽ�������ͼ����ˣ�֪ͨ������������ٷ���
			it = tempList->begin();
			while( it != tempList->end())
			{
				this->cmdStopSendVideo(v.at(i), *it);
				it++;
			}
		}
	}

    map<USERID, list<USERID>* >::iterator vslmIterator = m_VideoSendListMap.begin();
    while( vslmIterator != m_VideoSendListMap.end())
    {
        list<USERID>* mList = vslmIterator->second;
        delete mList;
        vslmIterator++;
    }
    m_VideoSendListMap.clear();


   // ֹͣ��Ƶ��׽
    this->EndVideoCapture();
}

void AVManager::StartVideoCapture()
{
	::GetApp()->getCooperationManager()->startVideoCapture();
}

void AVManager::EndVideoCapture()
{
	::GetApp()->getCooperationManager()->stopVideoCapture();
}

void AVManager::StartAudioSend()
{
	m_pTransModel->startSendAudio();
}

void AVManager::EndAudioSend()
{
	m_pTransModel->stopSendAudio();
}

void AVManager::StartVideoSend(__int64 videoSenderID)
{
    m_pTransModel->startSendVideo(videoSenderID);
}

void AVManager::EndVideoSend(__int64 videoSenderID)
{
    m_pTransModel->stopSendVideo(videoSenderID);
}

void AVManager::StartAudioRecv(USERID userId)
{
	// Windows tree control has this side effect.
	if( userId == this->m_userId )
	{
		return;
	}

    this->m_pTransModel->addUserAudioPlay(userId);
}

void AVManager::EndAudioRecv(USERID userId)
{
	// Windows tree control has this side effect.
	if( userId == this->m_userId )
	{
		return;
	}

    this->m_pTransModel->removeUserAudioPlay(userId);
}

void AVManager::StartVideoRecv(USERID userId, HWND hVideoWnd, int nwidth, int nheight)
{
	// Windows tree control has this side effect.
	if( userId == this->m_userId )
	{
		return;
	}
	//���ñ��عۿ�ѹ����Ƶ��־
	if( userId > 100000000000000000L )
	{
		if( ConferenceUserMgr::getRealIdByVirtualId(userId) == this->m_userId )
		{
			LONG handle = ConferenceUserMgr::getVirtualConferenceUserChannel(userId);
			if( this->m_bTKLVideo[handle-1] )
				return;
			this->m_bTKLVideo[handle-1] = true;
		}
	}

    m_pTransModel->addUserVideoPlay(userId, hVideoWnd, m_conferenceId, nwidth, nheight);
}

void AVManager::EndVideoRecv(USERID userId)
{
	// Windows tree control has this side effect.
	if( userId == this->m_userId )
	{
		return;
	}
	//���ñ��عۿ�ѹ����Ƶ��־
	if( userId > 100000000000000000L )
	{
		if( ConferenceUserMgr::getRealIdByVirtualId(userId) == this->m_userId )
		{
			LONG handle = ConferenceUserMgr::getVirtualConferenceUserChannel(userId);
			if( !this->m_bTKLVideo[handle-1] )
				return;
			this->m_bTKLVideo[handle-1] = false;
		}
	}

    m_pTransModel->removeUserVideoPlay(userId, m_conferenceId);
}

void AVManager::StartReceiveAudioFromUser(USERID userId)
{
    // ��֤����˲������ǵĽ����б���
    if( find(m_AudioReceiveList.begin(), m_AudioReceiveList.end(), userId) != m_AudioReceiveList.end() )
	{
		ASSERT(FALSE);
		return;
	}
    this->cmdApplyAudio(userId);
}

void AVManager::StopReceiveAudioFromUser(USERID userId)
{
    // ��֤����������ǵĽ����б���
    list<USERID>::iterator it = find(m_AudioReceiveList.begin(), m_AudioReceiveList.end(), userId);
    if( it == m_AudioReceiveList.end() )
	{
		ASSERT(FALSE);
		return;
	}
    m_AudioReceiveList.erase(it);

    // ֪ͨ�ײ����, ֹͣ����
    this->EndAudioRecv(userId);

    // ����������Է�
    this->cmdStopReceiveAudio(userId);
    return;
}

void AVManager::StartReceiveVideoFromUser(USERID userId, HWND hWnd)
{
    // ��֤����˲������ǵĽ����б���
    _ASSERTE( find(m_VideoReceiveList.begin(), m_VideoReceiveList.end(), userId) == m_VideoReceiveList.end());

    this->m_userVideoWindowMap.insert( map<USERID, HWND>::value_type(userId, hWnd));
    this->cmdApplyVideo(userId);
}

void AVManager::StopReceiveVideoFromUser(USERID userId)
{
    // ��֤����������ǵĽ����б���
    list<USERID>::iterator it = find(m_VideoReceiveList.begin(), m_VideoReceiveList.end(), userId);
    _ASSERTE( it != m_VideoReceiveList.end());
    m_VideoReceiveList.erase(it);

    // ֪ͨTransModelȡ��������Ƶ
    this->EndVideoRecv(userId);

    // ����������Է�
    this->cmdStopReceiveVideo(userId);
    return;
}

bool AVManager::isReceiveAudio(USERID userId)
{
    return find(m_AudioReceiveList.begin(), m_AudioReceiveList.end(), userId) != m_AudioReceiveList.end();
}

bool AVManager::isReceiveVideo(USERID userId)
{
	if( userId > 100000000000000000L )
	{
		if( ConferenceUserMgr::getRealIdByVirtualId(userId) == this->m_userId )
		{
			LONG handle = ConferenceUserMgr::getVirtualConferenceUserChannel(userId);
			return this->m_bTKLVideo[handle-1];
		}
	}
    return find(m_VideoReceiveList.begin(), m_VideoReceiveList.end(), userId) != m_VideoReceiveList.end();
}

void AVManager::getApplyAndStopVideoList( list<__int64>& applyList, list<__int64>& stopList)
{
	list<__int64>::iterator iter;
	for( iter = m_VideoReceiveList.begin(); iter != m_VideoReceiveList.end(); iter++ )
	{
		if( find( applyList.begin(), applyList.end(), *iter ) == applyList.end() )
		{
			stopList.push_back( *iter );
		}
		else
		{
			applyList.remove( *iter );
		}
	}
	vector<__int64> v;
	ConferenceUserMgr::getVirtualConferenceUserIds(this->m_userId, ::GetApp()->getCooperationManager()->getTKLChannelNumber(), &v);
	for( UINT i = 0; i < v.size(); i++ )
	{
		if( this->m_bTKLVideo[i] )
		{
			if( find( applyList.begin(), applyList.end(), v.at(i) ) == applyList.end() )
			{
				stopList.push_back( v.at(i) );
			}
			else
			{
				applyList.remove( v.at(i) );
			}
		}
	}
}

void AVManager::getApplyAndStopAudioList( list<__int64>& applyList, list<__int64>& stopList)
{
	list<__int64>::iterator iter;
	for( iter = m_AudioReceiveList.begin(); iter != m_AudioReceiveList.end(); iter++ )
	{
		if( find( applyList.begin(), applyList.end(), *iter ) == applyList.end() )
		{
			stopList.push_back( *iter );
		}
		else
		{
			applyList.remove( *iter );
		}
	}
}

void AVManager::ApplyAudio(LyvcMessage::BaseMessage* pBaseMessage)
{
	if( !m_pRoom->IsWindowVisible() )
		m_pRoom->ShowWindow( SW_NORMAL );

	LyvcMessage::ApplyAudio* pCmd = (LyvcMessage::ApplyAudio*)pBaseMessage;
    TRACE1("%d apply audio\n", pCmd->senderId);

	// ��������û����ڷ����б���
	BOOL b = ( find(m_AudioSendList.begin(), m_AudioSendList.end(), pCmd->senderId) == m_AudioSendList.end() );
	if( !b )
	{
	    _ASSERT( FALSE );
		TRACE1( "receive duplicate apply audio from user %d", pCmd->senderId );
		return;
	}
    // ͬ��
    this->cmdAgreeAudio(pCmd->senderId);

	// ��ʱ�����У��������໥��
	if( m_bIsInstantConf && !isReceiveAudio( pCmd->senderId ) )
		this->cmdApplyAudio( pCmd->senderId );

    // ��������б�Ϊ��, ��������(���ǵ�һ���������ǵ��û�)
    if( this->m_AudioSendList.empty() )
    {
        this->StartAudioSend();
    }

    // ���ӵ������б�
    this->m_AudioSendList.push_back(pCmd->senderId);
}

void AVManager::RejectAudio(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::RejectAudio* pCmd = (LyvcMessage::RejectAudio*)pBaseMessage;
    TRACE1("%d reject audio\n", pCmd->senderId);

	// Remove the user from apply list
	m_AudioApplyList.remove(pCmd->senderId);
}

void AVManager::AgreeAudio(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::AgreeAudio* pCmd = (LyvcMessage::AgreeAudio*)pBaseMessage;
    TRACE1("%d agree audio\n", pCmd->senderId);

	// Remove the user from apply list
	m_AudioApplyList.remove(pCmd->senderId);

    // ��������û����ڽ����б���
    _ASSERT( find(m_AudioReceiveList.begin(), m_AudioReceiveList.end(), pCmd->senderId) == m_AudioReceiveList.end());

    // ��������
    this->StartAudioRecv(pCmd->senderId);

    // ���ӵ������б�
    this->m_AudioReceiveList.push_back(pCmd->senderId);

	// ���½�����ʾ
	this->m_pRoom->setIsListenFlag(true, pCmd->senderId);
}

void AVManager::StopSendAudio(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::StopSendAudio* pCmd = (LyvcMessage::StopSendAudio*)pBaseMessage;
    TRACE1("%d stop send audio\n", pCmd->senderId);

    // ��������û������ǵĽ����б���
    list<USERID>::iterator it = find(m_AudioReceiveList.begin(), m_AudioReceiveList.end(), pCmd->senderId);
    _ASSERTE( it != m_AudioReceiveList.end());
    m_AudioReceiveList.erase(it);

    // ֪ͨ�ײ����ֹͣ����
    this->EndAudioRecv(pCmd->senderId);
}

void AVManager::StopReceiveAudio(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::StopReceiveAudio* pCmd = (LyvcMessage::StopReceiveAudio*)pBaseMessage;
    TRACE1("%d stop receive audio\n", pCmd->senderId);

    // ��������û������ǵķ����б���
    list<USERID>::iterator it = find(m_AudioSendList.begin(), m_AudioSendList.end(), pCmd->senderId);
    _ASSERTE( it != m_AudioSendList.end());
    m_AudioSendList.erase(it);

    // ��������б�Ϊ�գ�֪ͨTransModelֹͣ������Ƶ
    if( m_AudioSendList.empty() )
    {
        this->EndAudioSend();
    }
}

void AVManager::ProcessApplyVideo(_int64 recevierId){
}

void AVManager::ApplyVideo(LyvcMessage::BaseMessage* pBaseMessage)
{
	if( !m_pRoom->IsWindowVisible() )
		m_pRoom->ShowWindow( SW_NORMAL );
    LyvcMessage::ApplyVideo* pCmd = (LyvcMessage::ApplyVideo*)pBaseMessage;
    TRACE1("%d apply video\n", pCmd->senderId);

    // ͬ��
	this->cmdAgreeVideo(pCmd->senderId, pCmd->receiverId);

	if(pCmd->receiverId == this->m_userId){
		// ��������û����ڷ����б���
		_ASSERT( find(m_VideoSendList.begin(), m_VideoSendList.end(), pCmd->senderId) == m_VideoSendList.end());
		// ��������б�Ϊ��, ����ͼ��(���ǵ�һ���������ǵ��û�)
		if( this->m_VideoSendList.empty() )
		{
			this->StartVideoSend(pCmd->receiverId);
		}
		// ���ӵ������б�
		this->m_VideoSendList.push_back(pCmd->senderId);
	}else{
		map<USERID, list<USERID>* >::iterator mapit = m_VideoSendListMap.find(pCmd->receiverId);
		list<USERID>* tempList;
		if(mapit == m_VideoSendListMap.end()){
			tempList = new list<USERID>;
			m_VideoSendListMap.insert(map<USERID, list<USERID>* >::value_type(pCmd->receiverId, tempList));
		}else{
			tempList = mapit->second;
		}
		_ASSERT( find(tempList->begin(), tempList->end(), pCmd->senderId) == tempList->end());
		if( tempList->empty() )
		{
			this->StartVideoSend(pCmd->receiverId);
		}
		tempList->push_back(pCmd->senderId);		
	}
}

void AVManager::RejectVideo(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::RejectVideo* pCmd = (LyvcMessage::RejectVideo*)pBaseMessage;
    TRACE1("%d reject video\n", pCmd->senderId);

	// Remove the user from apply list
	m_VideoApplyList.remove(pCmd->senderId);
}

void AVManager::AgreeVideo(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::AgreeVideo* pCmd = (LyvcMessage::AgreeVideo*)pBaseMessage;
	TRACE1("%d agree video\n", pCmd->videoSenderId);

	// Remove the user from apply list
	m_VideoApplyList.remove(pCmd->videoSenderId);

    // ��������û����ڽ����б���
    _ASSERT( find(m_VideoReceiveList.begin(), m_VideoReceiveList.end(), pCmd->videoSenderId) == m_VideoReceiveList.end());

    // ����ͼ��
    map<USERID, HWND>::iterator it = m_userVideoWindowMap.find(pCmd->videoSenderId);
    _ASSERTE( it != m_userVideoWindowMap.end());
    HWND hVideoWnd = it->second;
    m_userVideoWindowMap.erase(it);
	this->StartVideoRecv(pCmd->videoSenderId, hVideoWnd, pCmd->width, pCmd->height);
	//�������Ƶѹ������Ƶ
	if( pCmd->videoSenderId > 100000000000000000L )
	{
		//����
		Base64Coder decoder;
		int len = pCmd->TKLHead.length();
		UCHAR buffer[1024];
		decoder.Decode((const PBYTE)pCmd->TKLHead.c_str(), len);
		memcpy( buffer, decoder.DecodedMessage(), 1024 );
		this->m_pTransModel->setTKLHead(pCmd->videoSenderId, buffer);

	}
    // ���ӵ������б�
    this->m_VideoReceiveList.push_back(pCmd->videoSenderId);

	// ������ʾ
	m_pRoom->showVideoWindow( pCmd->videoSenderId );
}

void AVManager::StopSendVideo(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::StopSendVideo* pCmd = (LyvcMessage::StopSendVideo*)pBaseMessage;
    TRACE1("%d stop send video\n", pCmd->senderId);

    // ��������û������ǵĽ����б���
    list<USERID>::iterator it = find(m_VideoReceiveList.begin(), m_VideoReceiveList.end(), pCmd->senderId);
    _ASSERTE( it != m_VideoReceiveList.end());
    m_VideoReceiveList.erase(it);

    // ֪ͨTransModelֹͣ����
    this->EndVideoRecv(pCmd->senderId);

    // ֪ͨ����رմ���
    m_pRoom->closeVideoWindow(pCmd->senderId);
}

void AVManager::StopReceiveVideo(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::StopReceiveVideo* pCmd = (LyvcMessage::StopReceiveVideo*)pBaseMessage;
    TRACE1("%d stop receive video\n", pCmd->senderId);

	if(pCmd->receiverId == this->m_userId){
		// ��������û������ǵķ����б���
		list<USERID>::iterator it = find(m_VideoSendList.begin(), m_VideoSendList.end(), pCmd->senderId);
		_ASSERTE( it != m_VideoSendList.end());
		m_VideoSendList.erase(it);

		// ��������б�Ϊ�գ�֪ͨTransModelֹͣ������Ƶ
		if( m_VideoSendList.empty() )
		{
			this->EndVideoSend(pCmd->receiverId);
		}
	}else{
		map<USERID, list<USERID>* >::iterator mapit = m_VideoSendListMap.find(pCmd->receiverId);
		list<USERID>* tempList;
		if(mapit == m_VideoSendListMap.end()){
			tempList = new list<USERID>;
			m_VideoSendListMap.insert(map<USERID, list<USERID>* >::value_type(pCmd->receiverId, tempList));
		}else{
			tempList = mapit->second;
		}
		list<USERID>::iterator it = find(tempList->begin(), tempList->end(), pCmd->senderId);
		_ASSERTE( it != tempList->end());
		if( it != tempList->end() )
		{
			tempList->erase(it);
			this->EndVideoSend(pCmd->receiverId);
		}
	}

}

void AVManager::UserChannelBroken(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::UserChannelBroken* pCmd = (LyvcMessage::UserChannelBroken*)pBaseMessage;
    TRACE1("%d channel broken.\n", pCmd->userId);

    // ����������������Ƶ��ֹͣ����
	m_AudioApplyList.remove(pCmd->userId);

    list<USERID>::iterator it;

	// ����������������Ƶ��ֹͣ����
	m_VideoApplyList.remove(pCmd->userId);
	vector<__int64> confUserIds;
	ConferenceUserMgr::getVirtualConferenceUserIds(pCmd->userId,4, &confUserIds);
	for(int i = 0;i < confUserIds.size();i++){
		it = find(m_VideoApplyList.begin(), m_VideoApplyList.end(), confUserIds.at(i));
		if( it != m_VideoApplyList.end())
			m_VideoApplyList.erase(it);
	}

    // ������ڽ��մ�����Ƶ,ֹͣ����
    it = find(m_AudioReceiveList.begin(), m_AudioReceiveList.end(), pCmd->userId);
    if( it != m_AudioReceiveList.end())
    {
        m_AudioReceiveList.erase(it);
        this->EndAudioRecv(pCmd->userId);
    }
    
    // ������ڷ�����Ƶ������,�����˴��б���ȥ��,����������һ����, ֹͣ��Ƶ����
    it = find(m_AudioSendList.begin(), m_AudioSendList.end(), pCmd->userId);
    if( it != m_AudioSendList.end())
    {
        m_AudioSendList.erase(it);
        if( m_AudioSendList.empty() )
        {
            this->EndAudioSend();
        }
    }

    // ������ڽ��մ�����Ƶ,ֹͣ����
    it = find(m_VideoReceiveList.begin(), m_VideoReceiveList.end(), pCmd->userId);
    if( it != m_VideoReceiveList.end())
    {
        m_VideoReceiveList.erase(it);
        this->EndVideoRecv(pCmd->userId);
    }
    
	for(int i = 0;i < confUserIds.size();i++){
		__int64 tempId = confUserIds.at(i);
		it = find(m_VideoReceiveList.begin(), m_VideoReceiveList.end(), tempId);
		if( it != m_VideoReceiveList.end())
		{
			m_VideoReceiveList.erase(it);
			this->EndVideoRecv(tempId);
		}
	}

	// ������ڷ�����Ƶ������,�����˴��б���ȥ��,����������һ����, ֹͣ��Ƶ����
    it = find(m_VideoSendList.begin(), m_VideoSendList.end(), pCmd->userId);
    if( it != m_VideoSendList.end())
    {
        m_VideoSendList.erase(it);
        if( m_VideoSendList.empty() )
        {
            this->EndVideoSend(pCmd->userId);
        }
    }
	ConferenceUserMgr::getVirtualConferenceUserIds(m_userId, 4, &confUserIds);
	for(int i = 0;i < confUserIds.size();i++){
		map<USERID, list<USERID>* >::iterator mapit = m_VideoSendListMap.find(confUserIds.at(i));
		list<USERID>* tempList;
		if(mapit == m_VideoSendListMap.end()){
			tempList = new list<USERID>;
			m_VideoSendListMap.insert(map<USERID, list<USERID>* >::value_type(confUserIds.at(i), tempList));
		}else{
			tempList = mapit->second;
		}
		it = find(tempList->begin(), tempList->end(), pCmd->userId);
		if( it != tempList->end() )
		{
			tempList->erase(it);
			this->EndVideoSend(confUserIds.at(i));
		}
	}
}

void AVManager::UserQuitConference(LyvcMessage::BaseMessage* pBaseMessage)
{
    LyvcMessage::UserQuitConference* pCmd = (LyvcMessage::UserQuitConference*)pBaseMessage;
    // ����������������Ƶ��ֹͣ����
	m_AudioApplyList.remove(pCmd->userId);

    // ����������������Ƶ��ֹͣ����
	m_VideoApplyList.remove(pCmd->userId);
    list<USERID>::iterator it;
	vector<__int64> confUserIds;
	ConferenceUserMgr::getVirtualConferenceUserIds(pCmd->userId,4, &confUserIds);
	for(int i = 0;i < confUserIds.size();i++){
		it = find(m_VideoApplyList.begin(), m_VideoApplyList.end(), confUserIds.at(i));
		if( it != m_VideoApplyList.end())
			m_VideoApplyList.erase(it);
	}
}

void AVManager::cmdApplyAudio(USERID userId)
{
	list<USERID>::iterator it = find(m_AudioApplyList.begin(), m_AudioApplyList.end(), userId);
	if( it != m_AudioApplyList.end() )
	{
		return;
	}
	m_AudioApplyList.push_back(userId);

    LyvcMessage::ApplyAudio msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = this->m_userId;
    msg.receiverId = userId;
    this->m_pMatrixC->sendMessage(&msg);
}

void AVManager::cmdAgreeAudio(USERID userId)
{
    LyvcMessage::AgreeAudio msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = this->m_userId;
    msg.receiverId = userId;
    this->m_pMatrixC->sendMessage(&msg);
}

void AVManager::cmdRejectAudio(USERID userId)
{
    LyvcMessage::RejectAudio msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = this->m_userId;
    msg.receiverId = userId;
    this->m_pMatrixC->sendMessage(&msg);
}

void AVManager::cmdStopReceiveAudio(USERID userId)
{
    LyvcMessage::StopReceiveAudio msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = this->m_userId;
    msg.receiverId = userId;
    this->m_pMatrixC->sendMessage(&msg);
}

void AVManager::cmdStopSendAudio(USERID userId)
{
    LyvcMessage::StopSendAudio msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = this->m_userId;
    msg.receiverId = userId;
    this->m_pMatrixC->sendMessage(&msg);
}

void AVManager::cmdApplyVideo(USERID userId)
{
	list<USERID>::iterator it = find(m_VideoApplyList.begin(), m_VideoApplyList.end(), userId);
	if( it != m_VideoApplyList.end() )
	{
		return;
	}
	m_VideoApplyList.push_back(userId);

    LyvcMessage::ApplyVideo msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = this->m_userId;
    msg.receiverId = userId;
    this->m_pMatrixC->sendMessage(&msg);
}

void AVManager::cmdAgreeVideo(USERID userId, USERID videoSenderId)
{
    LyvcMessage::AgreeVideo msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = this->m_userId;
    msg.receiverId = userId;
	msg.videoSenderId = videoSenderId;
	msg.width = VideoConfig::getWidth();
	msg.height = VideoConfig::getHeight();
	msg.TKLHead = ""; 
	//������������Ƶѹ������Ƶ������ͷ����
	if( videoSenderId > 100000000000000000L )
	{
		if( ConferenceUserMgr::getRealIdByVirtualId(videoSenderId) == this->m_userId )
		{
			LONG handle = ConferenceUserMgr::getVirtualConferenceUserChannel(videoSenderId);
			UCHAR* pHead = GetApp()->getCooperationManager()->getTKLHead(handle);
			//����
			Base64Coder encoder;
			encoder.Encode( (const PBYTE)pHead, 1024);
			msg.TKLHead = encoder.EncodedMessage();
		}
	}
    this->m_pMatrixC->sendMessage(&msg);
}

void AVManager::cmdRejectVideo(USERID userId)
{
    LyvcMessage::RejectVideo msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = this->m_userId;
    msg.receiverId = userId;
    this->m_pMatrixC->sendMessage(&msg);
}

void AVManager::cmdStopReceiveVideo(USERID userId)
{
    LyvcMessage::StopReceiveVideo msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = this->m_userId;
    msg.receiverId = userId;
    this->m_pMatrixC->sendMessage(&msg);
}

void AVManager::cmdStopSendVideo(USERID videoSenderId, USERID receiverId)
{
    LyvcMessage::StopSendVideo msg;
    msg.conferenceId = this->m_conferenceId;
    msg.senderId = videoSenderId;
    msg.receiverId = receiverId;
    this->m_pMatrixC->sendMessage(&msg);
}

