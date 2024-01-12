// Project1.cpp : Определяет точку входа для приложения.
//
//ДВА ВЕРХНИХ ИНКЛЮДА БЫЛИ НЕ СРАЗУ, А МЫ ПОДКЛЮЧИЛИ
#include<windows.h>
#include<windowsx.h>
#include "framework.h"
#include "svetafor.h"
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst; // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING]; // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING]; // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
    // 
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SVETAFOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SVETAFOR));
    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

//
// ФУНКЦИЯ: MyRegisterClass()
//
// ЦЕЛЬ: Регистрирует класс окна.
//

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SVETAFOR));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SVETAFOR);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

//
// ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
// ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
// КОММЕНТАРИИ:
//
// В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
// создается и выводится главное окно программы.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd)
    {
        return FALSE;
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

//
// ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
// ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
// WM_COMMAND - обработать меню приложения
// WM_PAINT - Отрисовка главного окна
// WM_DESTROY - отправить сообщение о выходе и вернуться
//
//

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    return LineTo(hdc, x2, y2);
}
void DrawMyObject(HDC hdc, int iPos);
RECT rect;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    PAINTSTRUCT ps;
    int iPos = rect.right / 5;
    switch (message)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rect);
        break;
    case WM_SIZE:
        GetClientRect(hWnd, &rect);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        DrawMyObject(hdc, iPos);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HBRUSH hBrownBrush, hRedBrush, hBlueBrush, hBluBrush, hWhiteBrush;
HPEN hBrownPen, hRedPen, hBluePen, hBluPen, hWhitePen, hBrownPen2, hBlackPen;
//ФУНКЦИЯ, КОТОРАЯ РИСУЕТ НАШ ОБЪЕКТ


void DrawMyObject(HDC hdc, int iPos)
{
    hWhiteBrush = GetStockBrush(WHITE_BRUSH);
    hWhiteBrush = CreateSolidBrush(RGB(238, 223, 230));
    SelectObject(hdc, hWhiteBrush);
    POINT ptk[5] = {
        {iPos / 99, rect.bottom * 9999},
        {rect.right, rect.bottom / 999},
        {rect.right / 9999, rect.bottom / 9999},
        {rect.left * 1000, rect.bottom * 1000},
        {iPos / 99, rect.bottom * 9999},
    };
    Polygon(hdc, ptk, 5);/////////заливка
    DeleteObject(hWhitePen);

    hBluePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));//контур внутренего прям
    hBlueBrush = CreateSolidBrush(RGB(130, 130, 130));//внутрен прям

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    POINT pt6[5] = { {iPos + rect.right * 18 / 100,rect.bottom * 5 / 100},
  {iPos + rect.right * 38 / 100,rect.bottom * 5 / 100},
  {iPos + rect.right * 38 / 100,rect.bottom * 95 / 100},
  {iPos + rect.right * 18 / 100,rect.bottom * 95 / 100},
  { iPos + rect.right * 18 / 100,rect.bottom * 5 / 100} };
    Polygon(hdc, pt6, 5);//ЗАЛІВКА ПРЯМОУГ

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);



    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЗЕЛЕНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 70 / 100, iPos + rect.right * 33 / 100, rect.bottom * 90 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);


    //




    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 52, 63));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 245, 143));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);





    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);



    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(163, 255, 158));//ЗЕЛЕНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 70 / 100, iPos + rect.right * 33 / 100, rect.bottom * 90 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);


    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЗЕЛЕНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 70 / 100, iPos + rect.right * 33 / 100, rect.bottom * 90 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);




    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 245, 143));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 52, 63));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);



    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 52, 63));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 245, 143));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);





    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);



    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(163, 255, 158));//ЗЕЛЕНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 70 / 100, iPos + rect.right * 33 / 100, rect.bottom * 90 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);


    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЗЕЛЕНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 70 / 100, iPos + rect.right * 33 / 100, rect.bottom * 90 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);




    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 245, 143));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 52, 63));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);


    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 52, 63));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 245, 143));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);





    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);



    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(163, 255, 158));//ЗЕЛЕНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 70 / 100, iPos + rect.right * 33 / 100, rect.bottom * 90 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);


    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЗЕЛЕНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 70 / 100, iPos + rect.right * 33 / 100, rect.bottom * 90 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);




    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 245, 143));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(0, 0, 0));//ЖЕЛТЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 40 / 100, iPos + rect.right * 33 / 100, rect.bottom * 60 / 100);

    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);

    hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));//КОНТУР ОВАЛА-ЧЕРНЫЙ
    hBlueBrush = CreateSolidBrush(RGB(255, 52, 63));//КРАСНЫЙ ОВАЛ

    SelectObject(hdc, hBluePen);
    SelectObject(hdc, hBlueBrush);

    Ellipse(hdc, iPos + rect.right * 23 / 100, rect.bottom * 10 / 100, iPos + rect.right * 33 / 100, rect.bottom * 30 / 100);
    Sleep(1000);
    DeleteObject(hBluePen);
    DeleteObject(hBlueBrush);



};

// Обработчик сообщений для окна "О программе".
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
