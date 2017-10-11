#include "stdafx.h"
#include "MultiAudioPlay.h"
#include "common/common/log/log.h"

MultiAudioPlay::MultiAudioPlay(__int64 userId)
{
    this->m_userId = userId;
    m_nInstanceCount = 0;
}

MultiAudioPlay::~MultiAudioPlay()
{
    // Close every process and release memory
    AudioProcessMap::iterator itProcess = m_audioProcesses.begin();
    while( itProcess != m_audioProcesses.end())
    {
        AudioProcessPlay* pAudioProcess = itProcess->second;
        pAudioProcess->destroy();
        delete pAudioProcess;

        itProcess++;
    }
}

bool MultiAudioPlay::create()
{
    return true;
}

void MultiAudioPlay::destroy()
{
}

bool MultiAudioPlay::createProcessForUser(__int64 userId)
{
	// �����Ƿ��Ѿ��н���Ϊ���û�����
	int userProcessCallCount;
	map<__int64, int>::iterator itUser = this->m_audioProcessUseCount.find(userId);
	if( itUser == this->m_audioProcessUseCount.end() )
	{
		userProcessCallCount = 1;
	}
	else
	{
		userProcessCallCount = itUser->second + 1;
		this->m_audioProcessUseCount.erase(itUser);
	}
	this->m_audioProcessUseCount.insert( map<__int64, int>::value_type(userId, userProcessCallCount));

	// ��������ô���Ϊ1����ô�����½���
	if( userProcessCallCount == 1 )
	{
		// Get a new name for the audio process
		char buffer[1024];
		sprintf(buffer, "AudioProcessPlay_%I64d_%d", this->m_userId, m_nInstanceCount);
		m_nInstanceCount ++;
	    
		// Create new audio process
		AudioProcessPlay* pAudioProcess = new AudioProcessPlay();
		if(! pAudioProcess->create(buffer))
		{
			pAudioProcess->destroy();
			delete pAudioProcess;

			itUser = this->m_audioProcessUseCount.find(userId);
			this->m_audioProcessUseCount.erase(itUser);

			return false;
		}

		// Add this audio process to map
		this->m_audioProcesses.insert( AudioProcessMap::value_type( userId, pAudioProcess));
	}

    return true;
}

bool MultiAudioPlay::destroyProcessForUser(__int64 userId)
{
    // ��֤����û��� �����б���
	int userProcessCallCount;
	map<__int64, int>::iterator itUser = this->m_audioProcessUseCount.find(userId);
	_ASSERTE(itUser != this->m_audioProcessUseCount.end());

	userProcessCallCount = itUser->second - 1;
	this->m_audioProcessUseCount.erase(itUser);
	
	if( userProcessCallCount == 0 )
	{
		AudioProcessMap::iterator it = m_audioProcesses.find(userId);
		_ASSERTE( it != m_audioProcesses.end());

		// �رս��̣��������
		AudioProcessPlay* pAudioProcess = it->second;
		pAudioProcess->destroy();
		delete pAudioProcess;
		this->m_audioProcesses.erase( userId);
	}
	else
	{
		this->m_audioProcessUseCount.insert( map<__int64, int>::value_type(userId, userProcessCallCount));
	}

    return true;
}

void MultiAudioPlay::playAudioPack(PACK_AUDIO *ppa)
{
    // �ҵ�����û���Ӧ�Ĳ��Ž���
    AudioProcessMap::iterator it = m_audioProcesses.find(ppa->userId);
    if( it == m_audioProcesses.end())
    {
        return;
    }

    // �����������
    AudioProcessPlay* pAudioProcess = it->second;
    pAudioProcess->play(ppa);
}
