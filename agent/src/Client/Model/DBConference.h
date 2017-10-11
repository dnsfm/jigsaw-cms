#ifndef DBCONFERENCE_H
#define DBCONFERENCE_H

//��ӳ��������ݿ��У��ͻ�����Ҫʹ�õ�����
class DBConference {
public:    

	__int64			m_id;               //�����ID
	string			m_sName;            //��������
	string			m_sDescription;     //��������
	CTime			m_tmStartTime;      //���鿪ʼʱ��
	CTime			m_tmEndTime;        //�������ʱ��
	__int64         m_modelId;          //����ģʽID
	__int64         m_creatorId;        //���鴴����ID
	string			m_sConfFileDesc;    //������������
	string			m_sConfFileURL;     //�������ϵ�ַ

	// operator.
	BOOL operator == (const DBConference& a)
	{
		return this->m_id == a.m_id;
	}
};

#endif
