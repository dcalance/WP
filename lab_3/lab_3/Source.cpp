
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
#include <list>
using namespace Gdiplus;
using namespace std;
#pragma comment (lib,"Gdiplus.lib")

#define ID_RED 100
#define ID_GREEN 101
#define ID_BLUE 102

#define ID_LINE 200
#define ID_CIRCLE 201
#define ID_SQUARE 202
#define ID_PIE 203
#define ID_POLY 204

bool clickWasPressed = false;
typedef struct POINTS2
{
	long x1;
	long y1;
	long x2;
	long y2;
	string type;
	int r;
	int g;
	int b;
	
}POINTS2;

list<POINTS2> pointList;


VOID OnPaint(RECT rect, HDC hdc, list<POINTS2> pointL)
{
	
	Graphics graphics(hdc);
	for (list<POINTS2>::iterator it = pointL.begin(); it != pointL.end(); it++)
	{
		
		Pen pen(Color(255, it->r, it->g, it->b));
		if (it->type == "line")
		{
			graphics.DrawLine(&pen, it->x1, it->y1, it->x2, it->y2);
		}

	}
	
}

void CreateCheckBoxes(HWND hwnd, HINSTANCE instance)
{
	CreateWindowEx(NULL, "button", "Red", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 10, 600, 100, 20, hwnd, (HMENU) ID_RED, instance, NULL);
	CreateWindowEx(NULL, "button", "Green", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 110, 600, 100, 20, hwnd, (HMENU) ID_GREEN, instance, NULL);
	CreateWindowEx(NULL, "button", "Blue", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 210, 600, 100, 20, hwnd, (HMENU)ID_BLUE, instance, NULL);
}

void CreateButtons(HWND hwnd, HINSTANCE instance)
{
	CreateWindowEx(NULL, "BUTTON", "Line", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 560, 100, 20, hwnd, (HMENU)ID_LINE, instance, NULL);
	CreateWindowEx(NULL, "BUTTON", "Square", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 535, 100, 20, hwnd, (HMENU)ID_SQUARE, instance, NULL);
	CreateWindowEx(NULL, "BUTTON", "Circle", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 510, 100, 20, hwnd, (HMENU)ID_CIRCLE, instance, NULL);
	CreateWindowEx(NULL, "BUTTON", "Pie", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 485, 100, 20, hwnd, (HMENU)ID_PIE, instance, NULL);
	CreateWindowEx(NULL, "BUTTON", "Polygon", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 460, 100, 20, hwnd, (HMENU)ID_POLY, instance, NULL);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);
	CreateCheckBoxes(hWnd, hInstance);
	CreateButtons(hWnd, hInstance);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;
	static POINT p1;
	static POINT p2;
	RECT rect;
	
	switch (message)
	{
	case WM_MOUSEMOVE:
		if (clickWasPressed)
		{
			if (GetCursorPos(&p2))
			{
				ScreenToClient(hWnd, &p2);
				POINTS2 el;
				el.x1 = p1.x;
				el.y1 = p1.y;
				el.x2 = p2.x;
				el.y2 = p2.y;
				el.type = "line";
				el.r = IsDlgButtonChecked(hWnd, ID_RED) * 255;
				el.g = IsDlgButtonChecked(hWnd, ID_GREEN) * 255;
				el.b = IsDlgButtonChecked(hWnd, ID_BLUE) * 255;
				pointList.push_back(el);
				InvalidateRect(hWnd, NULL, 1);
			}
		}
		return 0;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_POLY:
			if (!IsDlgButtonChecked(hWnd, ID_POLY))
			{
				CheckDlgButton(hWnd, ID_POLY, BST_CHECKED);
			}
			else
			{
				CheckDlgButton(hWnd, ID_POLY, BST_UNCHECKED);
			}
			return 0;
		case ID_RED:
			if (!IsDlgButtonChecked(hWnd, ID_RED))
			{
				CheckDlgButton(hWnd, ID_RED, BST_CHECKED);
			}
			else
			{
				CheckDlgButton(hWnd, ID_RED, BST_UNCHECKED);
			}
			return 0;
		case ID_BLUE:
			if (!IsDlgButtonChecked(hWnd, ID_BLUE))
			{
				CheckDlgButton(hWnd, ID_BLUE, BST_CHECKED);
			}
			else
			{
				CheckDlgButton(hWnd, ID_BLUE, BST_UNCHECKED);
			}
			return 0;
		case ID_GREEN:
			if (!IsDlgButtonChecked(hWnd, ID_GREEN))
			{
				CheckDlgButton(hWnd, ID_GREEN, BST_CHECKED);
			}
			else
			{
				CheckDlgButton(hWnd, ID_GREEN, BST_UNCHECKED);
			}
			return 0;
		}
		return 0;
	case WM_LBUTTONDOWN:
		if (!clickWasPressed)
		{
			if (GetCursorPos(&p1))
			{
				clickWasPressed = true;
				ScreenToClient(hWnd, &p1);
			}
		}
		else
		{
			if (GetCursorPos(&p2))
			{
				ScreenToClient(hWnd, &p2);
				POINTS2 el;
				el.x1 = p1.x;
				el.y1 = p1.y;
				el.x2 = p2.x;
				el.y2 = p2.y;
				el.type = "line";
				el.r = IsDlgButtonChecked(hWnd, ID_RED) * 255;
				el.g = IsDlgButtonChecked(hWnd, ID_GREEN) * 255;
				el.b = IsDlgButtonChecked(hWnd, ID_BLUE) * 255;
				pointList.push_back(el);
				InvalidateRect(hWnd, NULL, 1);
				clickWasPressed = false;
			}
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		OnPaint(rect, hdc, pointList);
		if (clickWasPressed)
		{
			pointList.pop_back();
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc