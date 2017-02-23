#ifndef UNICODE
#define UNICODE
#endif 

#define ID_EDITCHILD 100
#define ID_EDITCHILD2 101
#define BUTTON_ID1 102
#define BUTTON_ID2 103

#include <string.h>
#include <tchar.h>
#include <windows.h>
#include <time.h>

LPWSTR message = L"Done by Calancea Daniel";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = {};
	srand(time(NULL));
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Program Title",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

										// Position and Size
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);


	
	

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
	HFONT hFont;
	LPWSTR editMesage = L"Lorem ipsum dolor sit amet, consectetur ";
	switch (uMsg)
	{
	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_MINIMIZE:
			MoveWindow(hwnd, rand() % 500, rand() % 500, rand() % 500, rand() % 500, FALSE);
			ShowWindow(hwnd, SW_SHOW);
			return 0;

		case SC_MAXIMIZE:
			if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hwnd);
			}
			return 0;

		case SC_CLOSE:
			PlaySound(TEXT("DeviceConnect"), NULL, SND_ASYNC);
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	
	case WM_CREATE:
		static HWND button1 = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Change Window Name",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			10,         // y position 
			180,        // Button width
			50,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_ID1,       // No menu.
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		static HWND button2 = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Change Message",      // Button text 
			WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,  // Styles 
			10,         // x position 
			80,         // y position 
			180,        // Button width
			50,        // Button height
			hwnd,     // Parent window
			(HMENU)BUTTON_ID2,       // No menu.
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		static HWND hwndEdit;
		hwndEdit = CreateWindowEx(
			0, L"EDIT",   // predefined class 
			NULL,         // no window title 
			WS_CHILD | WS_VISIBLE | WS_VSCROLL |
			ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			80, 100, 150, 17,   // set size in WM_SIZE message 
			hwnd,         // parent window 
			(HMENU)ID_EDITCHILD,   // edit control ID 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);        // pointer not needed 
		hFont = CreateFont(0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Courier New"));
		SendMessage(hwndEdit, WM_SETFONT, (WPARAM)hFont, 0);
		SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)editMesage);

		static HWND hwndEdit2;
		hwndEdit2 = CreateWindowEx(
			0, L"EDIT",   // predefined class 
			NULL,         // no window title 
			WS_CHILD | WS_VISIBLE | WS_VSCROLL |
			ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			80, 100, 150, 17,   // set size in WM_SIZE message 
			hwnd,         // parent window 
			(HMENU)ID_EDITCHILD2,   // edit control ID 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);        // pointer not needed 

						  // Add text to the window. 
		SendMessage(hwndEdit2, WM_SETTEXT, 0, (LPARAM)editMesage);
		return 0;
	
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		if (GetDlgItem(hwnd, ID_EDITCHILD) == (HWND)lParam)
		{
			SetTextColor(hdc, RGB(255, 255, 255)); // Set text color to white
			SetBkColor(hdc, RGB(0, 0, 0)); // Set background color to black
		}
		return 0;
	}

	case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	case WM_SIZE:
			InvalidateRect(hwnd, 0, TRUE);
			
			MoveWindow(hwndEdit,
				200, 0,                  // starting x- and y-coordinates 
				200,        // width of client area 
				100,        // height of client area 
				TRUE);                 // repaint window 

			MoveWindow(hwndEdit2,
				200, 100,                  // starting x- and y-coordinates 
				100,        // width of client area 
				100,        // height of client area 
				TRUE);                 // repaint window 
			return 0;

	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			if (GetDlgItem(hwnd, BUTTON_ID1) == (HWND)lParam)
			{
				SetWindowText(hwnd, L"Oh yeaaa");
			}
			if (GetDlgItem(hwnd, BUTTON_ID2) == (HWND)lParam)
			{
				message = L"Message changed.";
				InvalidateRect(hwnd, 0, TRUE);
			}
			break;
		}
		return 0;
	case WM_PAINT:
		{
			RECT rc;
			GetClientRect(hwnd, &rc);
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			DrawText(hdc, message, -1, &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			EndPaint(hwnd, &ps);
		}
		return 0;

	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT Item;
			Item = (LPDRAWITEMSTRUCT)lParam;
			SelectObject(Item->hDC, CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Calibri"));
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
