#pragma once

//���湲��ͻ��˵���������ݰ��ı�־
const int DESKTOP_KEYBOARD           = 1; // ��������
const int DESKTOP_MOUSE              = 2; // �������

struct DESKTOP_CONTROL_PACKET
{
	BYTE			flag;          // ���ݰ�����
	//��������
	bool			downFlag;	   
	unsigned int	key;
	//�������
	BYTE			buttonMask;
	unsigned short	x;
	unsigned short	y;
};
