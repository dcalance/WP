#ifndef UNICODE
#define UNICODE
#endif 

#include <string.h>
#include <tchar.h>
#include <windows.h>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

										// Position and Size
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);


	HWND button1 = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"OK",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		10,         // y position 
		100,        // Button width
		100,        // Button height
		hwnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	HWND button2 = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"DILDO",      // Button text 
		WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,  // Styles 
		10,         // x position 
		120,         // y position 
		100,        // Button width
		100,        // Button height
		hwnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//case WM_CLOSE:
		//	if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		//	{
		//		DestroyWindow(hwnd);
		//	}
		//	// Else: User canceled. Do nothing.
		//	return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_SIZE:
			InvalidateRect(hwnd, 0, TRUE);
			return 0;

		case WM_PAINT:
		{
			RECT rc;
			GetClientRect(hwnd, &rc);
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			LPWSTR message = L"Hello";
			DrawText(hdc, message, -1, &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			EndPaint(hwnd, &ps);
		}
		return 0;

		case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT Item;
			Item = (LPDRAWITEMSTRUCT)lParam;
			SelectObject(Item->hDC, CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Consolas"));
			FillRect(Item->hDC, &Item->rcItem, CreateSolidBrush(0));
			SelectObject(Item->hDC, CreateSolidBrush(0));
			if (Item->itemState & ODS_SELECTED)
			{
				SetTextColor(Item->hDC, 0);
				SelectObject(Item->hDC, CreateSolidBrush(0xFF00));
				SelectObject(Item->hDC, CreatePen(PS_SOLID, 2, 0xFF00));
			}
			else
			{
				SetTextColor(Item->hDC, 0x00FF00);
				SelectObject(Item->hDC, CreatePen(PS_SOLID, 2, 0x00FF00));

			}
			SetBkMode(Item->hDC, TRANSPARENT);
			RoundRect(Item->hDC, Item->rcItem.left, Item->rcItem.top, Item->rcItem.right, Item->rcItem.bottom, 20, 20);
			int len;
			len = GetWindowTextLength(Item->hwndItem);
			LPSTR lpBuff;
			lpBuff = new char[len + 1];
			GetWindowTextA(Item->hwndItem, lpBuff, len + 1);
			DrawTextA(Item->hDC, lpBuff, len, &Item->rcItem, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
