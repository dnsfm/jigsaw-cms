#pragma once

class CTabItem
{
public:
	CTabItem( CWnd* pWnd )
	{
		m_pWnd = pWnd;
		m_nIndex = -1;
	};
	// ��������
	enum Type{ VideoBg = -2, WhiteboardDlg, ChatDlg };
	int		m_nType;
	// ����ָ��
	CWnd*	m_pWnd;
	// �û�id������Ϊchatdlg��ʱ��Ϊ����Է���id����������ʱΪ����id
	__int64 m_ChatWithId;
	// ��ǩҳ���
	int		m_nIndex;
};