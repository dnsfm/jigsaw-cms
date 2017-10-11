#pragma once

#include <string.h>
#import <msxml.dll>

class CXMLParser
{
public:
	CXMLParser(void);
	~CXMLParser(void);

	// ���ļ�װ��xml�ĵ�
	BOOL Load( LPCTSTR szFileName );
	// ����xml�ļ�
	BOOL Save( LPCTSTR szFileName );
	// ���ַ���װ��xml�ĵ�
	BOOL SetDoc( LPCTSTR szDoc );
	// ���һ���ڵ㵽���ڵ�����һ���ӽڵ��
	BOOL AddElem( LPCTSTR szName, LPCTSTR szData=NULL );
	// ���һ���ӽڵ�
	BOOL AddChildElem( LPCTSTR szName, LPCTSTR szData=NULL );
	// ����һ���ڵ㵽���ڵ�ĵ�һ���ӽڵ�ǰ
	BOOL InsertElem( LPCTSTR szName, LPCTSTR szData=NULL );
	// ����һ���ӽڵ�
	BOOL InsertChildElem( LPCTSTR szName, LPCTSTR szData=NULL );
	// ����ڵ�
	BOOL IntoElem();
	// �˳��ڵ�
	BOOL OutOfElem();
	// �������ɾ��һ����Ϣ��¼
	BOOL RemoveMsgNodeByIndex( int nIndex );
	// ɾ��������Ϣ��¼
	BOOL RemoveAllMsgNode();
	// ������ŵõ�ָ��element��ֵ
	string GetMsgElemTextByIndex( LPCTSTR szName, int nIndex );
    // �޸�xml�ļ���stylesheet����
	BOOL SetStyleSheetAttrib( LPCTSTR szValue );

private:
	BOOL addElem( LPCTSTR szName, LPCTSTR szData, BOOL bInsert, BOOL bAddChild );
	BOOL setRoot( LPCTSTR szRoot );

private:
	IXMLDOMDocument*	m_pDOMDoc;
	// ָ��ǰ�ڵ�ĸ��ڵ�
	IXMLDOMNode*		m_pParent;
	// ָ��ǰ�ڵ�
	IXMLDOMNode*		m_pMain;
	// ָ��ǰ�ڵ���ӽڵ�
	IXMLDOMNode*		m_pChild;
};
