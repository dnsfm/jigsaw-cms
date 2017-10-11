/*

Miranda IM: the free IM client for Microsoft* Windows*

Copyright 2000-2007 Miranda ICQ/IM project,
all portions of this codebase are copyrighted to the people
listed in contributors.txt.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "commonheaders.h"
#include "clc.h"

//loads of stuff that didn't really fit anywhere else

extern HANDLE hHideInfoTipEvent;

char* fnGetGroupCountsText(struct ClcData *dat, struct ClcContact *contact)
{
	static char szName[32];
	int onlineCount, totalCount;
	struct ClcGroup *group, *topgroup;

	if (contact->type != CLCIT_GROUP || !(dat->exStyle & CLS_EX_SHOWGROUPCOUNTS))
		return "";

	group = topgroup = contact->group;
	onlineCount = 0;
	totalCount = group->totalMembers;
	group->scanIndex = 0;
	for (;;) {
		if (group->scanIndex == group->cl.count) {
			if (group == topgroup)
				break;
			group = group->parent;
		}
		else if (group->cl.items[group->scanIndex]->type == CLCIT_GROUP) {
			group = group->cl.items[group->scanIndex]->group;
			group->scanIndex = 0;
			totalCount += group->totalMembers;
			continue;
		}
		else if (group->cl.items[group->scanIndex]->type == CLCIT_CONTACT)
			if (group->cl.items[group->scanIndex]->flags & CONTACTF_ONLINE)
				onlineCount++;
		group->scanIndex++;
	}
	if (onlineCount == 0 && dat->exStyle & CLS_EX_HIDECOUNTSWHENEMPTY)
		return "";
	mir_snprintf(szName, SIZEOF(szName), "(%u/%u)", onlineCount, totalCount);
	return szName;
}

int fnHitTest(HWND hwnd, struct ClcData *dat, int testx, int testy, struct ClcContact **contact, struct ClcGroup **group, DWORD * flags)
{
	struct ClcContact *hitcontact;
	struct ClcGroup *hitgroup;
	int hit, indent, width, i;
	int checkboxWidth;
	SIZE textSize;
	HDC hdc;
	RECT clRect;
	HFONT hFont;
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);

	if ( flags )
		*flags = 0;
	
	GetClientRect(hwnd, &clRect);
	if ( testx < 0 || testy < 0 || testy >= clRect.bottom || testx >= clRect.right ) {
		if ( flags ) {
			if (testx < 0)
				*flags |= CLCHT_TOLEFT;
			else if (testx >= clRect.right)
				*flags |= CLCHT_TORIGHT;
			if (testy < 0)
				*flags |= CLCHT_ABOVE;
			else if (testy >= clRect.bottom)
				*flags |= CLCHT_BELOW;
		}
		return -1;
	}
	if (testx < dat->leftMargin) {
		if (flags)
			*flags |= CLCHT_INLEFTMARGIN | CLCHT_NOWHERE;
		return -1;
	}
	hit = cli.pfnRowHitTest(dat, dat->yScroll + testy);
	if ( hit != -1 )
		hit = cli.pfnGetRowByIndex(dat, hit, &hitcontact, &hitgroup);
	if (hit == -1) {
		if (flags)
			*flags |= CLCHT_NOWHERE | CLCHT_BELOWITEMS;
		return -1;
	}
	if (contact)
		*contact = hitcontact;
	if (group)
		*group = hitgroup;
	for (indent = 0; hitgroup->parent; indent++, hitgroup = hitgroup->parent);
	if (testx < dat->leftMargin + indent * dat->groupIndent) {
		if (flags)
			*flags |= CLCHT_ONITEMINDENT;
		return hit;
	}
	checkboxWidth = 0;
	if (style & CLS_CHECKBOXES && hitcontact->type == CLCIT_CONTACT)
		checkboxWidth = dat->checkboxSize + 2;
	if (style & CLS_GROUPCHECKBOXES && hitcontact->type == CLCIT_GROUP)
		checkboxWidth = dat->checkboxSize + 2;
	if (hitcontact->type == CLCIT_INFO && hitcontact->flags & CLCIIF_CHECKBOX)
		checkboxWidth = dat->checkboxSize + 2;
	if (testx < dat->leftMargin + indent * dat->groupIndent + checkboxWidth) {
		if (flags)
			*flags |= CLCHT_ONITEMCHECK;
		return hit;
	}
	if (testx < dat->leftMargin + indent * dat->groupIndent + checkboxWidth + dat->iconXSpace) {
		if (flags)
			*flags |= CLCHT_ONITEMICON;
		return hit;
	}

	for (i = 0; i < dat->extraColumnsCount; i++) {
		if (hitcontact->iExtraImage[i] == 0xFF)
			continue;
		if (testx >= clRect.right - dat->extraColumnSpacing * (dat->extraColumnsCount - i) &&
			testx < clRect.right - dat->extraColumnSpacing * (dat->extraColumnsCount - i) + g_IconWidth ) {
				if (flags)
					*flags |= CLCHT_ONITEMEXTRA | (i << 24);
				return hit;
			}
	}
	hdc = GetDC(hwnd);
	if (hitcontact->type == CLCIT_GROUP)
		hFont = SelectObject(hdc, dat->fontInfo[FONTID_GROUPS].hFont);
	else
		hFont = SelectObject(hdc, dat->fontInfo[FONTID_CONTACTS].hFont);
	GetTextExtentPoint32(hdc, hitcontact->szText, lstrlen(hitcontact->szText), &textSize);
	width = textSize.cx;
	if (hitcontact->type == CLCIT_GROUP) {
		char *szCounts;
		szCounts = cli.pfnGetGroupCountsText(dat, hitcontact);
		if (szCounts[0]) {
			GetTextExtentPoint32A(hdc, " ", 1, &textSize);
			width += textSize.cx;
			SelectObject(hdc, dat->fontInfo[FONTID_GROUPCOUNTS].hFont);
			GetTextExtentPoint32A(hdc, szCounts, lstrlenA(szCounts), &textSize);
			width += textSize.cx;
		}
	}
	SelectObject(hdc, hFont);
	ReleaseDC(hwnd, hdc);
	if (testx < dat->leftMargin + indent * dat->groupIndent + checkboxWidth + dat->iconXSpace + width + 4) {
		if (flags)
			*flags |= CLCHT_ONITEMLABEL;
		return hit;
	}
	if (flags)
		*flags |= CLCHT_NOWHERE;
	return -1;
}

void fnScrollTo(HWND hwnd, struct ClcData *dat, int desty, int noSmooth)
{
	DWORD startTick, nowTick;
	int oldy = dat->yScroll;
	RECT clRect, rcInvalidate;
	int maxy, previousy;

	if (dat->iHotTrack != -1 && dat->yScroll != desty) {
		cli.pfnInvalidateItem(hwnd, dat, dat->iHotTrack);
		dat->iHotTrack = -1;
		ReleaseCapture();
	}
	GetClientRect(hwnd, &clRect);
	rcInvalidate = clRect;
	maxy = cli.pfnGetRowTotalHeight(dat) - clRect.bottom;
	if (desty > maxy)
		desty = maxy;
	if (desty < 0)
		desty = 0;
	if (abs(desty - dat->yScroll) < 4)
		noSmooth = 1;
	if (!noSmooth && dat->exStyle & CLS_EX_NOSMOOTHSCROLLING)
		noSmooth = 1;
	previousy = dat->yScroll;
	if (!noSmooth) {
		startTick = GetTickCount();
		for (;;) {
			nowTick = GetTickCount();
			if (nowTick >= startTick + dat->scrollTime)
				break;
			dat->yScroll = oldy + (desty - oldy) * (int) (nowTick - startTick) / dat->scrollTime;
			if (dat->backgroundBmpUse & CLBF_SCROLL || dat->hBmpBackground == NULL)
				ScrollWindowEx(hwnd, 0, previousy - dat->yScroll, NULL, NULL, NULL, NULL, SW_INVALIDATE);
			else
				cli.pfnInvalidateRect(hwnd, NULL, FALSE);
			previousy = dat->yScroll;
			SetScrollPos(hwnd, SB_VERT, dat->yScroll, TRUE);
			UpdateWindow(hwnd);
		}
	}
	dat->yScroll = desty;
	if (dat->backgroundBmpUse & CLBF_SCROLL || dat->hBmpBackground == NULL)
		ScrollWindowEx(hwnd, 0, previousy - dat->yScroll, NULL, NULL, NULL, NULL, SW_INVALIDATE);
	else
		cli.pfnInvalidateRect(hwnd, NULL, FALSE);
	SetScrollPos(hwnd, SB_VERT, dat->yScroll, TRUE);
}

void fnEnsureVisible(HWND hwnd, struct ClcData *dat, int iItem, int partialOk)
{
	int itemy, itemh = cli.pfnGetRowHeight(dat, iItem), newY;
	int moved = 0;
	RECT clRect;

	GetClientRect(hwnd, &clRect);
	itemy = cli.pfnGetRowTopY(dat, iItem);
	if (partialOk) {
		if (itemy + itemh - 1 < dat->yScroll) {
			newY = itemy;
			moved = 1;
		}
		else if (itemy >= dat->yScroll + clRect.bottom) {
			newY = itemy - clRect.bottom + itemh;
			moved = 1;
		}
	}
	else {
		if (itemy < dat->yScroll) {
			newY = itemy;
			moved = 1;
		}
		else if (itemy >= dat->yScroll + clRect.bottom - itemh) {
			newY = itemy - clRect.bottom + itemh;
			moved = 1;
		}
	}
	if (moved)
		cli.pfnScrollTo(hwnd, dat, newY, 0);
}

void fnRecalcScrollBar(HWND hwnd, struct ClcData *dat)
{
	SCROLLINFO si = { 0 };
	RECT clRect;
	NMCLISTCONTROL nm;

	GetClientRect(hwnd, &clRect);
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = cli.pfnGetRowTotalHeight(dat)-1;
	si.nPage = clRect.bottom;
	si.nPos = dat->yScroll;

	if (GetWindowLong(hwnd, GWL_STYLE) & CLS_CONTACTLIST) {
		if (dat->noVScrollbar == 0)
			SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
	}
	else SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

	cli.pfnScrollTo(hwnd, dat, dat->yScroll, 1);
	nm.hdr.code = CLN_LISTSIZECHANGE;
	nm.hdr.hwndFrom = hwnd;
	nm.hdr.idFrom = GetDlgCtrlID(hwnd);
	nm.pt.y = si.nMax;
	SendMessage(GetParent(hwnd), WM_NOTIFY, 0, (LPARAM) & nm);
}

void fnSetGroupExpand(HWND hwnd, struct ClcData *dat, struct ClcGroup *group, int newState)
{
	int contentCount;
	int groupy;
	int newY, posY;
	RECT clRect;
	NMCLISTCONTROL nm;

	if (newState == -1)
		group->expanded ^= 1;
	else {
		if (group->expanded == (newState != 0))
			return;
		group->expanded = newState != 0;
	}
	cli.pfnInvalidateRect(hwnd, NULL, FALSE);
	contentCount = cli.pfnGetGroupContentsCount(group, 1);
	groupy = cli.pfnGetRowsPriorTo(&dat->list, group, -1);
	if (dat->selection > groupy && dat->selection < groupy + contentCount)
		dat->selection = groupy;
	GetClientRect(hwnd, &clRect);
	newY = dat->yScroll;
	posY = cli.pfnGetRowBottomY(dat, groupy + contentCount);
	if (posY >= newY + clRect.bottom)
		newY = posY - clRect.bottom;
	posY = cli.pfnGetRowTopY(dat, groupy);
	if (newY > posY)
		newY = posY;
	cli.pfnRecalcScrollBar(hwnd, dat);
	cli.pfnScrollTo(hwnd, dat, newY, 0);
	nm.hdr.code = CLN_EXPANDED;
	nm.hdr.hwndFrom = hwnd;
	nm.hdr.idFrom = GetDlgCtrlID(hwnd);
	nm.hItem = (HANDLE) group->groupId;
	nm.action = group->expanded;
	SendMessage(GetParent(hwnd), WM_NOTIFY, 0, (LPARAM) & nm);
}

void fnDoSelectionDefaultAction(HWND hwnd, struct ClcData *dat)
{
	struct ClcContact *contact;

	if (dat->selection == -1)
		return;
	dat->szQuickSearch[0] = 0;
	if (cli.pfnGetRowByIndex(dat, dat->selection, &contact, NULL) == -1)
		return;
	if (contact->type == CLCIT_GROUP)
		cli.pfnSetGroupExpand(hwnd, dat, contact->group, -1);
	if (contact->type == CLCIT_CONTACT)
		CallService(MS_CLIST_CONTACTDOUBLECLICKED, (WPARAM) contact->hContact, 0);
}

int fnFindRowByText(HWND hwnd, struct ClcData *dat, const TCHAR *text, int prefixOk)
{
	struct ClcGroup *group = &dat->list;
	int testlen = lstrlen(text);

	group->scanIndex = 0;
	for (;;) {
		if (group->scanIndex == group->cl.count) {
			group = group->parent;
			if (group == NULL)
				break;
			group->scanIndex++;
			continue;
		}
		if (group->cl.items[group->scanIndex]->type != CLCIT_DIVIDER) {
			if ((prefixOk && !_tcsnicmp(text, group->cl.items[group->scanIndex]->szText, testlen)) ||
				(!prefixOk && !lstrcmpi(text, group->cl.items[group->scanIndex]->szText))) {
					struct ClcGroup *contactGroup = group;
					int contactScanIndex = group->scanIndex;
					for (; group; group = group->parent)
						cli.pfnSetGroupExpand(hwnd, dat, group, 1);
					return cli.pfnGetRowsPriorTo(&dat->list, contactGroup, contactScanIndex);
				}
				if (group->cl.items[group->scanIndex]->type == CLCIT_GROUP) {
					if (!(dat->exStyle & CLS_EX_QUICKSEARCHVISONLY) || group->cl.items[group->scanIndex]->group->expanded) {
						group = group->cl.items[group->scanIndex]->group;
						group->scanIndex = 0;
						continue;
					}
				}
		}
		group->scanIndex++;
	}
	return -1;
}

void fnEndRename(HWND hwnd, struct ClcData *dat, int save)
{
	HWND hwndEdit = dat->hwndRenameEdit;

	if (dat->hwndRenameEdit == NULL)
		return;
	dat->hwndRenameEdit = NULL;
	if (save) {
		TCHAR text[120];
		struct ClcContact *contact;
		GetWindowText(hwndEdit, text, SIZEOF(text));
		if (cli.pfnGetRowByIndex(dat, dat->selection, &contact, NULL) != -1) {
			if (lstrcmp(contact->szText, text)) {
				if (contact->type == CLCIT_GROUP && !_tcsstr(text, _T("\\"))) {
					TCHAR szFullName[256];
					if (contact->group->parent && contact->group->parent->parent)
						mir_sntprintf( szFullName, SIZEOF(szFullName), _T("%s\\%s"),
							cli.pfnGetGroupName(contact->group->parent->groupId, NULL), text);
					else 
						lstrcpyn( szFullName, text, SIZEOF( szFullName ));
					cli.pfnRenameGroup( contact->groupId, szFullName );
				}
				else if (contact->type == CLCIT_CONTACT) {
					TCHAR* otherName = cli.pfnGetContactDisplayName(contact->hContact, GCDNF_NOMYHANDLE);
					cli.pfnInvalidateDisplayNameCacheEntry(contact->hContact);
					if (text[0] == '\0') {
						DBDeleteContactSetting(contact->hContact, "CList", "MyHandle");
					}
					else {
						if (!lstrcmp(otherName, text))
							DBDeleteContactSetting(contact->hContact, "CList", "MyHandle");
						else
							DBWriteContactSettingTString(contact->hContact, "CList", "MyHandle", text);
					}
					if (otherName)
						mir_free(otherName);
				}
			}
		}
	}
	DestroyWindow(hwndEdit);
}

void fnDeleteFromContactList(HWND hwnd, struct ClcData *dat)
{
	struct ClcContact *contact;
	if (dat->selection == -1)
		return;
	dat->szQuickSearch[0] = 0;
	if (cli.pfnGetRowByIndex(dat, dat->selection, &contact, NULL) == -1)
		return;
	switch (contact->type) {
	case CLCIT_GROUP:
		CallService(MS_CLIST_GROUPDELETE, (WPARAM) (HANDLE) contact->groupId, 0);
		break;
	case CLCIT_CONTACT:
		CallService("CList/DeleteContactCommand", (WPARAM) (HANDLE)
			contact->hContact, (LPARAM) hwnd);
		break;
	}
}

static WNDPROC OldRenameEditWndProc;
static LRESULT CALLBACK RenameEditSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_RETURN:
			cli.pfnEndRename(GetParent(hwnd), (struct ClcData *) GetWindowLong(GetParent(hwnd), 0), 1);
			return 0;
		case VK_ESCAPE:
			cli.pfnEndRename(GetParent(hwnd), (struct ClcData *) GetWindowLong(GetParent(hwnd), 0), 0);
			return 0;
		}
		break;
	case WM_GETDLGCODE:
		if (lParam) {
			MSG *msg = (MSG *) lParam;
			if (msg->message == WM_KEYDOWN && msg->wParam == VK_TAB)
				return 0;
			if (msg->message == WM_CHAR && msg->wParam == '\t')
				return 0;
		}
		return DLGC_WANTMESSAGE;
	case WM_KILLFOCUS:
		cli.pfnEndRename(GetParent(hwnd), (struct ClcData *) GetWindowLong(GetParent(hwnd), 0), 1);
		return 0;
	}
	return CallWindowProc(OldRenameEditWndProc, hwnd, msg, wParam, lParam);
}

void fnBeginRenameSelection(HWND hwnd, struct ClcData *dat)
{
	struct ClcContact *contact;
	struct ClcGroup *group;
	RECT clRect;
	POINT pt;
	int h;

	KillTimer(hwnd, TIMERID_RENAME);
	ReleaseCapture();
	dat->iHotTrack = -1;
	dat->selection = cli.pfnGetRowByIndex(dat, dat->selection, &contact, &group);
	if (dat->selection == -1)
		return;
	if (contact->type != CLCIT_CONTACT && contact->type != CLCIT_GROUP)
		return;
	GetClientRect(hwnd, &clRect);
	cli.pfnCalcEipPosition( dat, contact, group, &pt );
	h = cli.pfnGetRowHeight(dat, dat->selection);
	dat->hwndRenameEdit = CreateWindow( _T("EDIT"), contact->szText, WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, pt.x, pt.y, clRect.right - pt.x, h, hwnd, NULL, cli.hInst, NULL);
	OldRenameEditWndProc = (WNDPROC) SetWindowLong(dat->hwndRenameEdit, GWL_WNDPROC, (LONG) RenameEditSubclassProc);
	SendMessage(dat->hwndRenameEdit, WM_SETFONT, (WPARAM) (contact->type == CLCIT_GROUP ? dat->fontInfo[FONTID_GROUPS].hFont : dat->fontInfo[FONTID_CONTACTS].hFont), 0);
	SendMessage(dat->hwndRenameEdit, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN | EC_USEFONTINFO, 0);
	SendMessage(dat->hwndRenameEdit, EM_SETSEL, 0, (LPARAM) (-1));
	ShowWindow(dat->hwndRenameEdit, SW_SHOW);
	SetFocus(dat->hwndRenameEdit);
}

void fnCalcEipPosition( struct ClcData *dat, struct ClcContact *contact, struct ClcGroup *group, POINT *result)
{
	int indent;
	for (indent = 0; group->parent; indent++, group = group->parent);
	result->x = indent * dat->groupIndent + dat->iconXSpace - 2;
	result->y = cli.pfnGetRowTopY(dat, dat->selection) - dat->yScroll;
}

int fnGetDropTargetInformation(HWND hwnd, struct ClcData *dat, POINT pt)
{
	RECT clRect;
	int hit;
	struct ClcContact *contact, *movecontact;
	struct ClcGroup *group, *movegroup;
	DWORD hitFlags;

	GetClientRect(hwnd, &clRect);
	dat->selection = dat->iDragItem;
	dat->iInsertionMark = -1;
	if (!PtInRect(&clRect, pt))
		return DROPTARGET_OUTSIDE;

	hit = cli.pfnHitTest(hwnd, dat, pt.x, pt.y, &contact, &group, &hitFlags);
	cli.pfnGetRowByIndex(dat, dat->iDragItem, &movecontact, &movegroup);
	if (hit == dat->iDragItem)
		return DROPTARGET_ONSELF;
	if (hit == -1 || hitFlags & CLCHT_ONITEMEXTRA)
		return DROPTARGET_ONNOTHING;

	if (movecontact->type == CLCIT_GROUP) {
		struct ClcContact *bottomcontact = NULL, *topcontact = NULL;
		struct ClcGroup *topgroup = NULL;
		int topItem = -1, bottomItem;
		int ok = 0;
		if (pt.y + dat->yScroll < cli.pfnGetRowTopY(dat, hit) + dat->insertionMarkHitHeight) {
			//could be insertion mark (above)
			topItem = hit - 1;
			bottomItem = hit;
			bottomcontact = contact;
			topItem = cli.pfnGetRowByIndex(dat, topItem, &topcontact, &topgroup);
			ok = 1;
		}
		if (pt.y + dat->yScroll >= cli.pfnGetRowBottomY(dat, hit+1) - dat->insertionMarkHitHeight) {
			//could be insertion mark (below)
			topItem = hit;
			bottomItem = hit + 1;
			topcontact = contact;
			topgroup = group;
			bottomItem = cli.pfnGetRowByIndex(dat, bottomItem, &bottomcontact, NULL);
			ok = 1;
		}
		if (ok) {
			ok = 0;
			if (bottomItem == -1 || bottomcontact->type != CLCIT_GROUP) {       //need to special-case moving to end
				if (topItem != dat->iDragItem) {
					for (; topgroup; topgroup = topgroup->parent) {
						if (topgroup == movecontact->group)
							break;
						if (topgroup == movecontact->group->parent) {
							ok = 1;
							break;
						}
					}
					if (ok)
						bottomItem = topItem + 1;
				}
			}
			else if (bottomItem != dat->iDragItem && bottomcontact->type == CLCIT_GROUP && bottomcontact->group->parent == movecontact->group->parent) {
				if (bottomcontact != movecontact + 1)
					ok = 1;
			}
			if (ok) {
				dat->iInsertionMark = bottomItem;
				dat->selection = -1;
				return DROPTARGET_INSERTION;
			}
		}
	}
	if (contact->type == CLCIT_GROUP) {
		if (dat->iInsertionMark == -1) {
			if (movecontact->type == CLCIT_GROUP) {     //check not moving onto its own subgroup
				for (; group; group = group->parent)
					if (group == movecontact->group)
						return DROPTARGET_ONSELF;
			}
			dat->selection = hit;
			return DROPTARGET_ONGROUP;
		}
	}
	return DROPTARGET_ONCONTACT;
}

int fnClcStatusToPf2(int status)
{
	switch(status) {
		case ID_STATUS_ONLINE: return PF2_ONLINE;
		case ID_STATUS_AWAY: return PF2_SHORTAWAY;
		case ID_STATUS_DND: return PF2_HEAVYDND;
		case ID_STATUS_NA: return PF2_LONGAWAY;
		case ID_STATUS_OCCUPIED: return PF2_LIGHTDND;
		case ID_STATUS_FREECHAT: return PF2_FREECHAT;
		case ID_STATUS_INVISIBLE: return PF2_INVISIBLE;
		case ID_STATUS_ONTHEPHONE: return PF2_ONTHEPHONE;
		case ID_STATUS_OUTTOLUNCH: return PF2_OUTTOLUNCH;
		case ID_STATUS_OFFLINE: return MODEF_OFFLINE;
	}
	return 0;
}

int fnIsHiddenMode(struct ClcData *dat, int status)
{
	return dat->offlineModes & cli.pfnClcStatusToPf2(status);
}

void fnHideInfoTip(HWND hwnd, struct ClcData *dat)
{
	CLCINFOTIP it = { 0 };

	if (dat->hInfoTipItem == NULL)
		return;
	it.isGroup = IsHContactGroup(dat->hInfoTipItem);
	it.hItem = (HANDLE) ((unsigned) dat->hInfoTipItem & ~HCONTACT_ISGROUP);
	it.cbSize = sizeof(it);
	dat->hInfoTipItem = NULL;
	NotifyEventHooks(hHideInfoTipEvent, 0, (LPARAM) & it);
}

void fnNotifyNewContact(HWND hwnd, HANDLE hContact)
{
	NMCLISTCONTROL nm;
	nm.hdr.code = CLN_NEWCONTACT;
	nm.hdr.hwndFrom = hwnd;
	nm.hdr.idFrom = GetDlgCtrlID(hwnd);
	nm.flags = 0;
	nm.hItem = hContact;
	SendMessage(GetParent(hwnd), WM_NOTIFY, 0, (LPARAM) & nm);
}

DWORD fnGetDefaultExStyle(void)
{
	BOOL param;
	DWORD ret = CLCDEFAULT_EXSTYLE;
	if (SystemParametersInfo(SPI_GETLISTBOXSMOOTHSCROLLING, 0, &param, FALSE) && !param)
		ret |= CLS_EX_NOSMOOTHSCROLLING;
	if (SystemParametersInfo(SPI_GETHOTTRACKING, 0, &param, FALSE) && !param)
		ret &= ~CLS_EX_TRACKSELECT;
	return ret;
}

#define DBFONTF_BOLD       1
#define DBFONTF_ITALIC     2
#define DBFONTF_UNDERLINE  4

void fnGetDefaultFontSetting(int i, LOGFONT* lf, COLORREF* colour)
{
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), lf, FALSE);
	*colour = GetSysColor(COLOR_WINDOWTEXT);
	lf->lfHeight = 8;
	switch (i) {
	case FONTID_GROUPS:
		lf->lfWeight = FW_BOLD;
		break;
	case FONTID_GROUPCOUNTS:
		*colour = GetSysColor(COLOR_3DSHADOW);
		break;
	case FONTID_OFFINVIS:
	case FONTID_INVIS:
		lf->lfItalic = !lf->lfItalic;
		break;
	case FONTID_DIVIDERS:
		break;
	case FONTID_NOTONLIST:
		*colour = GetSysColor(COLOR_3DSHADOW);
		break;
}	}

void fnGetFontSetting(int i, LOGFONT* lf, COLORREF* colour)
{
	DBVARIANT dbv;
	char idstr[20];
	BYTE style;

	cli.pfnGetDefaultFontSetting(i, lf, colour);
	wsprintfA(idstr, "Font%dName", i);
	if ( !DBGetContactSettingTString(NULL, "CLC", idstr, &dbv )) {
		lstrcpy(lf->lfFaceName, dbv.ptszVal);
		mir_free(dbv.pszVal);
	}
	wsprintfA(idstr, "Font%dCol", i);
	*colour = DBGetContactSettingDword(NULL, "CLC", idstr, *colour);
	wsprintfA(idstr, "Font%dSize", i);
	lf->lfHeight = (char) DBGetContactSettingByte(NULL, "CLC", idstr, lf->lfHeight);
	wsprintfA(idstr, "Font%dSty", i);
	style = (BYTE) DBGetContactSettingByte(NULL, "CLC", idstr, (lf->lfWeight == FW_NORMAL ? 0 : DBFONTF_BOLD) | (lf->lfItalic ? DBFONTF_ITALIC : 0) | (lf->lfUnderline ? DBFONTF_UNDERLINE : 0));
	lf->lfWidth = lf->lfEscapement = lf->lfOrientation = 0;
	lf->lfWeight = style & DBFONTF_BOLD ? FW_BOLD : FW_NORMAL;
	lf->lfItalic = (style & DBFONTF_ITALIC) != 0;
	lf->lfUnderline = (style & DBFONTF_UNDERLINE) != 0;
	lf->lfStrikeOut = 0;
	wsprintfA(idstr, "Font%dSet", i);
	lf->lfCharSet = DBGetContactSettingByte(NULL, "CLC", idstr, lf->lfCharSet);
	lf->lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf->lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf->lfQuality = DEFAULT_QUALITY;
	lf->lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
}

void fnLoadClcOptions(HWND hwnd, struct ClcData *dat)
{
	dat->rowHeight = DBGetContactSettingByte(NULL, "CLC", "RowHeight", CLCDEFAULT_ROWHEIGHT);
	{
		int i;
		LOGFONT lf;
		SIZE fontSize;
		HDC hdc = GetDC(hwnd);
		HFONT hFont = GetCurrentObject(hdc, OBJ_FONT);
		HFONT holdfont;	

		for (i = 0; i <= FONTID_MAX; i++) {
			if (!dat->fontInfo[i].changed)
				DeleteObject(dat->fontInfo[i].hFont);
			cli.pfnGetFontSetting(i, &lf, &dat->fontInfo[i].colour);
			{
				LONG height;
				HDC hdc = GetDC(NULL);
				height = lf.lfHeight;
				lf.lfHeight = -MulDiv(lf.lfHeight, GetDeviceCaps(hdc, LOGPIXELSY), 72);
				ReleaseDC(NULL, hdc);
				dat->fontInfo[i].hFont = CreateFontIndirect(&lf);
				lf.lfHeight = height;
			}
			dat->fontInfo[i].changed = 0;
			holdfont = SelectObject(hdc,dat->fontInfo[i].hFont);
			GetTextExtentPoint32(hdc, _T("x"), 1, &fontSize);
			dat->fontInfo[i].fontHeight = fontSize.cy;
			if (holdfont) SelectObject(hdc, holdfont);
		}
		SelectObject(hdc,hFont);
		ReleaseDC(hwnd, hdc);
	}
	dat->leftMargin = DBGetContactSettingByte(NULL, "CLC", "LeftMargin", CLCDEFAULT_LEFTMARGIN);
	dat->exStyle = DBGetContactSettingDword(NULL, "CLC", "ExStyle", cli.pfnGetDefaultExStyle());
	dat->scrollTime = DBGetContactSettingWord(NULL, "CLC", "ScrollTime", CLCDEFAULT_SCROLLTIME);
	dat->groupIndent = DBGetContactSettingByte(NULL, "CLC", "GroupIndent", CLCDEFAULT_GROUPINDENT);
	dat->gammaCorrection = DBGetContactSettingByte(NULL, "CLC", "GammaCorrect", CLCDEFAULT_GAMMACORRECT);
	dat->showIdle = DBGetContactSettingByte(NULL, "CLC", "ShowIdle", CLCDEFAULT_SHOWIDLE);
	dat->noVScrollbar = DBGetContactSettingByte(NULL, "CLC", "NoVScrollBar", 0);
	SendMessage(hwnd, INTM_SCROLLBARCHANGED, 0, 0);
	if (!dat->bkChanged) {
		DBVARIANT dbv;
		dat->bkColour = DBGetContactSettingDword(NULL, "CLC", "BkColour", CLCDEFAULT_BKCOLOUR);
		if (dat->hBmpBackground) {
			DeleteObject(dat->hBmpBackground);
			dat->hBmpBackground = NULL;
		}
		if (DBGetContactSettingByte(NULL, "CLC", "UseBitmap", CLCDEFAULT_USEBITMAP)) {
			if (!DBGetContactSetting(NULL, "CLC", "BkBitmap", &dbv)) {
				dat->hBmpBackground = (HBITMAP) CallService(MS_UTILS_LOADBITMAP, 0, (LPARAM) dbv.pszVal);
				mir_free(dbv.pszVal);
			}
		}
		dat->backgroundBmpUse = DBGetContactSettingWord(NULL, "CLC", "BkBmpUse", CLCDEFAULT_BKBMPUSE);
	}
	dat->greyoutFlags = DBGetContactSettingDword(NULL, "CLC", "GreyoutFlags", CLCDEFAULT_GREYOUTFLAGS);
	dat->offlineModes = DBGetContactSettingDword(NULL, "CLC", "OfflineModes", CLCDEFAULT_OFFLINEMODES);
	dat->selBkColour = DBGetContactSettingDword(NULL, "CLC", "SelBkColour", CLCDEFAULT_SELBKCOLOUR);
	dat->selTextColour = DBGetContactSettingDword(NULL, "CLC", "SelTextColour", CLCDEFAULT_SELTEXTCOLOUR);
	dat->hotTextColour = DBGetContactSettingDword(NULL, "CLC", "HotTextColour", CLCDEFAULT_HOTTEXTCOLOUR);
	dat->quickSearchColour = DBGetContactSettingDword(NULL, "CLC", "QuickSearchColour", CLCDEFAULT_QUICKSEARCHCOLOUR);
	dat->useWindowsColours = DBGetContactSettingByte(NULL, "CLC", "UseWinColours", CLCDEFAULT_USEWINDOWSCOLOURS);
	{
		NMHDR hdr;
		hdr.code = CLN_OPTIONSCHANGED;
		hdr.hwndFrom = hwnd;
		hdr.idFrom = GetDlgCtrlID(hwnd);
		SendMessage(GetParent(hwnd), WM_NOTIFY, 0, (LPARAM) & hdr);
	}
	SendMessage(hwnd, WM_SIZE, 0, 0);
}

#define GSIF_HASMEMBERS   0x80000000
#define GSIF_ALLCHECKED   0x40000000
#define GSIF_INDEXMASK    0x3FFFFFFF
void fnRecalculateGroupCheckboxes(HWND hwnd, struct ClcData *dat)
{
	struct ClcGroup *group;
	int check;

	group = &dat->list;
	group->scanIndex = GSIF_ALLCHECKED;
	for (;;) {
		if ((group->scanIndex & GSIF_INDEXMASK) == group->cl.count) {
			check = (group->scanIndex & (GSIF_HASMEMBERS | GSIF_ALLCHECKED)) == (GSIF_HASMEMBERS | GSIF_ALLCHECKED);
			group = group->parent;
			if (group == NULL)
				break;
			if (check)
				group->cl.items[(group->scanIndex & GSIF_INDEXMASK)]->flags |= CONTACTF_CHECKED;
			else {
				group->cl.items[(group->scanIndex & GSIF_INDEXMASK)]->flags &= ~CONTACTF_CHECKED;
				group->scanIndex &= ~GSIF_ALLCHECKED;
			}
		}
		else if (group->cl.items[(group->scanIndex & GSIF_INDEXMASK)]->type == CLCIT_GROUP) {
			group = group->cl.items[(group->scanIndex & GSIF_INDEXMASK)]->group;
			group->scanIndex = GSIF_ALLCHECKED;
			continue;
		}
		else if (group->cl.items[(group->scanIndex & GSIF_INDEXMASK)]->type == CLCIT_CONTACT) {
			group->scanIndex |= GSIF_HASMEMBERS;
			if (!(group->cl.items[(group->scanIndex & GSIF_INDEXMASK)]->flags & CONTACTF_CHECKED))
				group->scanIndex &= ~GSIF_ALLCHECKED;
		}
		group->scanIndex++;
	}
}

void fnSetGroupChildCheckboxes(struct ClcGroup *group, int checked)
{
	int i;

	for (i = 0; i < group->cl.count; i++) {
		if (group->cl.items[i]->type == CLCIT_GROUP) {
			cli.pfnSetGroupChildCheckboxes(group->cl.items[i]->group, checked);
			if (checked)
				group->cl.items[i]->flags |= CONTACTF_CHECKED;
			else
				group->cl.items[i]->flags &= ~CONTACTF_CHECKED;
		}
		else if (group->cl.items[i]->type == CLCIT_CONTACT) {
			if (checked)
				group->cl.items[i]->flags |= CONTACTF_CHECKED;
			else
				group->cl.items[i]->flags &= ~CONTACTF_CHECKED;
		}
	}
}

void fnInvalidateItem(HWND hwnd, struct ClcData *dat, int iItem)
{
	RECT rc;
	if ( iItem == -1 )
		return;

	GetClientRect(hwnd, &rc);
	rc.top = cli.pfnGetRowTopY(dat, iItem) - dat->yScroll;
	rc.bottom = rc.top + cli.pfnGetRowHeight(dat, iItem);
	cli.pfnInvalidateRect(hwnd, &rc, FALSE);
}

///////////////////////////////////////////////////////////////////////////////
// row coord functions

int fnGetRowTopY(struct ClcData *dat, int item)
{	return item * dat->rowHeight;
}

int fnGetRowBottomY(struct ClcData *dat, int item)
{	return (item+1) * dat->rowHeight;
}

int fnGetRowTotalHeight(struct ClcData *dat)
{	return dat->rowHeight * cli.pfnGetGroupContentsCount(&dat->list, 1);
}

int fnGetRowHeight(struct ClcData *dat, int item)
{	return dat->rowHeight;
}

int fnRowHitTest(struct ClcData *dat, int y)
{	if (!dat->rowHeight)
		return y;
	return y / dat->rowHeight;
}