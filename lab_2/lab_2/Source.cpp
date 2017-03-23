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


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lpCmdLine, int nCmdShow) {

	MSG  msg;
	WNDCLASSW wc = { 0 };
	wc.lpszClassName = L"Simple menu";
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
	
	CreateWindowEx(
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
	

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	LPCSTR a ,b;
	HBITMAP hBitmap01;

	switch (msg) {

	case WM_SIZE:
		InvalidateRect(hwnd, NULL, 1);
		break;
	
	case WM_PAINT:
		PAINTSTRUCT     ps;
		HDC             hdc;
		BITMAP          bitmap;
		HDC             hdcMem;
		HGDIOBJ         oldBitmap;
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
		//BitBlt(hdc, 0, 0,rect.right, rect.bottom, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);

		EndPaint(hwnd, &ps);
		break;
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

	case WM_CREATE:

		AddMenus(hwnd);
		RegisterHotKey(hwnd, ID_HOTKEY_PAUSE, MOD_CONTROL, 'D');
		RegisterHotKey(hwnd, ID_HOTKEY_CHANGEBG, MOD_SHIFT, ' ');



		break;
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
			// User clicked the scroll bar shaft left of the scroll box. 
		case SB_PAGEUP:
			
			break;

			// User clicked the scroll bar shaft right of the scroll box. 
		case SB_PAGEDOWN:
			
			break;

			// User clicked the left arrow. 
		case SB_LINEUP:
			
			break;

			// User clicked the right arrow. 
		case SB_LINEDOWN:
			
			break;

			// User dragged the scroll box. 
		case SB_THUMBPOSITION:
			
			break;

		}
		break;
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
