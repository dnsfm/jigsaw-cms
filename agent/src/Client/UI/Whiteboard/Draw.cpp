#include "stdafx.h"
#include "resource.h"       // main symbols

#include "Draw.h"
#include "structure.h"
#include <math.h>

#define MAXOFFSET 2 // �������������ʵ��������ֵ
					// ��AtPoint��AtLine������ʹ��

//�װ���Ϣ��ʽ
/*
ͼ��							����

�ֽ�	����					�ֽ�	����
1-4		�װ���
5-8		ͼ������				5-8		IDT_TEXT
9-12	������ɫ				9-12	������ɫ
13-16	���ʿ��				
17-20	�Ƿ����(�����)		17-76	��������LOGFONT
21-N	Ҫ���������			77-80	���ֻ����������Ͻ�����
		ÿ4���ֽ�Ϊһ����		81-84	���½�����
		ǰ2���ֽڱ�ʾx			85-88	�ֽ���
		��2���ֽڱ�ʾy			89-N	��������
*/

//-----------------------------
// ����ΪCDrawObject�෽��ʵ��
//-----------------------------

CDrawObject::CDrawObject(COLORREF crColor, int nWidth, BOOL bFill, int nStyle, WhiteboardOutStream* os)
{
	m_crPenColor = crColor;
	m_nPenWidth = nWidth;
	m_bFill = bFill;
	m_nStyle = nStyle;
	m_os = os;
	if( m_os )
	{
		m_os->setPos(4);
		m_os->writeU32( nStyle );
		m_os->writeU32( crColor );
		m_os->writeU32( nWidth );
	}
}

//--------------------------------
//����ΪCDrawLine(����)�෽��ʵ��
//--------------------------------

CDrawLine::CDrawLine(COLORREF color, int width, WhiteboardOutStream* os)
	:CDrawObject(color, width, FALSE, IDT_LINE, os)
{
	m_x1=m_y1=m_x2=m_y2=0;
}

void CDrawLine::NewPoint(long x, long y)
{
	m_x1 = m_x2 = x;
	m_y1 = m_y2 = y;
	TRACE2( "x=%d, y=%d\n", x, y );
}

void CDrawLine::AddPoint(long x, long y) 
{ 
	m_x2 = x; 
	m_y2 = y; 
	TRACE2( "x=%d, y=%d\n", x, y );
}

void CDrawLine::MoveAt(CDC *pDC, long x, long y)
{
	//��������DC
	COLORREF XorColor = pDC->GetBkColor() ^ GetPenColor();
	CPen pen(PS_SOLID, GetPenWidth(), XorColor), *oldpen;
	int oldmode = pDC->GetROP2();
	oldpen = pDC->SelectObject(&pen);
	pDC->SetROP2(R2_XORPEN);
	//�����ƶ�ֱ��
	pDC->MoveTo(m_x1, m_y1);
	pDC->LineTo(m_x2, m_y2);//ɾ��ԭͼ��

	m_x2 = x;
	m_y2 = y;

	pDC->MoveTo(m_x1, m_y1);
	pDC->LineTo(m_x2, m_y2);//����ͼ��

	//���»ָ�DC
	pDC->SelectObject(oldpen);
	pen.DeleteObject();//�ͷű���Դ
}

void CDrawLine::Draw(CDC* pDC)
{
	//��������DC
	CPen pen(PS_SOLID, GetPenWidth(), GetPenColor()), *oldpen;
	oldpen = pDC->SelectObject(&pen);
	//�����ƶ�ֱ��
	pDC->MoveTo(m_x1, m_y1);
	pDC->LineTo(m_x2, m_y2);

	//���»ָ�DC
	pDC->SelectObject(oldpen);
	pen.DeleteObject();//�ͷű���Դ
}

void CDrawLine::SendDraw()
{
	if( m_os )
	{
		m_os->pad(4);
		m_os->writeU16( m_x1 );
		m_os->writeU16( m_y1 );
		m_os->writeU16( m_x2 );
		m_os->writeU16( m_y2 );
		m_os->flush();
	}
}

//--------------------------------
//����ΪCDrawCurve(����)�෽��ʵ��
//--------------------------------

CDrawCurve::CDrawCurve(COLORREF color, int width, WhiteboardOutStream* os)
	:CDrawObject(color, width, FALSE, IDT_CURVE, os)
{
	m_nPointNumber = 0;
}

void CDrawCurve::NewPoint(long x, long y)
{
	m_points[0].x = x;
	m_points[0].y = y;
	m_nPointNumber = 1;
}

