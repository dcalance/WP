#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);

#define IDM_FILE_DNTPRESS 1
#define IDM_FILE_QUIT 3
#define IDM_FILE_ABOUT 4

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
	CreateWindowW(wc.lpszClassName, L"Simple menu",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 350, 250, 0, 0, hInstance, 0);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	LPCSTR a ,b;

	switch (msg) {

	case WM_CREATE:

		AddMenus(hwnd);
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