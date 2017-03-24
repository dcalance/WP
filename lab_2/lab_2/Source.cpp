#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
bool ChangeVolume(double nVolume, bool bScalar);
void AddMenus(HWND);

bool currentBackground = true;

#define IDM_FILE_DNTPRESS 1
#define IDM_FILE_QUIT 3
#define IDM_FILE_ABOUT 4

#define ID_HOTKEY_PAUSE 100
#define ID_HOTKEY_CHANGEBG 101

#define ID_SCROLLBAR 400

WNDCLASSW wc;
HWND scrollhwnd;
SCROLLINFO si;

int clientX = 0;
int clientY = 0;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lpCmdLine, int nCmdShow) {

	MSG  msg;
	WNDCLASSW wc = { 0 };
	wc.lpszClassName = L"Window";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	HWND hwnd = CreateWindowW(
		wc.lpszClassName, 
		L"Window",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 
		100, 
		640, 
		480, 
		0, 
		0, 
		wc.hInstance, 
		0);
	
	scrollhwnd = CreateWindowEx(
		0,                      // no extended styles 
		"SCROLLBAR",           // scroll bar control class 
		(PTSTR)NULL,           // no window text 
		WS_CHILD | WS_VISIBLE   // window styles  
		| SBS_HORZ,         // horizontal scroll bar style 
		0,              // horizontal position 
		10,				// vertical position 
		500,             // width of the scroll bar 
		20,               // height of the scroll bar
		hwnd,             // handle to main window 
		(HMENU)ID_SCROLLBAR,           // no menu 
		hInstance,      // instance owning this window 
		(PVOID)NULL            // pointer not needed 
	);
	
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;
	si.nMax = 20;
	si.nMin = 0;
	si.nPage = 1;
	si.nPos = 0;
	SetScrollInfo(scrollhwnd, SB_CTL, &si, 1);


	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	LPCSTR a ,b;
	HBITMAP hBitmap01;
	int id;
	HDC wdc;
	HFONT font;
	HFONT hFontOld;
	int iVertPos, iHorzPos;

	switch (msg) {

	case WM_SIZE:
		RECT rect1;
		int cxClient, cyClient;
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		
		if (cyClient < 480)
		{
			ShowScrollBar(hwnd, SB_VERT, 1);
		}
		else
		{
			ShowScrollBar(hwnd, SB_VERT, 0);
		}

		if (cxClient < 640)
		{
			ShowScrollBar(hwnd, SB_HORZ, 1);
		}
		else
		{
			ShowScrollBar(hwnd, SB_HORZ, 0);
		}

		

		/*si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		si.nMax = 6400 / (int)cxClient + 1;
		si.nMin = 0;
		si.nPage = 1;
		si.nPos = 0;
		SetScrollInfo(hwnd, SB_HORZ, &si, 1);

		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		si.nMax = 4800 / (int)cyClient + 1;
		si.nMin = 0;
		si.nPage = 1;
		si.nPos = 0;
		SetScrollInfo(hwnd, SB_VERT, &si, 1);*/

		InvalidateRect(hwnd, NULL, 1);
		return 0;
	
	case WM_PAINT:
		PAINTSTRUCT     ps;
		HDC             hdc;
		BITMAP          bitmap;
		HDC             hdcMem;
		HGDIOBJ         oldBitmap;

		// Get vertical scroll bar position

		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		GetScrollInfo(hwnd, SB_VERT, &si);
		iVertPos = si.nPos;

		// Get horizontal scroll bar position

		GetScrollInfo(hwnd, SB_HORZ, &si);
		iHorzPos = si.nPos;


		if (currentBackground)
		{
			hBitmap01 = (HBITMAP)LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		else
		{
			hBitmap01 = (HBITMAP)LoadImage(NULL, "cosmos.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		

		RECT rect;
		GetClientRect(hwnd, &rect);
		hdc = BeginPaint(hwnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap01);
		
		GetObject(hBitmap01, sizeof(bitmap), &bitmap);
		StretchBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		
		
		SelectObject(hdcMem, oldBitmap);
		wdc = GetWindowDC(hwnd);
		GetScrollInfo(scrollhwnd, SB_CTL, &si);
		SetTextColor(wdc, RGB(si.nPos * 15, si.nPos * 20, si.nPos * 25));
		SetBkMode(wdc, TRANSPARENT);
		
		font = CreateFont(50, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
		hFontOld = (HFONT)SelectObject(wdc, font);
		GetWindowRect(hwnd, &rect);
		rect.left = 40;
		rect.top = 100;
		DrawText(wdc, "This text is magic.", -1, &rect, DT_SINGLELINE | DT_NOCLIP);
		
		DeleteObject(font);
		DeleteObject(hFontOld);
		DeleteObject(hdcMem);
		DeleteObject(oldBitmap);
		DeleteObject(hBitmap01);
		DeleteDC(wdc);
		DeleteDC(hdc);
		
		EndPaint(hwnd, &ps);

		return 0;
	case WM_HOTKEY:
		switch (wParam)
		{
		case ID_HOTKEY_PAUSE:
			mciSendString("stop song1", NULL, 0, 0);
			break;
		case ID_HOTKEY_CHANGEBG:
			currentBackground = !currentBackground;
			InvalidateRect(hwnd, NULL, 1);
			break;
		}
		break;

	case WM_CREATE:

		AddMenus(hwnd);
		RegisterHotKey(hwnd, ID_HOTKEY_PAUSE, MOD_CONTROL, 'D');
		RegisterHotKey(hwnd, ID_HOTKEY_CHANGEBG, MOD_SHIFT, ' ');
		

		break;
	case WM_HSCROLL:
		id = GetDlgCtrlID((HWND)lParam);
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd, SB_HORZ, &si);
		switch (id)
		{
		case ID_SCROLLBAR:
			
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;
			GetScrollInfo(scrollhwnd, SB_CTL, &si);
			
			switch (LOWORD(wParam))
			{
					// User clicked the left arrow.
				case SB_LINELEFT:
					si.nPos -= 1;
					break;

					// User clicked the right arrow.
				case SB_LINERIGHT:
					si.nPos += 1;
					break;

					// User clicked the scroll bar shaft left of the scroll box.
				case SB_PAGELEFT:
					si.nPos -= si.nPage;
					break;

					// User clicked the scroll bar shaft right of the scroll box.
				case SB_PAGERIGHT:
					si.nPos += si.nPage;
					break;

					// User dragged the scroll box.
				case SB_THUMBTRACK:
					si.nPos = si.nTrackPos;
					break;

				default:
					break;
			}

			si.fMask = SIF_ALL;
			SetScrollInfo(scrollhwnd, SB_CTL, &si, 1);
			InvalidateRect(hwnd, NULL, 1);
			return 0;
		//default:
		//	iHorzPos = si.nPos;
		//	switch (LOWORD(wParam))
		//	{

		//		// User clicked the left arrow.

		//	case SB_LINELEFT:
		//		si.nPos -= 1;
		//		break;

		//		// User clicked the right arrow.
		//	case SB_LINERIGHT:
		//		si.nPos += 1;
		//		break;

		//		// User clicked the scroll bar shaft left of the scroll box.
		//	case SB_PAGELEFT:
		//		si.nPos -= si.nPage;
		//		break;

		//		// User clicked the scroll bar shaft right of the scroll box.
		//	case SB_PAGERIGHT:
		//		si.nPos += si.nPage;
		//		break;

		//		// User dragged the scroll box.
		//	case SB_THUMBTRACK:
		//		si.nPos = si.nTrackPos;
		//		break;
		//	}

		//	si.fMask = SIF_POS;
		//	SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		//	GetScrollInfo(hwnd, SB_HORZ, &si);

		//	// If the position has changed, scroll the window 

		//	if (si.nPos != iHorzPos)
		//	{
		//		ScrollWindow(hwnd, iHorzPos - si.nPos , 0,
		//			NULL, NULL);
		//		UpdateWindow(hwnd);
		//	}
		//	return 0;
		}
		
		return 0;

	//case WM_VSCROLL:
	//	// Get all the vertical scroll bar information

	//	si.cbSize = sizeof(si);
	//	si.fMask = SIF_ALL;
	//	GetScrollInfo(hwnd, SB_VERT, &si);

	//	// Save the position for comparison later on
	//	iVertPos = si.nPos;

	//	switch (LOWORD(wParam))
	//	{
	//	case SB_TOP:
	//		si.nPos = si.nMin;
	//		break;

	//	case SB_BOTTOM:
	//		si.nPos = si.nMax;
	//		break;

	//	case SB_LINEUP:
	//		si.nPos -= 1;
	//		break;

	//	case SB_LINEDOWN:
	//		si.nPos += 1;
	//		break;

	//	case SB_PAGEUP:
	//		si.nPos -= si.nPage;
	//		break;

	//	case SB_PAGEDOWN:
	//		si.nPos += si.nPage;
	//		break;

	//	case SB_THUMBTRACK:
	//		si.nPos = si.nTrackPos;
	//		break;

	//	default:
	//		break;
	//	}
	//	// Set the position and then retrieve it.  Due to adjustments
	//	//   by Windows it may not be the same as the value set.

	//	si.fMask = SIF_POS;
	//	SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
	//	GetScrollInfo(hwnd, SB_VERT, &si);

	//	// If the position has changed, scroll the window and update it

	//	if (si.nPos != iVertPos)
	//	{
	//		ScrollWindow(hwnd, 0,iVertPos - si.nPos,
	//			NULL, NULL);
	//		UpdateWindow(hwnd);
	//	}
	//	return 0;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case IDM_FILE_ABOUT:
			MessageBox(
				NULL,
				"Don't touch my program.\n I am watching you.",
				"Goddamnit",
				MB_ICONWARNING | MB_OK
			);
			break;
		case IDM_FILE_DNTPRESS:
			ChangeVolume(1.0, 0);
			a = "open DingDongSong.mp3 type mpegvideo alias song1";
			mciSendString(a, NULL, 0, 0);
			b = "play song1";
			mciSendString(b, NULL, 0, 0);
			break;

		case IDM_FILE_QUIT:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}

		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}

	

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void AddMenus(HWND hwnd) {

	HMENU hMenubar;
	HMENU hMenu;
	HMENU hMenu2;

	hMenubar = CreateMenu();
	hMenu = CreateMenu();
	hMenu2 = CreateMenu();

	AppendMenuW(hMenu, MF_STRING, IDM_FILE_DNTPRESS, L"&Don't press it");
	AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Quit");

	AppendMenuW(hMenu2, MF_STRING, IDM_FILE_ABOUT, L"&About");

	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu2, L"&About");

	SetMenu(hwnd, hMenubar);
}

bool ChangeVolume(double nVolume, bool bScalar)
{

	HRESULT hr = NULL;
	bool decibels = false;
	bool scalar = false;
	double newVolume = nVolume;

	CoInitialize(NULL);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	// -------------------------
	float currentVolume = 0;
	endpointVolume->GetMasterVolumeLevel(&currentVolume);
	endpointVolume->SetMute(0, NULL);
	//printf("Current volume in dB is: %f\n", currentVolume);

	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
	//CString strCur=L"";
	//strCur.Format(L"%f",currentVolume);
	//AfxMessageBox(strCur);

	// printf("Current volume as a scalar is: %f\n", currentVolume);
	if (bScalar == false)
	{
		hr = endpointVolume->SetMasterVolumeLevel((float)newVolume, NULL);
	}
	else if (bScalar == true)
	{
		hr = endpointVolume->SetMasterVolumeLevelScalar((float)newVolume, NULL);
	}
	endpointVolume->Release();

	CoUninitialize();

	return FALSE;
}
