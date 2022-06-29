// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <string>
#include <gdiplus.h>

#define MAX_LOADSTRING 100
#define TMR_1 1
#define ID_LEVEL5BUTTON1				220
#define ID_LEVEL5BUTTON2				221
#define ID_LEVEL5BUTTON3				222
#define ID_LEVEL5BUTTON4				223
#define ID_LEVEL4BUTTON1				224
#define ID_LEVEL4BUTTON2				231
#define ID_LEVEL4BUTTON3				232
#define ID_LEVEL4BUTTON5				233
#define ID_LEVEL3BUTTON1				234
#define ID_LEVEL3BUTTON2				235
#define ID_LEVEL3BUTTON4				236
#define ID_LEVEL3BUTTON5				237
#define ID_LEVEL2BUTTON1				238
#define ID_LEVEL2BUTTON3				239
#define ID_LEVEL2BUTTON4				240
#define ID_LEVEL2BUTTON5				241
#define ID_LEVEL1BUTTON2				242
#define ID_LEVEL1BUTTON3				243
#define ID_LEVEL1BUTTON4				244
#define ID_LEVEL1BUTTON5				245
#define TMR_2 246
#define TMR_winda 226
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;
INT ilosc5, ilosc4, ilosc3, ilosc2, ilosc1;
// buttons
HWND hwndButton;
RECT drawArea2 = { 0, 0, 2000, 2000 };

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);

struct Person
{
	BOOL areYouIn = 0;
	INT startingPoint;
	INT destinationPoint;
	bool areYouThere = 0;
};

//wektor osoby
std::vector<Person> destination;
std::vector<Person> queue;
Person buff;
int col = 0;
int mass = 0;
int value_before = 600;
int level1 = 0;
int level2 = 0;
int level3 = 0;
int level4 = 0;
int level5 = 0;
int go = 0;
void MyOnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, col, 0, 255));
    Pen pen2(Color(255, 255, 255, 255));

    // piêtra
    graphics.DrawLine(&pen, 50, 150, 500, 150);
    graphics.DrawLine(&pen, 850, 300, 1300, 300);
    graphics.DrawLine(&pen, 50, 450, 500, 450);
    graphics.DrawLine(&pen, 850, 600, 1300, 600);
    graphics.DrawLine(&pen, 50, 750, 500, 750);

    // winda
    graphics.DrawRectangle(&pen, 500, 0, 350, 750);
	Bitmap bmp(L"the_guy.png");
	
	if (level1 == 1)
	{
		graphics.DrawImage(&bmp, 200 + 35 * (ilosc1 - 1), 715, 35, 35);
	}
	if (level2 == 1)
	{
		graphics.DrawImage(&bmp, 1101 - 35 * (ilosc2 - 1), 565, 35, 35);
	}
	if (level3 == 1)
	{
		graphics.DrawImage(&bmp, 200 + 35 * (ilosc3 - 1), 415, 35, 35);
	}
	if (level4 == 1)
	{
		graphics.DrawImage(&bmp, 1101 - 35 * (ilosc4 - 1), 265, 35, 35);
	}
	if (level5 == 1)
	{
		graphics.DrawImage(&bmp, 200 + 35 * (ilosc5 - 1), 115, 35, 35);
	}
    
	Bitmap bmp_blank(L"blank.png");
	graphics.DrawRectangle(&pen2, 510, 5 + value_before, 330, 145);
	graphics.DrawRectangle(&pen, 510, 5 + value, 330, 145);
	for (int i = 0; i < queue.size(); i++)
	{
		if (queue[i].areYouIn == 0)
		{
			if ((queue[i].startingPoint / 10) % 2 == 0)
				graphics.DrawImage(&bmp, 300, 100 + queue[i].startingPoint, 50, 50);
			else graphics.DrawImage(&bmp, 1150, 100 + queue[i].startingPoint, 50, 50);
		}
		else if ((queue[i].startingPoint / 10) % 2 == 0)
		{
			graphics.DrawImage(&bmp_blank, 300, 100 + queue[i].startingPoint, 50, 50);
		}
		else graphics.DrawImage(&bmp_blank, 1150, 100 + queue[i].startingPoint, 50, 50);

		if (queue[i].areYouIn == 1 && queue[i].areYouThere == 0)
		{
			graphics.DrawImage(&bmp, 530 + queue[i].startingPoint / 2.5, 100 + value, 50, 50);
		}
		if (queue[i].areYouThere == 1)
		{
			if ((queue[i].destinationPoint / 10) % 2 == 0)
				graphics.DrawImage(&bmp, 400, 100 + queue[i].destinationPoint, 50, 50);
			else graphics.DrawImage(&bmp, 1050, 100 + queue[i].destinationPoint, 50, 50);
		}
	}
	for (int i = 0; i < destination.size(); i++)
	{
		if (destination[i].areYouIn == 0)
		{
			if ((destination[i].startingPoint / 10) % 2 == 0)
				graphics.DrawImage(&bmp, 300, 100 + destination[i].startingPoint, 50, 50);
			else graphics.DrawImage(&bmp, 1150, 100 + destination[i].startingPoint, 50, 50);
		}
		else if ((destination[i].startingPoint / 10) % 2 == 0)
		{
			graphics.DrawImage(&bmp_blank, 300, 100 + destination[i].startingPoint, 50, 50);
		}
		else graphics.DrawImage(&bmp_blank, 1150, 100 + destination[i].startingPoint, 50, 50);
		if (destination[i].areYouIn == 1 && destination[i].areYouThere == 0)
		{
			graphics.DrawImage(&bmp, 530 + destination[i].startingPoint / 2.5, 100 + value, 50, 50);
		}
		if (destination[i].areYouThere == 1)
		{
			if ((destination[i].destinationPoint / 10) % 2 == 0)
				graphics.DrawImage(&bmp, 400, 100 + destination[i].destinationPoint, 50, 50);
			else graphics.DrawImage(&bmp, 1050, 100 + destination[i].destinationPoint, 50, 50);
		}
	}
    //gosciu
    graphics.DrawRectangle(&pen2, 510, 5 + value_before, 330, 145);
    graphics.DrawRectangle(&pen, 510, 5 + value, 330, 145);
    //menu
    std::string s = std::to_string(mass);
    char const* pchar = s.c_str();
    TextOut(hdc, 900, 0, L"Obci¹¿enie windy: ", 17);
    TextOutA(hdc, 950, 50, pchar, 3);
    value_before = value;
}

