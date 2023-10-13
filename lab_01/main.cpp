#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

#define BUFSIZE 255

// Helper functions
int input_strings(wchar_t *s1, wchar_t *s2)
{
    int rc = 0;
    wchar_t buf[BUFSIZE];
    if (wscanf(L"%ls %ls", s1, s2) != 2)
    {
        fgetws(buf, sizeof(buf), stdin);
        rc = -1;
    }
    return rc;
}

// Algorithms
int levenshtein_iterative()
{
    return 0;
}

int damerau_levenshtein_iterative()
{
    return 0;
}

int damerau_levenshtein_recursive_no_cache()
{
    return 0;
}

int damerau_levenshtein_recursive_with_cache()
{
    return 0;
}

int main()
{
    setlocale(LC_ALL, "");
    int rc = 0;
    wchar_t buf[BUFSIZE];
    wchar_t s1[BUFSIZE] = { 0 };
    wchar_t s2[BUFSIZE] = { 0 };
    // Menu
    for (int c = 0; c != 3 && rc == 0;)
    {
        wprintf(L"Выберите действие:\n");
        wprintf(L"1 - Ввести два слова\n");
        wprintf(L"2 - Запустить тесты\n");
        wprintf(L"3 - Выйти\n");
        wprintf(L"> ");
        if (wscanf(L"%d", &c) != 1)
        {
            wprintf(L"Введите 1, 2 или 3.\n");
            fgetws(buf, sizeof(buf), stdin); // Flushing input
            continue;
        }
        if (c == 1)
        {
            rc = input_strings(s1, s2);
        }
        else if (c == 2)
        {
        }
        else if (c != 3)
        {
            wprintf(L"Введите 1, 2 или 3!\n");
        }
    }
    if (rc != 0)
    {
        wprintf(L"Программа завершилась с ошибкой.\n");
    }
    else
    {
        /* wprintf(L"s1: %ls\ns2: %ls\n", s1, s2); */
    }
    return rc;
}
