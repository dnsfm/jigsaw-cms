#pragma once

class SMsgHandler
{
public:
	//�ͻ��˴��������ͼ����¼��Ĵ���ʵ��������LyvcDesktopServer��ʵ��
	virtual void setMouse(int mask, int x, int y) = 0;
	virtual void setKey(bool downFlag, int key) = 0;

	//�пͻ�������
	virtual void requestUpdate() = 0;
};
