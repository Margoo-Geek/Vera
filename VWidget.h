#pragma once
#pragma warning (disable:4302)
#pragma warning (disable:4311)
#pragma warning (disable:4267)
#include "VObject.h"
#include "VString.h"
#include "VWinId.h"
#include "VSize.h"
#include <thread>
#include <functional>
#include "VApplication.h"
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")



LRESULT WINAPI VWigetProc(HWND hWnd, UINT uInt,
	WPARAM wpaRam, LPARAM lpAram);
#define CUR_Arrow 0
#define CUR_Wait  1
#define CUR_Ibeam 2
#define CUR_Cross 3

size_t tray_id;

class VWidget {
private:
	HWND winId = NULL;
	HWND w_parent;

	NOTIFYICONDATA nid;

	size_t t_id;

	VTray tray;

	std::vector<std::function<void()> >SizeChange;
	std::vector<std::function<void()> >MouseCheak;
	std::vector<std::function<void()> >Mini;
	std::vector<std::function<void()> >Max;

    std::thread pw_thread;

	VSize w_size;

	bool close = false;
	bool run_b = false;
	bool run_detache = false;

	void createWidgetWindow();
	void run_f() {
		while (true) {
			if (isClose() == true) break;
		}

		run_b = true;
	}

	void TrayDelete() {
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}

	_public enum class VerawindowFlag {
		VeraBorderlessStyle,
		VeraNoMaximizeButton,
		VeraNoMinimizeButton,
		VeraFixedSize,
		VeraUnableToDrag,
		VeraShowWindow,
		VeraHideWindow,
		VeraHideWindowIcon,
		VeraWindowForemost
	};
	_public VWidget(VWidget* parent = NULL);

	_public void setWindowName(VString name);
	_public void setGeometry(size_t x, size_t y,size_t w, size_t h);
	_public void setGeometry(VSize size);
	_public void setFixedSize(size_t w,size_t h);
	_public void setWindowIcon(VString url);
	_public void setCursor(LPCWSTR style);
	_public void setBackgroundFromPicture(VString url);


	_public void connect(std::function<void()>function,VWidgetEvent VWidgetEventStruct);

	_public void destroy();

	_public void setWindowFlag(VerawindowFlag flag);

	_public void resize(size_t w,size_t h);

	_public void move(size_t x,size_t y);

	_public void addTray(VTray tray);

	_public void setParent(VWidget* parent);
	_public void setParent(HWND parent);

	_public int run();

	_public bool isClose();

	_public void run_detach();

	_public void show();
	_public void hide();

	_public void _delete();

	_public wId getwId();
};

void VWidget::addTray(VTray tray) {
	tray.uid = static_cast<__int64>(t_id);
	this->tray = tray;
	FTWMTRAY puhk;
	puhk.amisId = winId;
	puhk.tray = tray;
	FTWMTRAY_SLOT.push_back(puhk);
}

void VWidget::setBackgroundFromPicture(VString url) {
	FTWMPAINT tmp;
	tmp.aimsId = winId;
	tmp.url = url;
	FTWM_SLOT.push_back(tmp);
}

void VWidget::setCursor(LPCWSTR style) {
	::SetCursor(::LoadCursorA(NULL, (LPCSTR)style));
}

