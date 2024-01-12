// WindowsProject1.cpp : Определяет точку входа для приложения.
//
#include "framework.h"
#include "WindowsProject1.h"
#include <ctime>
#include <winnt.h>
#include <windows.h>
#include <MMSystem.h>
#include <Iostream>
#pragma comment(lib, "winmm.lib")
using namespace std;
#define AMOUNT 30

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int x_coords[AMOUNT];
int y_coords[AMOUNT];
bool wings[AMOUNT];
HBRUSH bgBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
bool oficer_show = false;
bool oficer_go = false;
bool oficer_hunt = true;
int x_oficer = 0;
bool side = true;
bool hunt = true;
bool second = true;
bool extra_wing = false;
int extra_x = x_oficer + 120;
int extra_y = 260;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	return (int)msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		400, 100, 800, 560, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}



HBRUSH hPurpleBrush, hPinkBrush, hBlueBrush, hBluBrush, hWhiteBrush, hGreenBrush, hYellowBrush, hBackBrush, hGrayBrush;

HPEN hPurplePen, hPinkPen, hBluePen, hBluPen, hWhitePen, hBrownPen2, hBlackPen, hGreenPen, hYellowPen, hGrayPen;

void PaintPole(HDC hdc, bool flag)
{
	SelectObject(hdc, hBluePen);
	SelectObject(hdc, hBlueBrush);
	Rectangle(hdc, 0, 0, 800, 700);

	
	if (flag) {
		SelectObject(hdc, hYellowPen);
		SelectObject(hdc, hYellowBrush);
		Ellipse(hdc, 700, -50, 850, 100);


		MoveToEx(hdc, 595, 20, NULL);
		LineTo(hdc, 675, 20);

		

		MoveToEx(hdc, 625, 115, NULL);
		LineTo(hdc, 687, 75);

		

		MoveToEx(hdc, 735, 110, NULL);
		LineTo(hdc, 715, 180);

	}
	else {
		SelectObject(hdc, hYellowPen);
		SelectObject(hdc, hYellowBrush);
		Ellipse(hdc, 725, -25, 825, 75);

		MoveToEx(hdc, 600, 65, NULL);
		LineTo(hdc, 680, 50);

		MoveToEx(hdc, 670, 160, NULL);
		LineTo(hdc, 705, 95);


		MoveToEx(hdc, 765, 115, NULL);
		LineTo(hdc, 765, 185);
	}
	

	SelectObject(hdc, hGreenPen);
	SelectObject(hdc, hGreenBrush);
	Rectangle(hdc, 0, 400, 800, 700);
}
void PaintBabochka(HDC hdc, int x, int y, bool flag)
{
	SelectObject(hdc, hPinkPen);
	if (flag)
	{
		MoveToEx(hdc, x - 5, y - 10, NULL);
		LineTo(hdc, x, y);
		LineTo(hdc, x + 5, y - 10);
	}
	else
	{
		SelectObject(hdc, hPurplePen);
	
		MoveToEx(hdc, x - 5, y + 10, NULL);
		LineTo(hdc, x, y);
		LineTo(hdc, x + 5, y + 10);
	}
}
void PaintRomashka(HDC hdc, int x, int y, bool flag)
{
	int p = 5;
	if(flag){
		SelectObject(hdc, hGreenPen);
		SelectObject(hdc, hYellowBrush);
		int R = 17, r = 8, l = 50;
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x + p, y - l - 10);

		SelectObject(hdc, hGrayPen);
		Ellipse(hdc, x - 10 + p, y - l - 10, x + 10 + p, y - l + 10);
		SelectObject(hdc, hGrayBrush);
		Ellipse(hdc, x - r + p, y - l - R - r, x + r + p, y - l - R + r);
		Ellipse(hdc, x + p - 0.951 * R - r, y - l - 0.309 * R - r, x + p - 0.951 * R + r, y - l - 0.309 * R + r);
		Ellipse(hdc, x + p + 0.951 * R - r, y - l - 0.309 * R - r, x + p + 0.951 * R + r, y - l - 0.309 * R + r);
		Ellipse(hdc, x + p - 0.588 * R - r, y - l + 0.809 * R - r, x + p - 0.588 * R + r, y - l + 0.809 * R + r);
		Ellipse(hdc, x + p + 0.588 * R - r, y - l + 0.809 * R - r, x + p + 0.588 * R + r, y - l + 0.809 * R + r);
	}
	else {
		SelectObject(hdc, hGreenPen);
		SelectObject(hdc, hYellowBrush);
		int R = 17, r = 8, l = 50;
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x - p, y - l - 10);

		SelectObject(hdc, hGrayPen);
		Ellipse(hdc, x - p - 10, y - l - 10, x + 10, y - l + 10);
		SelectObject(hdc, hGrayBrush);
		Ellipse(hdc, x - p - r, y - l - R - r, x - p + r, y - l - R + r);
		Ellipse(hdc, x - p - 0.951 * R - r, y - l - 0.309 * R - r, x - p - 0.951 * R + r, y - l - 0.309 * R + r);
		Ellipse(hdc, x - p + 0.951 * R - r, y - l - 0.309 * R - r, x - p + 0.951 * R + r, y - l - 0.309 * R + r);
		Ellipse(hdc, x - p - 0.588 * R - r, y - l + 0.809 * R - r, x - p - 0.588 * R + r, y - l + 0.809 * R + r);
		Ellipse(hdc, x - p + 0.588 * R - r, y - l + 0.809 * R - r, x - p + 0.588 * R + r, y - l + 0.809 * R + r);

	}
	
}
void PaintOficer(HDC hdc, int x, int y, bool side, bool hunt)
{
	SelectObject(hdc, hGreenPen);
	MoveToEx(hdc, x - 30, y, NULL);
	LineTo(hdc, x, y - 40);
	LineTo(hdc, x + 30, y);
	MoveToEx(hdc, x, y - 40, NULL);
	LineTo(hdc, x, y - 100);
	MoveToEx(hdc, x - 30, y - 50, NULL);
	LineTo(hdc, x, y - 90);
	LineTo(hdc, x + 30, y - 50);
	
	SelectObject(hdc, hYellowPen);
	SelectObject(hdc, hYellowBrush);
	Arc(hdc, x - 20, y - 140, x + 20, y - 100, x - 15, y - 135, x + 15, y - 135);


	SelectObject(hdc, hGreenPen);
	SelectObject(hdc, hGreenBrush);
	
	MoveToEx(hdc, x, y - 150, NULL);
	LineTo(hdc, x + 15, y - 135);
	LineTo(hdc, x + 9, y - 129);
	LineTo(hdc, x, y - 127);
	LineTo(hdc, x - 9, y - 129);
	LineTo(hdc, x - 15, y - 135);
	LineTo(hdc, x, y - 150);
	LineTo(hdc, x, y - 136);


	SelectObject(hdc, hGrayPen);
	SelectObject(hdc, hGrayBrush);
	if (side)
	{

		
		MoveToEx(hdc, x + 30, y - 50, NULL);
		if (hunt)
		{
			

			LineTo(hdc, x + 80, y - 170);
			Arc(hdc, x + 75 - 13, y - 170 + 12 - 13, x + 75 + 13, y - 170 + 12 + 13, x + 80, y - 170, x + 30, y - 50);
		}
		else
		{
			LineTo(hdc, x + 160, y - 50);
			Arc(hdc, x + 160 - 26, y - 50 - 13, x + 160, y - 50 + 13, x + 160, y - 50, x - 30, y - 50);
		}
	}
	else
	{
		MoveToEx(hdc, x - 30, y - 50, NULL);
		if (hunt)
		{
			LineTo(hdc, x - 80, y - 170);
			Arc(hdc, x - 75 - 13, y - 170 + 12 - 13, x - 75 + 13, y - 170 + 12 + 13, x - 30, y - 50, x - 80, y - 170);
		}
		else
		{
			LineTo(hdc, x - 160, y - 50);
			Arc(hdc, x - 160 + 26, y - 50 - 13, x - 160, y - 50 + 13, x - 30, y - 50, x - 160, y - 50);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{

		// -----------------  Pen Color  -----------------

		hPurplePen = CreatePen(PS_SOLID, 3, RGB(83, 64, 198));
		hPinkPen = CreatePen(PS_SOLID, 3, RGB(212, 76, 213));
		hBlackPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		hGreenPen = CreatePen(PS_SOLID, 3, RGB(78, 215, 82));
		hYellowPen = CreatePen(PS_SOLID, 3, RGB(215, 145, 57));
		hBluePen = CreatePen(PS_SOLID, 3, RGB(85, 209, 215));
		hGrayPen = CreatePen(PS_SOLID, 3, RGB(204, 206, 207));

		// -----------------  Brush Color  -----------------

		hBackBrush = CreateSolidBrush(RGB(209, 241, 255));
		hPurpleBrush = CreateSolidBrush(RGB(123, 104, 238));
		hGreenBrush = CreateSolidBrush(RGB(118, 255, 122));
		hPinkBrush = CreateSolidBrush(RGB(252, 116, 253));
		hBlueBrush = CreateSolidBrush(RGB(125, 249, 255));
		hYellowBrush = CreateSolidBrush(RGB(234, 255, 0));
		hGrayBrush = CreateSolidBrush(RGB(240, 240, 240));


		SetTimer(hWnd, 1111, 30, NULL);
		SetTimer(hWnd, 2222, 200, NULL);
		srand(time(NULL));
		for (unsigned short int i = 0; i < AMOUNT; i++)
		{
			x_coords[i] = rand() % 601 + 100;
			y_coords[i] = rand() % 301 + 50;
			wings[i] = rand() % 2;
		}
		
		PlaySound(L"Ирина.WAV", NULL, SND_FILENAME | SND_ASYNC);
		
	}
	case WM_ERASEBKGND:
		return (LRESULT)1; // Say we handled it.

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HDC hdcmem = CreateCompatibleDC(hdc);
		HBITMAP buffer = CreateCompatibleBitmap(hdc, 800, 500);
		SelectObject(hdcmem, buffer);
		RECT r;
		GetClientRect(hWnd, &r);
		SetRect(&r, 0, 0, 800, 500);
		FillRect(hdcmem, &r, bgBrush);
		PaintPole(hdcmem, extra_wing);
		for (unsigned short int i = 0; i < 8; i++)
			PaintRomashka(hdcmem, 50 + 100 * i, 485, extra_wing);
		for (unsigned short int i = 0; i < AMOUNT; i++)
			PaintBabochka(hdcmem, x_coords[i], y_coords[i], wings[i]);
		if (oficer_show)
		{
			PaintOficer(hdcmem, x_oficer, 400, side, hunt);
			PaintBabochka(hdcmem, extra_x, extra_y, extra_wing);
		}
		BitBlt(hdc, 0, 0, 800, 500, hdcmem, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1111:
		{
			for (unsigned int i = 0; i < AMOUNT; i++)
			{
				x_coords[i] += rand() % 11 - 5;
				y_coords[i] += rand() % 11 - 5;
				if (x_coords[i] <= 50)
					x_coords[i] = 50 + rand() % 10;
				if (x_coords[i] >= 750)
					x_coords[i] = 750 - rand() % 10;
				if (y_coords[i] <= 0)
					y_coords[i] = rand() % 10;
				if (y_coords[i] >= 350)
					y_coords[i] = 350 - rand() % 10;
			}
			if (oficer_show)
			{
				if (oficer_go)
				{
					if (side)
					{
						x_oficer += 8;
						extra_x += 8;
						if (x_oficer >= 600)
						{
							side = false;
							extra_x = x_oficer - 120;
						}
					}
					else
					{
						x_oficer -= 8;
						extra_x -= 8;
						if (x_oficer <= 200)
						{
							side = true;
							extra_x = x_oficer + 120;
						}
					}
				}
				else
				{
					hunt = false;
					if (side)
						extra_x = x_oficer + 145;
					else
						extra_x = x_oficer - 145;
					extra_y = 350;
				}
			}
			InvalidateRect(hWnd, NULL, true);
			break;
		}
		case 2222:
		{
			for (unsigned short int i = 0; i < AMOUNT; i++)
				wings[i] = !wings[i];
			extra_wing = !extra_wing;
			InvalidateRect(hWnd, NULL, true);
			break;
		}
		}
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_SPACE:
		{
			if (second)
			{
				oficer_show = true;
				oficer_go = true;
				second = false;
			}
			else
				oficer_go = false;
			break;
		}
		}
		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 1111);
		KillTimer(hWnd, 2222);
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

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
