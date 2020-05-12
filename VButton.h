#pragma once
#define _CRTDBG_MAP_ALLOC
#ifndef GCL_HCURSOR
#define GCL_HCURSOR         (-12)
#endif
#if defined _M_IX86  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#elif defined _M_X64  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#else  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#endif
#include "VWidget.h"
#include "VApplication.h"

LRESULT WINAPI VButtonProc(HWND hWnd, UINT uInt,
	WPARAM wpaRam, LPARAM lpAram);


class VButton {
private:
	HWND winId = NULL;
	HWND ButtonHwnd = NULL;
	HWND w_parent;
	VString btnstring;

	long long btn_Id;

	std::vector<std::function<void()> >Chlik;

	std::thread pw_thread;

	VSize w_size;

	bool close = false;
	bool run_b = false;

	void creativeWindow();
	
	bool isClose() { return close; }

	void run_f() {
		while (true) {
			if (isClose() == true) break;
		}

		run_b = true;
	}

	_public enum class corStyle {
		Wait,
		No,
		Arrow,
		Ibeam,
		Cross,
#if(WINVER >= 0x0500)
		Hand,
#endif
#if(WINVER >= 0x0400)
		Help,
#endif
		Appstarting,
#if(WINVER >= 0x0606)
		Pin,
		Person,
#endif 
		Fromfile,
	};

	_public VButton(VWidget* parent = NULL);

	_public void setWindowName(VString name);
	_public void setGeometry(size_t x, size_t y, size_t w, size_t h);
	_public void setGeometry(VSize size);
	_public void setFont(size_t h,size_t w, bool Italic,bool Underline,bool Strikethrough,VString fontName);
	_public void setFont(HFONT font);
#ifdef MSVC_2017
	_public void setCursor(LPCSTR style);
#else
	_public void setCursor(LPCWSTR style);
#endif
	_public void setCurosr(corStyle style,VString filename = "");
	_public void setBackgroundFromPicture(VString size);
	_public void append(VString string);
	_public void setIcon(VString iconUrl);
	_public void setIcon(VString iconUrl,size_t w,size_t h);
	_public void setState(bool flag);

	_public void connect(std::function<void()>function, VButtonEvent event);

	_public void resize(size_t w, size_t h);

	_public void enable();
	_public void unenable();

	_public void move(size_t x, size_t y);

	_public void setParent(VWidget* parent);
	_public void setParent(HWND parent);

	_public wId getwId();

	_public VString toPlaneText();

	_public int run();
	_public void run_detach();

	_public void show();
	_public void hide();

	_public void _delete();
};

wId VButton::getwId() {
	wId retu(ButtonHwnd);
	return retu;
}

void VButton::setState(bool flag) {
	SendMessage(ButtonHwnd,BM_SETSTATE,(WPARAM)flag,0);
}

VString VButton::toPlaneText() {
#ifdef MSVC_2017
	int len = static_cast<int>(SendMessage(ButtonHwnd, WM_GETTEXTLENGTH, 0, 0));

	wchar_t *buffer = new wchar_t[len + 1];

	SendMessage(ButtonHwnd, WM_GETTEXT, (WPARAM)(len + 1), (LPARAM)buffer);

	VString str;
	str.fromStdWstring((std::wstring)buffer);
#else
	int len = static_cast<int>(SendMessage(ButtonHwnd, WM_GETTEXTLENGTH, 0, 0));

	TCHAR *buffer = new TCHAR[len + 1];

	SendMessage(ButtonHwnd, WM_GETTEXT, (WPARAM)(len + 1), (LPARAM)buffer);

	VString str;
	str.fromStdWstring(buffer);
#endif
	delete[] buffer;
	return str;
}

void VButton::append(VString string) {
	VString btn = btnstring;
	std::string tn = btn.toStdString() + string.toStdString();
	btn.fromStdString(tn);
	btnstring = btn;
	setWindowName(btn);
}

void VButton::setCurosr(VButton::corStyle style, VString filename) {
	if (style == VButton::corStyle::Arrow) {
		SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)IDC_ARROW));
	}
	if (style == VButton::corStyle::Appstarting) {
		SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)IDC_APPSTARTING));
	}
	if (style == VButton::corStyle::Cross) {
		SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)IDC_CROSS));
	}
#if(WINVER >= 0x0500)
	if (style == VButton::corStyle::Hand) {
		SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)IDC_HAND));
	}
#endif
#if(WINVER >= 0x0400)
	if (style == VButton::corStyle::Help) {
		SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)IDC_HAND));
	}
#endif
	if (style == VButton::corStyle::Ibeam) {
		SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)IDC_IBEAM));
	}
	if (style == VButton::corStyle::No) {
		SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)IDC_NO));
	}
