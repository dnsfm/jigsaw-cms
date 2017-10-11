#pragma once

#include "rfb\VNCServer.h"
#include "DesktopServer.h"
#include "SMsgHandler.h"
#include "rfb\SDesktop.h"
#include "rfb\Cursor.h"
#include "rfb\TransImageGetter.h"

namespace rfb
{
	class ComparingUpdateTracker;
	class PixelBuffer;
}

namespace LyvcMessage
{
	class MatrixC;
}

class SMsgWriter;
class SMsgHandler;
class SMsgReader;
class LyvcOutStream;

class LyvcDesktopServer : rfb::VNCServer, 
						public DesktopServer,
						public SMsgHandler
{
//���죬��������
public:
	LyvcDesktopServer();
	~LyvcDesktopServer();

//
//��DesktopServer�̳У�����Ľӿ�
//
public:
	//��ʼ
	virtual void start(
		LyvcMessage::MatrixC* pMatrixC,       // ��Ϣϵͳ
		DESKTOPSERVER_CALLBACK pCallback,     // Callback function
		void* pCallbackParameter);            // Callback parameter
	//����
	virtual void stop();
	virtual void reInitialize();
//
//��VNCServer�̳�
//
public:
	virtual void setPixelBuffer(rfb::PixelBuffer* pb_);
	virtual void setColourMapEntries(int firstColour=0, int nColours=0);
	virtual void serverCutText(const char* str, int len) {};
	virtual void bell() {};
	virtual bool clientsReadyForUpdate() { return true; };
	virtual void closeClients(const char* reason) {};
    virtual void tryUpdate() ;
    virtual void setCursor(int width, int height, int hotspotX, int hotspotY,
                           void* cursorData, void* mask) ;
    virtual void setCursorPos(int x, int y) ;
	virtual void setName(const char* name) {};

//
//��UpdateTracker�̳�
//
public:
	virtual void add_changed(const rfb::Region &region);
    virtual void add_copied(const rfb::Region &dest, const rfb::Point &delta);

//
//��SMsgHandler�̳�
//
	virtual void setMouse(int mask, int x, int y);
	virtual void setKey(bool downFlag, int key);
	virtual void requestUpdate() { restart(); };

//
//LyvcDesktopServer��˽�г�Ա
//
private:
	//���·��ͳ�ʼ����Ϣ��������Ļ
	void restart();
	//��ʼ����Ļ��׽�������Ϣ�շ�����
	void init(LyvcMessage::MatrixC* pMatrixC, DESKTOPSERVER_CALLBACK pCallback, void* pCallbackParameter);

	rfb::Point cursorTL() { return cursorPos.subtract(cursor.hotspot); }
    bool needRenderedCursor();
	//��ȡ��Ļ�������������
    void checkUpdate();
	void writeCursor();

private:
	rfb::SDesktop* desktop;	//��Ļ��׽
    bool m_bInitialized;	//��ʼ����־
	rfb::PixelBuffer* pb;	//�洢��Ļ����
	rfb::ComparingUpdateTracker* comparer;//�Ƚϸ�������
	rfb::SimpleUpdateTracker updates;	//��������
	rfb::Rect renderedCursorRect;		//�������
	rfb::Point cursorPos;				//���λ��
    rfb::Cursor cursor;					//���
    rfb::Point renderedCursorTL;		//���λ��
    rfb::ManagedPixelBuffer renderedCursor;//�������
	rfb::Point pointerEventPos;				//����¼�λ��
    time_t lastEventTime;
    time_t pointerEventTime;
    std::set<rdr::U32> pressedKeys;		//���̰���

    bool renderedCursorInvalid;
	bool removeRenderedCursor;
	bool drawRenderedCursor;;

	bool m_bNeedSendInit;//�������ʾ���øı䣬��Ҫ���·��ͳ�ʼ����Ϣ��־
	bool m_bStarted;
	bool m_bSendingUpdate;

private:
	//������Ϣ����ָ��
	SMsgWriter* m_pMsgWriter;
	//������Ϣ����ָ��
	SMsgReader* m_pMsgReader;
	//��ͬ��ɫ����ת��
	rfb::TransImageGetter m_transImageGetter;

	LyvcOutStream* m_os;
};
