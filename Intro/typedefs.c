#include <WinDef.h>
#include <wchar.h>
#include <stdio.h>
#include <windows.h>
/*It's necessary to set the locale to characters like ã and ç to work properly. It's done by adding the locale.h and calling the function setlocale.*/
#include <locale.h>

BOOL hasMoreThanFive(const wchar_t * name)
{
    size_t size = wcslen(name);
    if (size <= 5)
    {
        return FALSE;
    }

    return TRUE;    
}

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");
    wchar_t name[256] = {0};
    wprintf(L"Digit your name: ");
    fgetws(name, 255, stdin);
    name[wcscspn(name, L"\n")] = L'0'; //wcscspn is the wide char version of strcspn

    BOOL result = hasMoreThanFive(name);
    if (result)
    {
        wprintf(L"Your name has more than 5 letters.\n");
    } else
    {
        wprintf(L"Your name has less than 5 letters. Só testando os caracteres. maçã");
    }    
    
    return 0;
}