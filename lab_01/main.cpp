#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "func.h"

#define BUFSIZE 255

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

        // NOTE: We can either use scanf everywhere or wscanf. Otherwise crash.
        if (wscanf(L"%d", &c) != 1)
        {
            wprintf(L"Введите 1, 2 или 3.\n");
            fgetws(buf, sizeof(buf), stdin); // Flushing input
            continue;
        }

        if (c == 1)
        {
            rc = input_strings(s1, s2);

            size_t len1 = wcsnlen(s1, BUFSIZE);
            size_t len2 = wcsnlen(s2, BUFSIZE);

            size_t li = levenshtein_iterative_full_matrix(s1, len1, s2, len2);
            size_t dli = damerau_levenshtein_iterative_full_matrix(s1, len1, s2, len2);
            size_t dlr = damerau_levenshtein_recursive_no_cache(s1, len1, s2, len2);
            size_t dlrc = damerau_levenshtein_recursive_with_cache(s1, len1, s2, len2);

            wprintf(L"%-41ls: %ld\n", L"Levenshtein Iterative", li);
            wprintf(L"%-41ls: %ld\n", L"Damerau-Levenshtein Iterative", dli);
            wprintf(L"%-41ls: %ld\n", L"Damerau-Levenshtein Recursive No Cache", dlr);
            wprintf(L"%-41ls: %ld\n", L"Damerau-Levenshtein Recursive With Cache", dlrc);
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
        wprintf(L"s1: %ls %ld\ns2: %ls %ld\n", s1, wcslen(s1), s2, wcslen(s2));
    }

    return rc;
}

