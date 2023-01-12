#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main()
{
    setlocale(LC_ALL, "");
    wprintf(L"%lc", L'');
    getchar();
}
