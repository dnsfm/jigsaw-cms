#pragma once

// TCP���ݰ������ݴ�С����
#define MAX_TCP_SIZE 512*1024

//���ݰ��ı�־
const int FVS_TCP_USER    = 1; // ��ǰ���ӵ��û�ID
const int FVS_TCP_FILE    = 2; // �ļ�����
const int FVS_TCP_DESKTOP = 3; // �����������
const int FVS_TCP_WHITEBOARD = 4; // �װ�����

//���ݰ�
struct PACK_TCP
{
	BYTE	flag;          // ���ݰ�����
	__int64 userId;        // �û��Լ���id
//	__int64 confId;		   // ����id
	DWORD   data_size;     // ������ʵ�����ݴ�С
};

