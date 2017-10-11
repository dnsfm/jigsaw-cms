// -=- CViewManager.h

// Creates and manages CView instances.

#ifndef __RFB_WIN32_CVIEW_MANAGER_H__
#define __RFB_WIN32_CVIEW_MANAGER_H__
#include <string>
#include <list>
#include "rfb_win32/MsgWindow.h"
#include "ClientNotifier.h"

namespace rfb {

	namespace win32 {

		class CView;

		class CViewManager : public MsgWindow 
		{
		public:
			CViewManager();
			~CViewManager();

			void remNotifier(__int64 uid);
			void addNotifier(__int64 uid, ClientNotifier* pNotifier);
			//��ӿͻ���
			CView* addClient(__int64 uid, std::string name);
			//ɾ���ͻ���
			void remClient(__int64 uid = 0);
			CView* getView(__int64 uid);

			__int64 getTopDesktopClientId();

		protected:
			LRESULT processMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	
		private:
			//�ͻ���ָ��
			std::list<CView*> m_viewList;

	    public:
			// ÿ��view�ر�ʱҪ֪ͨ�Ķ���
		    map<__int64, list<ClientNotifier*> > m_notifierMap;
		};

	};

};

#endif