#if(WINVER >= 0x0606)
	if (style == VButton::corStyle::Person) {
		SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)IDC_PERSON));
	}
	if (style == VButton::corStyle::Pin) {
		SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)IDC_PIN));
	}
#endif
	if (style == VButton::corStyle::Fromfile) {
		std::wstring fln = filename.toStdWstring();
#ifdef MSVC_2017
		SetClassLong(winId, GCL_HCURSOR, (LONG)LoadCursorFromFile((LPCSTR)fln.c_str()));
#else
		SetClassLong(winId, GCL_HCURSOR, (LONG)LoadCursorFromFile(fln.c_str()));
#endif
	}
}

void VButton::setBackgroundFromPicture(VString url) {
	HBITMAP	hBmp;
	std::wstring tmp = url.toStdWstring();
#ifdef MSVC_2017
	hBmp = (HBITMAP)LoadImage(GetModuleHandleA(NULL), (LPCSTR)tmp.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
#else
	hBmp = (HBITMAP)LoadImage(GetModuleHandleA(NULL), tmp.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
#endif
	SendMessage(ButtonHwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
}

void VButton::setIcon(VString iconUrl, size_t w, size_t h) {
	std::wstring cvt = iconUrl.toStdWstring();
	HICON hIcon;
#ifdef MSVC_2017
	hIcon = (HICON)LoadImage(NULL, (LPCSTR)cvt.c_str(), IMAGE_ICON, w, h, LR_LOADFROMFILE);
#else
	hIcon = (HICON)LoadImage(NULL, cvt.c_str(), IMAGE_ICON, w, h, LR_LOADFROMFILE);
#endif
	SendMessage(ButtonHwnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
}

void VButton::setIcon(VString iconUrl) {
	std::wstring cvt = iconUrl.toStdWstring();
	HICON hIcon;
#ifdef MSVC_2017
	hIcon = (HICON)LoadImage(NULL, (LPCSTR)cvt.c_str(), IMAGE_ICON, 24, 24, LR_LOADFROMFILE);
#else
	hIcon = (HICON)LoadImage(NULL, cvt.c_str(), IMAGE_ICON, 24, 24, LR_LOADFROMFILE);
#endif
	SendMessage(ButtonHwnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
}

#ifdef MSVC_2017
void VButton::setCursor(LPCSTR style) {
	SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)style));
}
#else
void VButton::setCursor(LPCWSTR style) {
	SetClassLong(winId, GCL_HCURSOR, (LONG)::LoadCursorA(NULL, (LPCSTR)style));
}
#endif

void VButton::setFont(size_t h, size_t w, bool Italic, bool Underline, bool Strikethrough, VString fontName) {
	HDC hdc = ::GetDC(ButtonHwnd);
	std::wstring cvt = fontName.toStdWstring();
	HFONT font = CreateFont(
		h, w, 0, 0, 400,
		Italic, Underline, Strikethrough,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY,
		FF_DONTCARE,
#ifdef MSVC_2017
		(LPCSTR)cvt.c_str()
#else
		cvt.c_str()
#endif
	);
	SendMessage(ButtonHwnd,WM_SETFONT,(WPARAM)font,NULL);
}
void VButton::setFont(HFONT font) {
	SendMessage(ButtonHwnd, WM_SETFONT, (WPARAM)font, NULL);
}

void VButton::enable() {
	EnableWindow(ButtonHwnd, true);
}
void VButton::unenable() {
	EnableWindow(ButtonHwnd, false);
}

void VButton::setParent(VWidget* parent) {
	SetParent(winId, parent->getwId().windowId());
	show();
}
void VButton::setParent(HWND parent) {
	SetParent(winId, parent);
	show();
}

void VButton::run_detach() {
	std::thread run_t(&VButton::run,this);
	run_t.detach();
}

void VButton::connect(std::function<void()>function, VButtonEvent event) {
	if (event == VButtonEvent::VeraClick) Chlik.push_back(function);
}

void VButton::move(size_t x, size_t y) {
	hide();
	w_size._x = x;
	w_size._y = y;
	MoveWindow(winId, x, y, w_size._w, w_size._h, FALSE);
	show();
}

void VButton::resize(size_t w, size_t h) {
	hide();
	w_size._w = w;
	w_size._h = h;
	MoveWindow(winId, w_size._x, w_size._y, w, h, FALSE);
	MoveWindow(ButtonHwnd, w_size._x, w_size._y, w, h, FALSE);
	show();
}

void VButton::setGeometry(size_t x, size_t y, size_t w, size_t h) {
	w_size._x = x;
	w_size._y = y;
	w_size._h = h;
	w_size._w = w;
	MoveWindow(winId, x, y, w, h, 0);
}
void VButton::setGeometry(VSize size) {
	w_size._x = size._x;
	w_size._y = size._y;
	w_size._h = size._h;
	w_size._w = size._w;
	MoveWindow(winId, size._x, size._y, size._w, size._h, 0);
}

void VButton::setWindowName(VString name) {
#ifdef MSVC_2017
	btnstring = name;
 	SendMessage(ButtonHwnd, WM_SETTEXT, NULL, (LPARAM)name.c_str());
#else
	btnstring = name;
	SendMessage(ButtonHwnd, WM_SETTEXT, NULL, (LPARAM)name.toStdWstring().c_str());
#endif
}

int VButton::run() {
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	::SendMessage(ButtonHwnd, WM_SETFONT, (WPARAM)hFont, 1);
	int getSize = 0;
	size_t vectsize[2] = { 0 };
	while (true) {
		vectsize[0] = VButtonEventVector.size();
		if (vectsize[0] > vectsize[1]) {
			if (VButtonEventVector[vectsize[0] - 1].aimsId == btn_Id) {
				if (VButtonEventVector.at(vectsize[0] - 1).event == VButtonEvent::VeraClick) {
					for (size_t i = 0; i < Chlik.size(); i++) {
						Chlik[i]();
						VButtonEventVector.pop_back();
					}
				}
			}
		}
		if (isClose() == true) break;
		vectsize[1] = VButtonEventVector.size();
		Sleep(80);
	}
	return 0;
}

void VButton::_delete() {
	pw_thread.detach();
}

void VButton::show() {
	ShowWindow(winId, SW_SHOW);
}

void VButton::hide() {
	ShowWindow(winId, SW_HIDE);
}

VButton::VButton(VWidget* parent) {
	if (parent != NULL) w_parent = parent->getwId().windowId();
	else w_parent = NULL;
	pw_thread = std::thread(&VButton::creativeWindow, this);
	while (true) if (winId != NULL) {
		Sleep(80);
		break;
	}
	pw_thread.detach();
}
 

void VButton::creativeWindow() {
	btn_Id = button_case;
	button_case++;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	WNDCLASSEX wc;
	MSG msg;
	HWND hwnd;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = VButtonProc;
	wc.cbClsExtra = wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT(" ");
	wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(NULL,
		wc.lpszClassName,
		wc.lpszClassName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		80,
		80,
		NULL,
		NULL,
		hInstance,
		NULL);
	UpdateWindow(hwnd);
	winId = hwnd;
	resize(80,80);
#ifdef MSVC_2017
	ButtonHwnd = CreateWindow((LPCSTR)"Button", (LPCSTR)" ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_FLAT,
		0, 0, 80, 80, hwnd, (HMENU)btn_Id, GetModuleHandle(NULL), NULL);
#else
	ButtonHwnd = CreateWindow(L"Button", L" ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_FLAT,
		0, 0, 80, 80, hwnd, (HMENU)btn_Id, GetModuleHandle(NULL), NULL);
#endif
	UpdateWindow(ButtonHwnd);
	ShowWindow(ButtonHwnd, SW_SHOW);
	SetParent(ButtonHwnd, winId);
	RECT rect;
	GetWindowRect(winId, &rect);
	w_size._x = rect.left;
	w_size._y = rect.top;
	w_size._w = rect.right;
	w_size._h = rect.bottom;
	LONG_PTR Style = ::GetWindowLongPtr(winId, GWL_STYLE);
	Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
	::SetWindowLongPtr(winId, GWL_STYLE, Style);
	if (w_parent != NULL) {
		setParent(w_parent);
		show();
	}
	run_detach();
	while (true) {
		if (!GetMessage(&msg, 0, 0, 0))break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	close = true;
}

LRESULT WINAPI VButtonProc(HWND hWnd, UINT uInt,
	WPARAM wpaRam, LPARAM lpAram) {
	VStringList url;
	bool flag = false;
	for (size_t i = 0; i < FTWM_SLOT.size(); i++) {
		if (FTWM_SLOT[i].aimsId == hWnd) {
			url.push_back(FTWM_SLOT[i].url);
			flag = true;
		}
	}
	switch (uInt) {
	case WM_DESTROY:
		PostQuitMessage(NULL);
		return DefWindowProc(hWnd, uInt,
			wpaRam, lpAram);
	case WM_COMMAND:
		VButtonEventStruct ev_;
		ev_.aimsId = (WPARAM)wpaRam;
		ev_.event = VButtonEvent::VeraClick;
		VButtonEventVector.push_back(ev_);
		return DefWindowProc(hWnd, uInt, wpaRam, lpAram);
		break;
	case WM_PAINT:
		if (flag == true) {
			std::wstring cvrt = url[url.size() - 1].toStdWstring();
#ifdef MSVC_2017
			setGround(hWnd, (LPCSTR)cvrt.c_str());
#else
			setGround(hWnd, cvrt.c_str());
#endif
		}
		break;
	}
	return DefWindowProc(hWnd, uInt, wpaRam, lpAram);
}