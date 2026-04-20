#ifndef UNICODE
#define UNICODE
#endif
#include "rawProc.h"
#include "stdlib.h"

#define SQUARE_SIZE 50

COLORREF bg = RGB(150, 150, 200);
int x = 10;
int y = 10;
int width = 10;
int height = 10;

LRESULT CALLBACK wProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        MessageBoxW(NULL, L"I guess I'm going.", L"Closing...", MB_OK);
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    
    case WM_PAINT:
        {
            PAINTSTRUCT paintStruct = {0};
            HDC hdc = BeginPaint(hwnd, &paintStruct);

            HBRUSH brushWnd = CreateSolidBrush(bg);
            FillRect(hdc, &paintStruct.rcPaint, brushWnd);
            DeleteObject(brushWnd);

            RECT clientArea = {0};
            GetClientRect(hwnd, &clientArea);

            int redSquare = (int)(((float)x / (float)clientArea.right) * 255) % 256;
            int greenSquare = (int)(((float)y / (float)clientArea.right) * 255) % 256;
            int blueSquare = ((int)(1.0f - ((float)x / (float)clientArea.right) * 255) + 256) % 256;

            HBRUSH brushSquare = CreateSolidBrush(RGB(redSquare, greenSquare, blueSquare));

            RECT square = {0};
            square.bottom = y;
            square.left = x;
            square.right = x + SQUARE_SIZE;
            square.top = y + SQUARE_SIZE;
            FillRect(hdc, &square, brushSquare);
            DeleteObject(brushSquare);

            width = clientArea.right;
            height = clientArea.top;

            EndPaint(hwnd, &paintStruct);
            return 0;
        }

    /*
    case WM_MOUSEMOVE:
        {
            x = (int)(short)LOWORD(lParam);
            y = (int)(short)HIWORD(lParam);
            return 0;
        }
        */
    case WM_INPUT:
        {
            BYTE buffer[1024];
            UINT size = sizeof(buffer);

            if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer, &size, sizeof(RAWINPUTHEADER)) > 0)
            {
                RAWINPUT* raw = (RAWINPUT*)buffer;

                if (raw->header.dwType == RIM_TYPEMOUSE)
                {
                    x += raw->data.mouse.lLastX;
                    y += raw->data.mouse.lLastY;
                }

                if (x > width - SQUARE_SIZE)
                {
                    x = width - SQUARE_SIZE - 1;
                }
                if (x < 0)
                {
                    x = 1;
                }

                if (y > height - SQUARE_SIZE)
                {
                    y = height - SQUARE_SIZE - 1;
                }
                if (y < 0)
                {
                    y = 1;
                }
                
            }
        }
    
    default:
        break;
    }
   

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}