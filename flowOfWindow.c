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

        EndPaint(hwnd, &paintStruct);

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