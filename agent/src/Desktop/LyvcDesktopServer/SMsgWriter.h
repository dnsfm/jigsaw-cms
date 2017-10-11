#pragma once
#include "rfb/types.h"
#include "rfb/Rect.h"
#include "rfb/ConnParams.h"
#include "rfb/UpdateTracker.h"
#include "rfb/msgTypes.h"
#include "rfb/ZRLEEncoder.h"

namespace rdr { class OutStream; }

class SMsgWriter
{
public:
	//���캯��
	SMsgWriter();
	~SMsgWriter(void);

public:
	void setOutStream(rdr::OutStream* os) { m_os = os; };
	rdr::OutStream* getOutStream() { return m_os; };
	void startRect(const rfb::Rect& r) ;
	void endRect() ;
	void startMsg(int type);
	void endMsg();

	//����һЩ��ʼ����Ϣ
	void writeServerInit(rfb::ColourMap* cm=0);
	//���ͱ仯�˵ľ�������
	void writeRects(const rfb::UpdateInfo& ui, rfb::ImageGetter* ig, rfb::Region* updatedRegion);
	//�������
	void writeCursor(const rfb::Rect& r, const rfb::Point& pt, rfb::ImageGetter* ig);

	//ΪҪ���͵����������ڴ�ռ�
    rdr::U8* getImageBuf(int required);

public:
	//�ͻ��˺ͷ���˵�һЩ���Ӳ���
	rfb::ConnParams* m_cp;

private:
	void writeSetColorMapEntries(int firstColour, int nColours, rfb::ColourMap* cm);
	//����������Ϣ
	void writeCopyRect(const rfb::Rect& r, int srcX, int srcY);
	//ʵ�ʷ��ͱ仯���εķ���
	void writeRect(const rfb::Rect& r, rfb::ImageGetter* ig);//const char* data, int uncomprLen, int comprLen);

private:
	// zrle encoder
	rfb::ZRLEEncoder* m_encoder;
	// ���
	rdr::OutStream* m_os;
	//�������ݻ�����
    rdr::U8* m_imageBuf;
	//��������С
    int m_imageBufSize;

};
