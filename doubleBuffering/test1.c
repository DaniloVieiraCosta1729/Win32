#include <windows.h>
#include <locale.h>

// definitions
#define SIDESQUARE 50

// global variables
HBRUSH wndBrush = {0};
HBRUSH squareBrush = {0};
HDC backDC = NULL;
HBITMAP backBitmap = NULL;
int bufferWidth;
int bufferHeight;
int mouseX;
int mouseY;

LRESULT CALLBACK renderProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR argvW, int nCmdShow)
{
    setlocale(LC_ALL, "");
    
    const wchar_t CLASS_NAME[] = L"Graphics Stuff";
    WNDCLASS wc = {0};
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = renderProc;
    wc.hInstance = hInstance;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"I'm the Graphics Lord Now",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
    );
    if (!hwnd)
    {
        MessageBoxW(NULL, L"Something went wrong when creating the window.", L"Error", MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);

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

LRESULT CALLBACK renderProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    switch (nMsg)
    {
        case WM_CLOSE:
        {
            if (MessageBox(hwnd, L"Posso fechar mesmo?", L"SEKIRO", MB_OKCANCEL) == IDOK)
            {
                DestroyWindow(hwnd);
            }            

            return 0;
        }
        
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps = {0};
            HDC hdc = BeginPaint(hwnd, &ps);
            
            wndBrush = CreateSolidBrush(RGB(255, 0,0));
            RECT rect = {0, 0, bufferWidth, bufferHeight};
            FillRect(backDC, &rect, wndBrush);

            RECT mouseSquare = {mouseX, mouseY, mouseX + SIDESQUARE, mouseY + SIDESQUARE};
            COLORREF squareColor = RGB((((mouseX % 256) + 256) % 256), ((((mouseX + mouseX)/2) % 256) + 256) % 256, (((mouseY % 256) + 256) % 256));
            squareBrush = CreateSolidBrush(squareColor);
            FillRect(backDC, &mouseSquare, squareBrush);

            BitBlt(hdc, 0, 0, bufferWidth, bufferHeight, backDC, 0, 0, SRCCOPY);
            
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_SIZE:
        {
            bufferHeight = HIWORD(lParam);
            bufferWidth = LOWORD(lParam);

            HDC hdc = GetDC(hwnd);

            if (backDC)
            {
                DeleteObject(backBitmap);
                DeleteDC(backDC);
            }

            backDC = CreateCompatibleDC(hdc);
            backBitmap = CreateCompatibleBitmap(hdc, bufferWidth, bufferHeight);
            SelectObject(backDC, backBitmap);
            
            ReleaseDC(hwnd, hdc);
            return 0;
        }

        case WM_ERASEBKGND:
            return 1;

        case WM_MOUSEMOVE:
        {
            mouseX = (int)(short)LOWORD(lParam);
            mouseY = (int)(short)HIWORD(lParam);
        }
        
        default:
            break;
    }

    return DefWindowProc(hwnd, nMsg, wParam, lParam);
}