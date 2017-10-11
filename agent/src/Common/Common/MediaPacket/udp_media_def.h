#pragma once

// UDP���ݰ������ݴ�С����
#define MAX_UDP_SIZE 60000

//���ݰ��ı�־
const int	FVS_MSG_AUDIO					= 1; // �������ݰ� 
const int	FVS_MSG_VIDEO					= 2; // ͼ�����ݰ�
const int	FVS_MSG_COMPRESSION_VIDEO       = 3; // ͼ�����ݰ�
const int	FVS_MSG_ADDR					= 4; // ˢ��UDP��ַ�����ݰ�

//��Ƶ���ݰ�����������Ƶ���ݣ�
struct PACK_AUDIO
{
	BYTE	flag;
	__int64	userId;	
	DWORD	no;			//��ţ�
	WORD	data_size;
};

//��Ƶ���ݰ�����������Ƶ����,ԭ�������ݵĳ����Ǳ仯�ģ�
struct PACK_VIDEO
{
	BYTE	flag;	
	__int64	userId;	
	DWORD	no;			//���
	BYTE	format;		//��Ƶ�ĸ�ʽ
	WORD	width;
	WORD	height;
	WORD	band;		//����kb
	BYTE	frameRate;	//֡��
	BYTE	key;		//�Ƿ�ؼ�֡
	WORD	key_interval;//�ؼ�֡���
	DWORD	data_size;	//�ֽ���
};

// ��ַ���ݰ�
struct PACK_ADDR
{
	BYTE	flag;
	__int64	userId;	
};
