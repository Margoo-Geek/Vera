#pragma once
#include <vector>
#include <iostream>
#include "VObject.h"

#define  WM_SHOWTASK (WM_USER + 1)

enum class VButtonEvent {
	VeraClick
};

struct VButtonEventStruct {
	WPARAM aimsId;
	VButtonEvent event;
};

enum class VWidgetEvent {
	VeraSizeChange,
	VeraMouseCheak,
	VeraWindowSmall,
	VeraWindowMax,
	VeraWindowClose
};

struct VWidgetEventStruct {
	HWND aimsId;
	VWidgetEvent event;
};

struct FTWMPAINT {
	HWND aimsId = NULL;
	VString url = "";
};

constexpr UINT V_TRAY_CHLIK = 0xffffff;

enum class VTrayIconStyle {
	FromFile,
	FromSourfile
};

class VTray {
public:
	VString description;
	VString iconFile = "No icon file";
	LPWSTR iconSour = (LPWSTR)L"No icon";
	size_t uid = 0;
	void setIcon(VTrayIconStyle style, LPWSTR source, VString file) {
		if (style == VTrayIconStyle::FromFile)
			iconFile = file;
		else
			iconSour = source;
	}
	void setDescription(VString descriptionString) {
		description = descriptionString;
	}
};

struct FTWMTRAY {
	HWND amisId = NULL;
	VTray tray;
};

struct FTWMCLOSE {
	HWND amisId = NULL;
	std::function<void()>event;
};

std::vector<VWidgetEventStruct>VWidgetEventVector;
std::vector<VButtonEventStruct>VButtonEventVector;
std::vector<FTWMPAINT>FTWM_SLOT;
std::vector<FTWMTRAY>FTWMTRAY_SLOT;
std::vector<FTWMCLOSE>FTWMCLOSE_SLOT;


long long button_case = 0;
void ToTray(HWND hWnd,FTWMTRAY tr) {
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd;
	nid.uID = tr.tray.uid;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;
	if (tr.tray.iconSour != L"No icon") nid.hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(tr.tray.iconSour));
	else if (tr.tray.iconFile != "No icon file") nid.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), tr.tray.iconFile.toStdWstring().c_str(), IMAGE_ICON, 30, 40, LR_LOADFROMFILE);
	wcscpy_s(nid.szTip, tr.tray.description.toStdWstring().c_str());
	Shell_NotifyIcon(NIM_ADD, &nid);
}
void DeleteTray(HWND hWnd, FTWMTRAY tr) {
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd;
	nid.uID = tr.tray.uid;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;
	if (tr.tray.iconSour != L"No icon") nid.hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(tr.tray.iconSour));
	else if (tr.tray.iconFile != "No icon file") nid.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), tr.tray.iconFile.toStdWstring().c_str(), IMAGE_ICON, 30, 40, LR_LOADFROMFILE);
	wcscpy_s(nid.szTip, tr.tray.description.toStdWstring().c_str());
	Shell_NotifyIcon(NIM_DELETE, &nid);
}