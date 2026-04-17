#include <windows.h>
#include <stdio.h>
#include <locale.h>

int WINAPI wWinMain(
    HINSTANCE hI,
    HINSTANCE hIp,
    PWSTR argvLike,
    int nCmdShow
)
{
    setlocale(LC_ALL, "");
    MessageBoxW(NULL, L"Olá", L"Janela", MB_OK);
    return 0;
} // about the macro WINAPI that expands to __stdcall: __stdcall is used because the compiler usually uses the __cdecl which is a calling convention that cleans the stack outside the function, that is, in x86-32, after the function returns, the stack pointer is incremented. Some functions, though, like wWinMain and WinMain were written using a different convention, a convention where the stack pointer is incremented by the function itself, so we need to inform that to the compiler, otherwise, the stack will be cleaned twice and the stack will be unaligned, and this is done by the use of the directive __stdcall.