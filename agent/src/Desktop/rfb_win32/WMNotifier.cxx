/* Copyright (C) 2002-2003 RealVNC Ltd.  All Rights Reserved.
 *    
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 */

// -=- WMNotifier.cxx
#include "stdafx.h"

#include "WMNotifier.h"
#include "WMShatter.h"
#include "MsgWindow.h"

using namespace rfb;
using namespace win32;


WMMonitor::WMMonitor() : MsgWindow(_T("WMMonitor")) {
}

WMMonitor::~WMMonitor() {
}


LRESULT
WMMonitor::processMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
  case WM_DISPLAYCHANGE:
    if (notifier) {
      notifier->notifyDisplayEvent(Notifier::DisplaySizeChanged);
      notifier->notifyDisplayEvent(Notifier::DisplayPixelFormatChanged);
    }
    break;
	case WM_SYSCOLORCHANGE:
  case WM_PALETTECHANGED:
    if (notifier) {
      notifier->notifyDisplayEvent(Notifier::DisplayColourMapChanged);
    }
    break;
  };
  return MsgWindow::processMessage(msg, wParam, lParam);
}