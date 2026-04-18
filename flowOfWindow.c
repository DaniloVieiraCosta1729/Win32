#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <locale.h>

LRESULT CALLBACK myCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        MessageBoxW(NULL, L"A janela será fechada.", L"Fechando...", MB_OK);
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        PAINTSTRUCT paintStruct = {};
        HDC hdc = BeginPaint(hwnd, &paintStruct);

        FillRect(hdc, &paintStruct.rcPaint, (HBRUSH)(COLOR_HIGHLIGHT+1));

        RECT rectangle = {0};
        rectangle.bottom = 30;
        rectangle.left = 40;
        rectangle.top = 100;
        rectangle.right = 90;

        RECT biggerR = {0};
        biggerR.bottom = 110;
        biggerR.left = 100;
        biggerR.right = 250;
        biggerR.top = 260;

        FillRect(hdc, &rectangle, (HBRUSH)(COLOR_WINDOW+1));

        HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
        FillRect(hdc, &biggerR, brush);

        EndPaint(hwnd, &paintStruct);

        return 0;

    case WM_LBUTTONDOWN:
        int x = (int)(short)LOWORD(lParam); // The coordinates are of type WORD (unsigned 16 bits), but semantically, we should look at this as a 16-bit signed integer, so to obtain the right interpretation, we should cast it to short. The int is just to keep things standard.
        int y = (int)(short)HIWORD(lParam);

        wchar_t position[256];
        wsprintf(position, L"Clique na posição (%d, %d)", x, y);
        MessageBoxW(hwnd, position, L"Posição", MB_OK);
        return 0;
    
    default:
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR argvWind, int nCmdShow)
{
    setlocale(LC_ALL, "");

    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = myCallback;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME, 
        L"Learning Win32", 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL 
    );

    if (hwnd == NULL)
    {
        MessageBoxW(NULL, L"Error in creating the window.", L"Error", MB_OK);
        Sleep(2000);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
    
}