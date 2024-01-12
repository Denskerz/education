// Project1.cpp : Определяет точку входа для приложения.
//
//ДВА ВЕРХНИХ ИНКЛЮДА БЫЛИ НЕ СРАЗУ, А МЫ ПОДКЛЮЧИЛИ
#include<windows.h>
#include<windowsx.h>
#include "framework.h"
#include "figury.h"
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
    LoadStringW(hInstance, IDC_FIGURY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIGURY));
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIGURY));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FIGURY);
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


HBRUSH hPurpleBrush, hPinkBrush, hBlueBrush, hBluBrush, hWhiteBrush, hGreenBrush, hYellowBrush;
HPEN hPurplePen, hPinkPen, hBluePen, hBluPen, hWhitePen, hBrownPen2, hBlackPen, hGreenPen, hYellowPen;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
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
    case WM_SIZE:
        static int cxCoord = LOWORD(lParam);
        static int cyCoord = HIWORD(lParam);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // ------------- Lines -----------

        SelectObject(hdc, hBlackPen);
        MoveToEx(hdc, cxCoord / 3, 0, 0); LineTo(hdc, cxCoord / 3, cyCoord);
        MoveToEx(hdc,  cxCoord * 2 / 3, 0, 0); LineTo(hdc, cxCoord * 2 / 3, cyCoord);
        MoveToEx(hdc, 0, (cyCoord) / 2, 0); LineTo(hdc, cxCoord, (cyCoord) / 2);

        // ------------- Text --------------

        wchar_t Txt1[] = L"Прямоугольник ";
        wchar_t Txt2[] = L"Квадрат ";
        wchar_t Txt3[] = L"Эллипс ";
        wchar_t Txt4[] = L"Сектор ";
        wchar_t Txt5[] = L"Правильный треугольник ";
        wchar_t Txt6[] = L"Ромб ";
        wchar_t Txt7[] = L"Ерошевич Денис Владимирович";

        SetTextColor(hdc, RGB(0, 0, 0));

        // ------------- Position of the text --------------

        TextOut(hdc, cxCoord / 3 / 2 - 49 -1, (cyCoord - (40 + 10)) / 2 - (20 + 5), Txt1, _tcslen(Txt1));
        TextOut(hdc, cxCoord / 2 - 30 , (cyCoord - (40 + 10)) / 2 - (20 + 5), Txt2, _tcslen(Txt2));
        TextOut(hdc, cxCoord * 5 / 6 - 25, (cyCoord - (40 + 10)) / 2 - (20 + 5), Txt3, _tcslen(Txt3));
        TextOut(hdc, cxCoord / 6 - 25, cyCoord  - 50, Txt4, _tcslen(Txt4));
        TextOut(hdc, cxCoord / 2 - 85, cyCoord - 50, Txt5, _tcslen(Txt5));
        TextOut(hdc, cxCoord * 5 / 6 - 15, cyCoord  - 50, Txt6, _tcslen(Txt6));
        TextOut(hdc, cxCoord - 235, cyCoord - 450, Txt7, _tcslen(Txt7));

        // ----------------   Rectangle   -----------------

        SelectObject(hdc, hPurplePen);
        SelectObject(hdc, hPurpleBrush);

        POINT p1[5] = { {30, 20},
            {270, 20},
            {270, 160},
            {30, 160 },
             {30, 20} };

        Polygon(hdc, p1, 4);//внутренний 
    
        // ------------------   Square   -------------------

        SelectObject(hdc, hGreenPen);
        SelectObject(hdc, hGreenBrush);

        Rectangle(hdc, cxCoord / 3 + 75, 20, cxCoord * 4 / 6 - 75, 155);


        // ------------------   Ellipse   -------------------

        SelectObject(hdc, hBluePen);
        SelectObject(hdc, hBlueBrush);

        Ellipse(hdc,  cxCoord * 3 / 4,  (cyCoord + 110) / 8, (11 * cxCoord - 100 ) / 12, (cyCoord * 3 - 200) / 8);


        // ------------------   Pie   -------------------

        SelectObject(hdc, hPinkPen);
        SelectObject(hdc, hPinkBrush);

        Pie(hdc, 60, 250, 350, 400, 20, 250, 20, 400);

        // ----------------   Triangle   -----------------
        
        SelectObject(hdc, hGreenPen);
        SelectObject(hdc, hGreenBrush);

        POINT p2[4] = { {cxCoord / 2, 250}, 
            {cxCoord / 2 + 90, 393}, 
            {cxCoord / 2 - 90, 393}, 
            {cxCoord / 2, 250} };

        Polygon(hdc, p2, 4);//внутренний 

        // ----------------   Rhombus   -----------------

        SelectObject(hdc, hYellowPen);
        SelectObject(hdc, hYellowBrush);

        POINT p3[5] = { {cxCoord * 5 / 6, 250},
            {cxCoord - 40, 315}, 
            {cxCoord * 5 / 6, 380}, 
            {cxCoord * 2 / 3 + 40, 315},
            {cxCoord * 5 / 6, 250} };

        Polygon(hdc, p3, 4);


        // ------------ Delete Pens and Brushes -----------

        DeleteObject(hPurplePen);
        DeleteObject(hPinkPen);
        DeleteObject(hBlackPen);
        DeleteObject(hYellowPen);
        DeleteObject(hBluePen);

        DeleteObject(hPurpleBrush);
        DeleteObject(hGreenBrush);
        DeleteObject(hPinkBrush);
        DeleteObject(hBlueBrush);
        DeleteObject(hYellowBrush);


        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CREATE:

        // -----------------  Pen Color  -----------------

        hPurplePen = CreatePen(PS_SOLID, 3, RGB(83, 64, 198));
        hPinkPen = CreatePen(PS_SOLID, 3, RGB(212, 76, 213));
        hBlackPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
        hGreenPen = CreatePen(PS_SOLID, 3, RGB(78, 215, 82));
        hYellowPen = CreatePen(PS_SOLID, 3, RGB(215, 145, 57));
        hBluePen = CreatePen(PS_SOLID, 3, RGB(85, 209, 215));

        // -----------------  Brush Color  -----------------

        hPurpleBrush = CreateSolidBrush(RGB(123, 104, 238));
        hGreenBrush = CreateSolidBrush(RGB(118, 255, 122));
        hPinkBrush = CreateSolidBrush (RGB(252, 116, 253));
        hBlueBrush = CreateSolidBrush(RGB(125, 249, 255));
        hYellowBrush = CreateSolidBrush(RGB(255, 185, 97));
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


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
