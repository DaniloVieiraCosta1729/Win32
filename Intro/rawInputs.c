#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <locale.h>
#include "rawProc.h"

LRESULT CALLBACK wProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR argvWin, int nCmdShow)
{
    setlocale(LC_ALL, "");

    const wchar_t CLASS_NAME[] = L"Raw Input";
    WNDCLASS wc = {0};
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = wProcedure;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Aprendendo Raw Input",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL)
    {
        MessageBoxW(NULL, L"Error in Creating the Window", L"Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    RAWINPUTDEVICE rid = {0};
    rid.hwndTarget = hwnd;
    rid.dwFlags = RIDEV_INPUTSINK;
    rid.usUsagePage = 1;
    rid.usUsage = 2; // for mouse
    RegisterRawInputDevices(&rid, 1, sizeof(rid));
    
    MSG msg = {0};
    while (1)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return 0;
            }
            
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        InvalidateRect(hwnd, NULL, FALSE);
        Sleep(1);
    }
    
    return 0;        
}