void MyOnPaint_action_getting_in(HDC hdc, Person passenger)
{

}
void MyOnPaint_action_getting_out(HDC hdc, Person passenger)
{

}

void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}

void repaintWindow_action_getting_in(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, Person passenger)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint_action_getting_in(hdc, passenger);
	EndPaint(hWnd, &ps);
}
void repaintWindow_action_getting_out(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea, Person passenger)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint_action_getting_out(hdc, passenger);
	EndPaint(hWnd, &ps);
}

int OnCreate(HWND window)
{
	return 0;
}

// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 600;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable


// main window
	hWnd = CreateWindow(szWindowClass, L"Projekt 4 - Winda", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	SetWindowPos(hWnd, 0, 0, 0, 1600, 900, SWP_FRAMECHANGED | SWP_NOMOVE);

	// guziki do windy V
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 2, 35, 35, hWnd, (HMENU)ID_LEVEL5BUTTON4, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 39, 35, 35, hWnd, (HMENU)ID_LEVEL5BUTTON3, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 76, 35, 35, hWnd, (HMENU)ID_LEVEL5BUTTON2, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 113, 35, 35, hWnd, (HMENU)ID_LEVEL5BUTTON1, GetModuleHandle(NULL), NULL);

	// guziki do windy IV
	hwndButton = CreateWindow(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1315, 150, 35, 35, hWnd, (HMENU)ID_LEVEL4BUTTON5, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1315, 187, 35, 35, hWnd, (HMENU)ID_LEVEL4BUTTON3, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1315, 224, 35, 35, hWnd, (HMENU)ID_LEVEL4BUTTON2, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1315, 261, 35, 35, hWnd, (HMENU)ID_LEVEL4BUTTON1, GetModuleHandle(NULL), NULL);

	// guziki do windy III
	hwndButton = CreateWindow(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 298, 35, 35, hWnd, (HMENU)ID_LEVEL3BUTTON5, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 335, 35, 35, hWnd, (HMENU)ID_LEVEL3BUTTON4, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 372, 35, 35, hWnd, (HMENU)ID_LEVEL3BUTTON2, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 409, 35, 35, hWnd, (HMENU)ID_LEVEL3BUTTON1, GetModuleHandle(NULL), NULL);

	// guziki do windy II
	hwndButton = CreateWindow(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1315, 446, 35, 35, hWnd, (HMENU)ID_LEVEL2BUTTON5, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1315, 483, 35, 35, hWnd, (HMENU)ID_LEVEL2BUTTON4, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1315, 520, 35, 35, hWnd, (HMENU)ID_LEVEL2BUTTON3, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1315, 557, 35, 35, hWnd, (HMENU)ID_LEVEL2BUTTON1, GetModuleHandle(NULL), NULL);

	// guziki do windy I
	hwndButton = CreateWindow(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 594, 35, 35, hWnd, (HMENU)ID_LEVEL1BUTTON5, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 631, 35, 35, hWnd, (HMENU)ID_LEVEL1BUTTON4, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 668, 35, 35, hWnd, (HMENU)ID_LEVEL1BUTTON3, GetModuleHandle(NULL), NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 705, 35, 35, hWnd, (HMENU)ID_LEVEL1BUTTON2, GetModuleHandle(NULL), NULL);

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
	RECT rc;
	HDC hdcMem;
	HBITMAP hbmMem, hbmOld;
	HBRUSH hbrBkGnd;
	HFONT hfntOld;
	// Get the size of the client rectangle.
	GetClientRect(hWnd, &rc);
	// Create a compatible DC.
	hdcMem = CreateCompatibleDC(lpPS->hdc);
	// Create a bitmap big enough for our client rectangle.
	hbmMem = CreateCompatibleBitmap(lpPS->hdc, rc.right - rc.left, rc.bottom - rc.top);
	// Select the bitmap into the off-screen DC.
	hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);
	// Erase the background.
	hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);
	MyOnPaint(hdcMem);
	// Drawing goes here.
	HPEN hPenOld;
	HPEN hLinePen;
	COLORREF qLineColor;
	qLineColor = RGB(255, 0, 0);
	hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
	hPenOld = (HPEN)SelectObject(hdcMem, hLinePen);
	SelectObject(hdcMem, hPenOld);
	DeleteObject(hLinePen);
	
	BitBlt(lpPS->hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hdcMem, 0, 0, SRCCOPY);
	// Done with off-screen bitmap and DC.
	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	Person Osoba;

	RECT Client_Rect;
	GetClientRect(hWnd, &Client_Rect);
	int win_width = Client_Rect.right - Client_Rect.left;
	int win_height = Client_Rect.bottom + Client_Rect.left;
	HDC Memhdc;
	HBITMAP Membitmap;
	
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_LEVEL5BUTTON1:
			if (ilosc5 < 8)
			{
				ilosc5++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 0, 600,0};
				level5 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL5BUTTON2:
			if (ilosc5 < 8)
			{
				ilosc5++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 0, 450,0 };
				level5 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL5BUTTON3:
			if (ilosc5 < 8)
			{
				ilosc5++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 0, 300,0 };
				level5 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL5BUTTON4:
			if (ilosc5 < 8)
			{
				ilosc5++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 0, 150,0 };
				level5 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL4BUTTON5:
			if (ilosc4 < 8)
			{
				ilosc4++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 150, 0,0 };
				level4 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL4BUTTON3:
			if (ilosc4 < 8)
			{
				ilosc4++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 150, 300,0 };
				level4 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL4BUTTON2:
			if (ilosc4 < 8)
			{
				ilosc4++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 150, 450,0 };
				level4 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL4BUTTON1:
			if (ilosc4 < 8)
			{
				ilosc4++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 150, 600,0 };
				level4 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL3BUTTON5:
			if (ilosc3 < 8)
			{
				ilosc3++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 300, 0,0 };
				level3 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL3BUTTON4:
			if (ilosc3 < 8)
			{
				ilosc3++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 300, 150,0 };
				level3 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL3BUTTON2:
			if (ilosc3 < 8)
			{
				ilosc3++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 300, 450,0 };
				level3 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL3BUTTON1:
			if (ilosc3 < 8)
			{
				ilosc3++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 300, 600,0 };
				level3 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL2BUTTON5:
			if (ilosc2 < 8)
			{
				ilosc2++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 450, 0,0 };
				level2 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL2BUTTON4:
			if (ilosc2 < 8)
			{
				ilosc2++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 450, 150,0 };
				level2 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL2BUTTON3:
			if (ilosc2 < 8)
			{
				ilosc2++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 450, 300,0 };
				level2 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL2BUTTON1:
			if (ilosc2 < 8)
			{
				ilosc2++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 450, 600,0 };
				level2 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
			}
			break;
		case ID_LEVEL1BUTTON5:
			if (ilosc1 < 8)
			{
				ilosc1++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 600, 0,0 };
				level1 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
				SetTimer(hWnd, TMR_1, 15, 0);
			}
			break;
		case ID_LEVEL1BUTTON4:
			if (ilosc1 < 8)
			{
				ilosc1++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 600, 150,0 };
				level1 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
				SetTimer(hWnd, TMR_1, 15, 0);
			}
			break;
		case ID_LEVEL1BUTTON3:
			if (ilosc1 < 8)
			{
				ilosc1++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 600, 300,0 };
				level1 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
				SetTimer(hWnd, TMR_1, 15, 0);
			}
			break;
		case ID_LEVEL1BUTTON2:
			if (ilosc1 < 8)
			{
				ilosc1++;
				KillTimer(hWnd, 226);
				Osoba = { 0, 600, 450,0 };
				level1 = 1;
				destination.push_back(Osoba);
				SetTimer(hWnd, TMR_winda, 15, 0);
				SetTimer(hWnd, TMR_1, 15, 0);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Paint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		return (LRESULT)1; // Say we handled it.
	case WM_TIMER:
		switch (wParam)
		{
		case TMR_winda:
			//force window to repaint
			//if (value == 0 || value == 150 || value == 300 || value == 450 || value == 600) Sleep(2000);
			//for (int i = 0; i < destination.size(); i++)
			if (destination.size() > 0 && queue.size() == 0)
			{
				queue.push_back(destination[0]);
				destination.erase(destination.begin());
			}
			if (queue.size() > 0)
			{
				if (queue[0].areYouIn == 0)
				{
					repaintWindow(hWnd, hdc, ps, &drawArea2);
					if (value != queue[0].startingPoint)
					{
						if (value > queue[0].startingPoint)
						{
							value--;
						}
						else
						{
							value++;
						}
					}
					else
					{
						Sleep(2000);
						queue[0].areYouIn = 1;
						mass = mass + 70;
						//dej go do windy
					}
				}

				if (queue[0].destinationPoint != value && queue[0].areYouIn == 1)
				{
					repaintWindow(hWnd, hdc, ps, &drawArea2);
					if (value > queue[0].destinationPoint)
					{
						value--;
					}
					else
					{
						value++;
					}
				}
				else if (queue[0].destinationPoint == value && queue[0].areYouIn == 1)
				{
					Sleep(2000);
					queue[0].areYouThere = 1;
					mass = mass - 70;
					//kasuj goscia z windy
				}
				if (destination.size() > 0)
				{
					for (int i = 0; i < destination.size(); i++)
					{
						if (value < queue[0].destinationPoint)
						{
							if (value == destination[i].startingPoint && destination[i].areYouIn == 0 && destination[i].destinationPoint <= queue[0].destinationPoint)
							{
								destination[i].areYouIn = 1;
								mass = mass + 70;
								Sleep(2000);
								repaintWindow(hWnd, hdc, ps, &drawArea2);
							}
							else if (value == destination[i].startingPoint && destination[i].areYouIn == 0 && destination[i].destinationPoint > queue[0].destinationPoint)
							{
								destination[i].areYouIn = 1;
								mass = mass + 70;
								queue.push_back(destination[i]);
								Sleep(2000);
								repaintWindow(hWnd, hdc, ps, &drawArea2);
							}
							if (value == destination[i].destinationPoint && destination[i].areYouIn == 1)
							{
								destination[i].areYouThere = 1;
								mass = mass - 70;
								Sleep(2000);
								repaintWindow(hWnd, hdc, ps, &drawArea2);
							}
						}
						if (value > destination[0].destinationPoint)
						{
							if (value == destination[i].startingPoint && destination[i].areYouIn == 0 && destination[i].destinationPoint >= queue[0].destinationPoint)
							{
								destination[i].areYouIn = 1;
								mass = mass + 70;
								Sleep(2000);
								repaintWindow(hWnd, hdc, ps, &drawArea2);
							}
							else if (value == destination[i].startingPoint && destination[i].areYouIn == 0 && destination[i].destinationPoint < queue[0].destinationPoint)
							{
								destination[i].areYouIn = 1;
								mass = mass + 70;
								queue.push_back(destination[i]);
								Sleep(2000);
								repaintWindow(hWnd, hdc, ps, &drawArea2);
							}
							if (value == destination[i].destinationPoint && destination[i].areYouIn == 1)
							{
								destination[i].areYouThere = 1;
								mass = mass - 70;
								Sleep(2000);
								repaintWindow(hWnd, hdc, ps, &drawArea2);
							}
						}
					}
				}


				if (queue[0].areYouThere == 1)
				{
					queue.erase(queue.begin());
				}
			}
			for (int i = 0; i < destination.size(); i++)
			{
				if (destination[i].areYouThere == 1)
				{
					destination.erase(destination.begin() + i);
					i = 0;
				}
			}
			repaintWindow(hWnd, hdc, ps, &drawArea2);
			break;
		}
	case TMR_1:
		if (go <= 300) go=go+3;
		else KillTimer(hWnd, 1);
		break;
	case TMR_2:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