void CDrawCurve::AddPoint(long x, long y)
{ 
	m_points[m_nPointNumber].x = x;
	m_points[m_nPointNumber].y = y;
	m_nPointNumber++;
}

void CDrawCurve::MoveAt(CDC *pDC, long x, long y)
{
	//��������DC
	CPen pen(PS_DOT, GetPenWidth(), GetPenColor()), *oldpen;
	oldpen = pDC->SelectObject(&pen);

	pDC->MoveTo( m_points[m_nPointNumber-1].x, m_points[m_nPointNumber-1].y );
	pDC->LineTo(x, y);

	//���»ָ�DC
	pDC->SelectObject(oldpen);
	pen.DeleteObject();//�ͷű���Դ

	m_points[m_nPointNumber].x = x;
	m_points[m_nPointNumber].y = y;
	m_nPointNumber++;
}

void CDrawCurve::Draw(CDC* pDC)
{
	//��������DC
	CPen pen(PS_DOT, GetPenWidth(), GetPenColor()), *oldpen;
	oldpen = pDC->SelectObject(&pen);

    for( int i = 0; i < m_nPointNumber - 1; i++ )
	{
		pDC->MoveTo(m_points[i].x, m_points[i].y);
		pDC->LineTo(m_points[i+1].x, m_points[i+1].y);
	}
	//���»ָ�DC
	pDC->SelectObject(oldpen);
	pen.DeleteObject();//�ͷű���Դ

	m_points[0] = m_points[m_nPointNumber-1];
	m_nPointNumber = 1;
}

void CDrawCurve::SendDraw()
{
	if( m_os )
	{
		m_os->setPos(4);
		m_os->writeU32( IDT_CURVE );
		m_os->writeU32( GetPenColor() );
		m_os->writeU32( GetPenWidth() );
		m_os->writeU32( m_nPointNumber );
		for( int i = 0; i < m_nPointNumber; i++ )
		{
			m_os->writeU16( m_points[i].x );
			m_os->writeU16( m_points[i].y );
		}
		m_os->flush();
		TRACE0( "send curve\n" );
	}
}

int CDrawCurve::getPointNumber()
{
    return m_nPointNumber;
}

//-----------------------------------
// ����ΪCDrawRect(�����)�෽��ʵ��
//-----------------------------------

CDrawRect::CDrawRect(COLORREF color, int width, BOOL bFill, WhiteboardOutStream* os)
	:CDrawObject(color, width, bFill, IDT_RECTANGLE, os)
{
	m_x1=m_y1=m_x2=m_y2=0;
}

void CDrawRect::Draw(CDC* pDC)
{
	CPen pen(PS_SOLID, GetPenWidth(), GetPenColor());
	int oldmode = pDC->GetROP2();

	CPen* oldpen = pDC->SelectObject(&pen);
	CBrush* oldbrush;
	CBrush  brush(GetPenColor());

	if( GetFill() )	
		oldbrush = (CBrush*)pDC->SelectObject(&brush);
	else
		oldbrush=(CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	pDC->Rectangle(m_x1, m_y1, m_x2, m_y2);


	//���»ָ�DC
	pDC->SetROP2(oldmode);
	pDC->SelectObject(oldpen);
	pDC->SelectObject(&oldbrush);
	pen.DeleteObject();
}

void CDrawRect::SendDraw()
{
	if( m_os )
	{
		m_os->writeU32( GetFill() );
		m_os->writeU16( m_x1 );
		m_os->writeU16( m_y1 );
		m_os->writeU16( m_x2 );
		m_os->writeU16( m_y2 );
		m_os->flush();
	}
}


void CDrawRect::NewPoint(long x, long y)
{
	m_x1 = m_x2 = x;
	m_y1 = m_y2 = y;
}

void CDrawRect::AddPoint(long x, long y)
{
	m_x2 = x;
	m_y2 = y;
};

void CDrawRect::MoveAt(CDC *pDC, long x, long y)
{
	if( !GetFill() )
	{
		COLORREF XorColor = pDC->GetBkColor() ^ GetPenColor();
		CPen pen(PS_SOLID, GetPenWidth(), XorColor);
		int oldmode = pDC->GetROP2();

		CPen* oldpen = pDC->SelectObject(&pen);
		//����Ϊ���ա�ˢ���Ȳ���䡣
		CBrush* oldbrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		pDC->SetROP2(R2_XORPEN);

		//ɾ��ԭͼ��
		pDC->Rectangle(m_x1, m_y1, m_x2, m_y2);

		//�޸���ͼ������
		m_x2 = x;
		m_y2 = y;

		//����ͼ��
		pDC->Rectangle(m_x1, m_y1, m_x2, m_y2);

		//���»ָ�DC
		pDC->SetROP2(oldmode);
		pDC->SelectObject(oldpen);
		pen.DeleteObject();
	}
	else
	{
		COLORREF XorColor = pDC->GetBkColor() ^ GetPenColor();
		CPen pen(PS_SOLID, GetPenWidth(), XorColor);
		int oldmode = pDC->GetROP2();

		CPen* oldpen = pDC->SelectObject(&pen);
		//����ˢ��䡣
		CBrush  brush(XorColor);
		CBrush* oldbrush = (CBrush*)pDC->SelectObject(brush);

		pDC->SetROP2(R2_XORPEN);

		//ɾ��ԭͼ��
		pDC->Rectangle(m_x1, m_y1, m_x2, m_y2);

		//�޸���ͼ������
		m_x2 = x;
		m_y2 = y;

		//����ͼ��
		pDC->Rectangle(m_x1, m_y1, m_x2, m_y2);

		//���»ָ�DC
		pDC->SetROP2(oldmode);
		pDC->SelectObject(oldpen);
		pDC->SelectObject(&oldbrush);
		pen.DeleteObject();
	}
}

//-------------------------------------
// ����ΪCDrawEllipse(����Բ)�෽��ʵ��
//-------------------------------------

CDrawEllipse::CDrawEllipse(COLORREF color, int width, BOOL bFill, WhiteboardOutStream* os)
	:CDrawObject(color, width, bFill, IDT_ELLIPSE, os)
{
	m_x1=m_y1=m_x2=m_y2=0;
}

void CDrawEllipse::NewPoint(long x, long y)
{
	m_x1 = m_x2 = x;
	m_y1 = m_y2 = y;
}

void CDrawEllipse::MoveAt(CDC *pDC, long x, long y)
{
	if( !GetFill() )
	{
		COLORREF XorColor = pDC->GetBkColor() ^ GetPenColor();
		CPen pen(PS_SOLID, GetPenWidth(), XorColor);
		int oldmode = pDC->GetROP2();

		CPen* oldpen = pDC->SelectObject(&pen);
		//����Ϊ���ա�ˢ���Ȳ���䡣
		CBrush* oldbrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	
		pDC->SetROP2(R2_XORPEN);

		//ɾ��ԭͼ��
		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

		//�޸���ͼ������
		m_x2 = x;
		m_y2 = y;

		//����ͼ��
		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

		//���»ָ�DC
		pDC->SetROP2(oldmode);
		pDC->SelectObject(oldpen);
		pen.DeleteObject();
	}
	else
	{
		COLORREF XorColor = pDC->GetBkColor() ^ GetPenColor();
		CPen pen(PS_SOLID, GetPenWidth(), XorColor);
		int oldmode = pDC->GetROP2();

		CPen* oldpen = pDC->SelectObject(&pen);
		//����ˢ��䡣
		CBrush  brush(XorColor);
		CBrush* oldbrush = (CBrush*)pDC->SelectObject(brush);
		pDC->SetROP2(R2_XORPEN);

		//ɾ��ԭͼ��
		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

		//�޸���ͼ������

		m_x2 = x;
		m_y2 = y;

		//����ͼ��
		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

		//���»ָ�DC
		pDC->SetROP2(oldmode);
		pDC->SelectObject(oldpen);
		pDC->SelectObject(&oldbrush);
		pen.DeleteObject();
	}
}

void CDrawEllipse::Draw(CDC* pDC)
{
	CPen pen(PS_SOLID, GetPenWidth(), GetPenColor());
	int oldmode = pDC->GetROP2();

	CPen* oldpen = pDC->SelectObject(&pen);
	CBrush* oldbrush;
	CBrush  brush(GetPenColor());
	if( GetFill() )	
		oldbrush = (CBrush*)pDC->SelectObject(&brush);
	else
		oldbrush=(CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

	//���»ָ�DC
	pDC->SetROP2(oldmode);
	pDC->SelectObject(oldpen);
	pDC->SelectObject(&oldbrush);
	pen.DeleteObject();
}

void CDrawEllipse::SendDraw()
{
	if( m_os )
	{
		m_os->writeU32( GetFill() );
		m_os->writeU16( m_x1 );
		m_os->writeU16( m_y1 );
		m_os->writeU16( m_x2 );
		m_os->writeU16( m_y2 );
		m_os->flush();
	}
}

//-----------------------------------
// ����ΪCDrawCircle(��Բ)�෽��ʵ��
//-----------------------------------

CDrawCircle::CDrawCircle(COLORREF color, int width, BOOL bFill, WhiteboardOutStream* os)
	:CDrawObject(color, width, bFill, IDT_CIRCLE, os)
{
	m_x1=m_y1=m_x2=m_y2=0;
}

void CDrawCircle::NewPoint(long x, long y)
{
	m_x1 = m_x2 = x;
	m_y1 = m_y2 = y;
}

void CDrawCircle::MoveAt(CDC *pDC, long x, long y)
{
	if( !GetFill() )
	{
		COLORREF XorColor = pDC->GetBkColor() ^ GetPenColor();
		CPen pen(PS_SOLID, GetPenWidth(), XorColor);
		int oldmode = pDC->GetROP2();

		CPen* oldpen = pDC->SelectObject(&pen);
		//����Ϊ���ա�ˢ���Ȳ���䡣
		CBrush* oldbrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	
		pDC->SetROP2(R2_XORPEN);

		//ɾ��ԭͼ��
		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

		//�޸���ͼ������
		long min = min(abs(x - m_x1), abs(y - m_y1));
		if( x < m_x1 )
			m_x2 = m_x1 - min;
		else
			m_x2 = m_x1 + min;
		if( y < m_y1 )
			m_y2 = m_y1 - min;
		else
			m_y2 = m_y1 + min;

		//����ͼ��
		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

		//���»ָ�DC
		pDC->SetROP2(oldmode);
		pDC->SelectObject(oldpen);
		pen.DeleteObject();
	}
	else
	{
		COLORREF XorColor = pDC->GetBkColor() ^ GetPenColor();
		CPen pen(PS_SOLID, GetPenWidth(), XorColor);
		int oldmode = pDC->GetROP2();

		CPen* oldpen = pDC->SelectObject(&pen);
		//����ˢ��䡣
		CBrush  brush(XorColor);
		CBrush* oldbrush = (CBrush*)pDC->SelectObject(brush);


		pDC->SetROP2(R2_XORPEN);

		//ɾ��ԭͼ��
		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

		//�޸���ͼ������
		long min = min(abs(x - m_x1), abs(y - m_y1));
		if( x < m_x1 )
			m_x2 = m_x1 - min;
		else
			m_x2 = m_x1 + min;
		if( y < m_y1 )
			m_y2 = m_y1 - min;
		else
			m_y2 = m_y1 + min;

		//����ͼ��
		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

		//���»ָ�DC
		pDC->SetROP2(oldmode);
		pDC->SelectObject(oldpen);
		pDC->SelectObject(&oldbrush);
		pen.DeleteObject();
	}
}

void CDrawCircle::Draw(CDC* pDC)
{
	CPen pen(PS_SOLID, GetPenWidth(), GetPenColor());
	int oldmode = pDC->GetROP2();

	CPen* oldpen = pDC->SelectObject(&pen);
	CBrush* oldbrush;
	CBrush  brush(GetPenColor());
	if( GetFill() )	
		oldbrush = (CBrush*)pDC->SelectObject(&brush);
	else
		oldbrush=(CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	if( GetFill() )
		oldbrush = (CBrush*)pDC->SelectObject(&brush);
	pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

	//���»ָ�DC
	pDC->SetROP2(oldmode);
	pDC->SelectObject(oldpen);
	pDC->SelectObject(&oldbrush);
	pen.DeleteObject();
}

void CDrawCircle::SendDraw()
{
	if( m_os )
	{
		m_os->writeU32( GetFill() );
		m_os->writeU16( m_x1 );
		m_os->writeU16( m_y1 );
		m_os->writeU16( m_x2 );
		m_os->writeU16( m_y2 );
		m_os->flush();
	}
}

//-----------------------------------
// ����ΪCDrawPoly(�����)�෽��ʵ��
//-----------------------------------

CDrawPoly::CDrawPoly(COLORREF color, int width, WhiteboardOutStream* os)
	:CDrawObject(color, width, FALSE, IDT_POLY, os)
{
	m_nPointNumber = 0;
}

void CDrawPoly::NewPoint(long x, long y)
{
	m_nPointNumber = 1;
	m_points[0].x = x;
	m_points[0].y = y;
	m_oldx = x;
	m_oldy = y;
}

void CDrawPoly::AddPoint(long x, long y)
{
	if(m_nPointNumber < MAXPLINEPOINT)
	{
		m_points[m_nPointNumber].x = x;
		m_points[m_nPointNumber].y = y;
		m_oldx = x;
		m_oldy = y;
		m_nPointNumber++;
	}
}

void CDrawPoly::MoveAt(CDC *pDC, long x, long y)
{
	if( m_nPointNumber == MAXPLINEPOINT )
		return;
	//��������DC
	COLORREF XorColor = pDC->GetBkColor() ^ GetPenColor();
	CPen pen(PS_SOLID, GetPenWidth(), XorColor);
	int oldmode = pDC->GetROP2();
	CPen* oldpen = pDC->SelectObject(&pen);
	//����Ϊ���ա�ˢ���Ȳ���䡣
	CBrush* oldbrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetROP2(R2_XORPEN);

	//�޸���ͼ������
	pDC->MoveTo(m_points[m_nPointNumber-1].x, m_points[m_nPointNumber-1].y);
	pDC->LineTo(m_oldx, m_oldy);
	m_oldx = x;
	m_oldy = y;
	pDC->MoveTo(m_points[m_nPointNumber-1].x, m_points[m_nPointNumber-1].y);
	pDC->LineTo(m_oldx, m_oldy);

	//���»ָ�DC
	pDC->SetROP2(oldmode);
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	pen.DeleteObject();
}

void CDrawPoly::EndPoint(CDC* pDC)
{
	CPen pen(PS_SOLID, GetPenWidth(), GetPenColor());
	CPen* oldpen = pDC->SelectObject(&pen);
	pDC->MoveTo(m_points[m_nPointNumber-1].x, m_points[m_nPointNumber-1].y);
	pDC->LineTo(m_points[0].x, m_points[0].y);
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
}

void CDrawPoly::Draw(CDC* pDC)
{
	//��������DC
	CPen pen(PS_SOLID, GetPenWidth(), GetPenColor()), *oldpen;
	oldpen = pDC->SelectObject(&pen);

    for( int i = 0; i < m_nPointNumber - 1; i++ )
	{
		pDC->MoveTo(m_points[i].x, m_points[i].y);
		pDC->LineTo(m_points[i+1].x, m_points[i+1].y);
	}
	if( m_nPointNumber > 2 )
	{
		pDC->MoveTo(m_points[m_nPointNumber-1].x, m_points[m_nPointNumber-1].y);
		pDC->LineTo(m_points[0].x, m_points[0].y);
	}
	//���»ָ�DC
	pDC->SelectObject(oldpen);
	pen.DeleteObject();//�ͷű���Դ
}

void CDrawPoly::SendDraw()
{
	if( m_os )
	{
		m_os->writeU32(m_nPointNumber);
		for( int i = 0; i < m_nPointNumber; i++ )
		{
			m_os->writeU16( m_points[i].x );
			m_os->writeU16( m_points[i].y );
		}
		m_os->flush();
	}
}

//-----------------------------------
// ����ΪCDrawText�෽��ʵ��
//-----------------------------------

CDrawText::CDrawText(LOGFONT lf, CString str, COLORREF color, WhiteboardOutStream* os)
	:CDrawObject(color, 1, FALSE, IDT_TEXT, os)
{
    m_sText = str;
	m_lf = lf;
}

void CDrawText::Draw(CDC* pDC)
{
	CFont font;
	font.CreateFontIndirect( &m_lf );
	CFont* pOldFont = pDC->SelectObject( &font );
	COLORREF crOldColor = pDC->SetTextColor( this->GetPenColor() );
	int nOldBkMode = pDC->SetBkMode( OPAQUE );
	COLORREF crOldBkColor = pDC->SetBkColor( RGB(255, 255, 255) );
	pDC->DrawText( m_sText, CRect( m_x1, m_y1, m_x2, m_y2 ), DT_LEFT|DT_WORDBREAK );
	pDC->SelectObject( pOldFont );
	pDC->SetTextColor( crOldColor );
	pDC->SetBkMode( nOldBkMode );
	pDC->SetBkColor( crOldBkColor );
	font.DeleteObject();
}

void CDrawText::SendDraw()
{
	if( m_os )
	{
		m_os->writeBytes( &m_lf, sizeof(LOGFONT) );
		m_os->writeU16( m_x1 );
		m_os->writeU16( m_y1 );
		m_os->writeU16( m_x2 );
		m_os->writeU16( m_y2 );
		m_os->writeString( m_sText );
		m_os->flush();
	}
}