void VWidget::setWindowIcon(VString url) {
	HICON hIcon, hIconSm;
	std::wstring cvt = url.toStdWstring();
#ifdef MSVC_2017
	hIcon = (HICON)LoadImage(NULL,(LPCSTR) cvt.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	SendMessage(winId, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	hIconSm = (HICON)LoadImage(NULL, (LPCSTR)cvt.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	SendMessage(winId, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
#else
	hIcon = (HICON)LoadImage(NULL, cvt.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	SendMessage(winId, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	hIconSm = (HICON)LoadImage(NULL, cvt.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	SendMessage(winId, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
#endif
}

void VWidget::run_detach() {
	std::thread run_t(&VWidget::run,this);
	run_detache = true;
	run_t.detach();
}
void VWidget::connect(std::function<void()>function, VWidgetEvent VWidgetEventStruct) {
	if (VWidgetEventStruct == VWidgetEvent::VeraSizeChange) SizeChange.push_back(function);
	else if (VWidgetEventStruct == VWidgetEvent::VeraMouseCheak) MouseCheak.push_back(function);
	else if (VWidgetEventStruct == VWidgetEvent::VeraWindowSmall) Mini.push_back(function);
	else if (VWidgetEventStruct == VWidgetEvent::VeraWindowMax) Max.push_back(function);
	else if (VWidgetEventStruct == VWidgetEvent::VeraWindowClose) {
		FTWMCLOSE cl;
		cl.amisId = winId;
		cl.event = function;
		FTWMCLOSE_SLOT.push_back(cl);
	}
}

void VWidget::setFixedSize(size_t w, size_t h) {
	resize(w,h);
	setWindowFlag(VerawindowFlag::VeraFixedSize);
}

void VWidget::setWindowFlag(VWidget::VerawindowFlag flag) {
	if (flag == VerawindowFlag::VeraBorderlessStyle) {
		LONG_PTR Style = ::GetWindowLongPtr(winId, GWL_STYLE);
		Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
		::SetWindowLongPtr(winId, GWL_STYLE, Style);
	}
	if (flag == VerawindowFlag::VeraFixedSize) {
		LONG_PTR Style = ::GetWindowLongPtr(winId, GWL_STYLE);
		Style = Style & ~WS_THICKFRAME;
		::SetWindowLongPtr(winId, GWL_STYLE, Style);
		setWindowFlag(VerawindowFlag::VeraNoMaximizeButton);
	}
	if (flag == VerawindowFlag::VeraNoMaximizeButton) {
		LONG_PTR Style = ::GetWindowLongPtr(winId, GWL_STYLE);
		Style = Style & ~WS_MAXIMIZEBOX;
		::SetWindowLongPtr(winId, GWL_STYLE, Style);
	}
	if (flag == VerawindowFlag::VeraNoMinimizeButton) {
		LONG_PTR Style = ::GetWindowLongPtr(winId, GWL_STYLE);
		Style = Style & ~WS_MINIMIZEBOX;
		::SetWindowLongPtr(winId, GWL_STYLE, Style);
	}
	if (flag == VerawindowFlag::VeraHideWindowIcon) {
		SetWindowLong(winId, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
	}
	if (flag == VerawindowFlag::VeraWindowForemost) {
		RECT rect;
		GetWindowRect(winId, &rect);
		SetWindowPos(winId, HWND_TOPMOST, rect.left, rect.top, 0, 0, SWP_NOSIZE);
	}
}


void VWidget::move(size_t x, size_t y) {
	w_size._x = x;
	w_size._y = y;
	unsigned long long tmp = static_cast<unsigned long long>(0);
	MoveWindow(winId, x, y, w_size._w, w_size._h, static_cast<int>(tmp <= INT_MAX));
}

void VWidget::resize(size_t w, size_t h) {
	w_size._w = w;
	w_size._h = h;
	MoveWindow(winId,w_size._x, w_size._y,w, h,FALSE);
}

void VWidget::destroy() {
	_delete();
}

void VWidget::setParent(VWidget* parent) {
	SetParent(winId, parent->winId);
}
void VWidget::setParent(HWND parent) {
	SetParent(winId, parent);
}

void VWidget::setGeometry(VSize size) {
	w_size = size;
	MoveWindow(winId, size._x, size._y, size._w, size._h, static_cast<int>(0));
}

void VWidget::setGeometry(size_t x, size_t y, size_t w, size_t h) {
	w_size._x = x;
	w_size._y = y;
	w_size._h = h;
	w_size._w = w;
	MoveWindow(winId, x, y, w, h,static_cast<int>(0));
}

void VWidget::setWindowName(VString name) {
#ifdef MSVC_2017
	SetWindowText(winId, name.c_str());
#else
	std::wstring string = name.toStdWstring();
	SetWindowText(winId, string.c_str());
#endif
}
int VWidget::run() {
	int getSize = 0;
	size_t vectsize[2] = { 0 };
	while (true) {
		vectsize[0] = VWidgetEventVector.size();
		if (vectsize[0] > vectsize[1]) {
			if (VWidgetEventVector[vectsize[0] - 1].aimsId == winId) {
				if (VWidgetEventVector.at(vectsize[0] - 1).event == VWidgetEvent::VeraSizeChange) {
					if (getSize != 0) {
						for (size_t i = 0; i < SizeChange.size(); i++) {
							SizeChange[i]();
						}
					}
					getSize++;
				}
				else if (VWidgetEventVector.at(vectsize[0] - 1).event == VWidgetEvent::VeraMouseCheak) {
					for (size_t i = 0; i < MouseCheak.size(); i++) {
						MouseCheak[i]();
					}
				}
				else if (VWidgetEventVector.at(vectsize[0] - 1).event == VWidgetEvent::VeraWindowSmall) {
					for (size_t i = 0; i < Mini.size(); i++) {
						Mini[i](); 
					}
				}
				else if (VWidgetEventVector.at(vectsize[0] - 1).event == VWidgetEvent::VeraWindowMax) {
					for (size_t i = 0; i < Max.size(); i++) {
						Max[i]();
					}
				}
			}
		}
		if (isClose() == true)
			break;
		vectsize[1] = VWidgetEventVector.size();
		Sleep(80);
	}
	return 0;
}

void VWidget::_delete() {
	pw_thread.detach();
}

void VWidget::show() {
	ShowWindow(winId,SW_SHOW);
}

void VWidget::hide() {
	ShowWindow(winId, SW_HIDE);
}

wId VWidget::getwId() {
	wId tmp(winId);
	return tmp;
}

VWidget::VWidget(VWidget* parent) {
	if (parent != NULL)
		w_parent = parent->winId;
	pw_thread = std::thread(&VWidget::createWidgetWindow, this);
	pw_thread.detach();
	while (true) if (winId != NULL) break;
}

void VWidget::createWidgetWindow() {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	WNDCLASSEX wc;
	MSG msg;
	HWND hwnd;
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = VWigetProc;
	wc.cbClsExtra = wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("VWidget Window");
	wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wc);
	
	hwnd = CreateWindowEx(NULL,
		wc.lpszClassName,
		wc.lpszClassName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		400,
		400,
		NULL,
		NULL,
		hInstance,
		NULL);
	UpdateWindow(hwnd);
	winId = hwnd;
	RECT rect;
	GetWindowRect(winId,&rect);
	w_size._x = rect.left;
	w_size._y = rect.top;
	w_size._w = sizeof(rect.right - rect.left) <= 4;
	w_size._h = sizeof(rect.bottom - rect.top) <= 4;
	if (w_parent != NULL) {
		setParent(w_parent);
		show();
	}
	t_id = tray_id;
	tray_id++;
	while (true) {
		if (!GetMessage(&msg, 0, 0, 0))break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	close = true;
}
bool VWidget::isClose() {
	return close;
}
void setGround(HWND m_hWnd, const TCHAR* pBackImgFullPath)
{
	DWORD dwExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if ((dwExStyle & 0x80000) != 0x80000)
		SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle ^ 0x80000);
	using namespace Gdiplus;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

#ifdef MSVC_2017
	Gdiplus::Image* pImage = Gdiplus::Image::FromFile((WCHAR*)pBackImgFullPath);
#else
	Gdiplus::Image* pImage = Gdiplus::Image::FromFile(pBackImgFullPath);
#endif
	if (pImage == NULL) {
		throw "Picture open error";
	}

	RECT windowRect;
	GetWindowRect(m_hWnd, &windowRect);
	SIZE sizeWindow;
	if (windowRect.left == windowRect.right) {
		sizeWindow.cx = pImage->GetWidth();
		sizeWindow.cy = pImage->GetHeight();
	}
	else {
		sizeWindow.cx = windowRect.right - windowRect.left;
		sizeWindow.cy = windowRect.bottom - windowRect.top;
	}

	HDC hDC = ::GetDC(m_hWnd);
	HDC hdcMemory = CreateCompatibleDC(hDC);
	RECT rcWindow;
	GetWindowRect(m_hWnd, &rcWindow);

	BITMAPINFOHEADER stBmpInfoHeader = { 0 };
	int nBytesPerLine = ((sizeWindow.cx * 32 + 31) & (~31)) >> 3;
	stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	stBmpInfoHeader.biWidth = sizeWindow.cx;
	stBmpInfoHeader.biHeight = sizeWindow.cy;
	stBmpInfoHeader.biPlanes = 1;
	stBmpInfoHeader.biBitCount = 32;
	stBmpInfoHeader.biCompression = BI_RGB;
	stBmpInfoHeader.biClrUsed = 0;
	stBmpInfoHeader.biSizeImage = nBytesPerLine * sizeWindow.cy;

	PVOID pvBits = NULL;
	HBITMAP hbmpMem = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, &pvBits, NULL, 0);

	HGDIOBJ hbmpOld = ::SelectObject(hdcMemory, hbmpMem);
	POINT ptWinPos = { rcWindow.left, rcWindow.top };

	Gdiplus::Graphics graph(hdcMemory);
	graph.SetSmoothingMode(Gdiplus::SmoothingModeNone);
	graph.DrawImage(pImage, 0, 0, sizeWindow.cx, sizeWindow.cy);
	graph.FillRectangle(&SolidBrush(Color::Gray), 0, 0, 100, 50); 

	HMODULE hFuncInst = LoadLibrary(TEXT("User32.DLL"));
	typedef BOOL(WINAPI* MYFUNC)(HWND, HDC, POINT*, SIZE*, HDC, POINT*, COLORREF, BLENDFUNCTION*, DWORD);
	MYFUNC UpdateLayeredWindow;
	UpdateLayeredWindow = (MYFUNC)::GetProcAddress(hFuncInst, "UpdateLayeredWindow");
	POINT ptSrc = { 0, 0 };
	BLENDFUNCTION blendFunc;
	blendFunc.BlendOp = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 1;
	blendFunc.SourceConstantAlpha = 255;
	if (!UpdateLayeredWindow(m_hWnd, hDC, &ptWinPos, &sizeWindow, hdcMemory, &ptSrc, 0, &blendFunc, ULW_ALPHA)) {
			throw "UpdateLayeredWindow error";
	}


	delete pImage;
	graph.ReleaseHDC(hdcMemory);
	graph.SetSmoothingMode(SmoothingModeHighQuality);
	::SelectObject(hdcMemory, hbmpOld);

	::DeleteObject(hFuncInst);
	::DeleteObject(hbmpOld);
	::DeleteObject(hbmpMem);
	::DeleteDC(hdcMemory);
	::DeleteDC(hDC);
}
LRESULT WINAPI VWigetProc(HWND hWnd, UINT uInt,
	WPARAM wpaRam, LPARAM lpAram) {
	VStringList url;
	bool ftwmpaint = false,ftwmstray = false, ftwmclose = false;
	int twmstray_pos = 0,twmclose_pos = 0;
	for (size_t i = 0; i < FTWM_SLOT.size(); i++) {
		if (FTWM_SLOT[i].aimsId == hWnd) {
			url.push_back(FTWM_SLOT[i].url);
			ftwmpaint = true;
		}
	}
	for (size_t i = 0; i < FTWMTRAY_SLOT.size(); i++) {
		if (FTWMTRAY_SLOT[i].amisId == hWnd) {
			ftwmstray = true;
			twmstray_pos = i;
		}
	}
	for (size_t i = 0; i < FTWMCLOSE_SLOT.size(); i++) {
		if (FTWMCLOSE_SLOT[i].amisId == hWnd) {
			ftwmclose = true;
			twmclose_pos = i;
		}
	}
	switch (uInt) {
	case WM_DESTROY:
		if (ftwmstray == true) DeleteTray(hWnd, FTWMTRAY_SLOT[twmstray_pos]);
		PostQuitMessage(NULL);
		return DefWindowProc(hWnd, uInt,
			wpaRam, lpAram);
	case WM_CLOSE:
		if (ftwmclose == true) {
			FTWMCLOSE_SLOT[twmclose_pos].event();
			ShowWindow(hWnd, SW_SHOW);
			return (LRESULT)"Nope";
		}
		break;
	case WM_SIZE:
		if (wpaRam == SIZE_MINIMIZED) {
			VWidgetEventStruct ev;
			ev.aimsId = hWnd;
			ev.event = VWidgetEvent::VeraWindowSmall;
			VWidgetEventVector.push_back(ev);
			if (ftwmstray == true) {
				ToTray(hWnd, FTWMTRAY_SLOT[twmstray_pos]);
			}
		}
		else if (wpaRam == SIZE_MAXIMIZED) {
			VWidgetEventStruct ev;
			ev.aimsId = hWnd;
			ev.event = VWidgetEvent::VeraWindowMax;
			VWidgetEventVector.push_back(ev);
		}
		else {
			VWidgetEventStruct ev;
			ev.aimsId = hWnd;
			ev.event = VWidgetEvent::VeraSizeChange;
			VWidgetEventVector.push_back(ev);
		}
		break;
	case WM_SHOWTASK :
		if (lpAram == WM_LBUTTONDBLCLK) {
			ShowWindow(hWnd, SW_SHOWNORMAL);
		}
		break;
	case WM_LBUTTONDOWN:
		VWidgetEventStruct ev_;
		ev_.aimsId = hWnd;
		ev_.event = VWidgetEvent::VeraMouseCheak;
		VWidgetEventVector.push_back(ev_);
		break;
	case WM_PAINT:
		if (ftwmpaint == true) {
			std::wstring cvrt = url[url.size() - 1].toStdWstring();
#ifdef MSVC_2017
			setGround(hWnd, (LPCSTR)cvrt.c_str());
#else
			setGround(hWnd, cvrt.c_str());
#endif
		}
		break;
	}
	return DefWindowProc(hWnd, uInt,
		wpaRam, lpAram);
}