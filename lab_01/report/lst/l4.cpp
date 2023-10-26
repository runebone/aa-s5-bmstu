#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <unistd.h>

#include "func.h"
#include "colors.h"
#include "benchmark.h"

#define BUFSIZE 100'000
#define CURDIR "/home/human/University/aa/lab_01/"

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

int input_sssn(size_t *start, size_t *stop, size_t *step, size_t *n)
{
    int rc = 0;
    wchar_t buf[BUFSIZE];
    if (wscanf(L"%lu %lu %lu %lu", start, stop, step, n) != 4)
    {
        fgetws(buf, sizeof(buf), stdin);
        rc = -1;
    }
    return rc;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    int rc = 0;
    wchar_t buf[BUFSIZE];
    wchar_t s1[BUFSIZE] = { 0 };
    wchar_t s2[BUFSIZE] = { 0 };

    // Menu
    for (int c = 0; c != 5 && rc == 0;)
    {
        wprintf(L"Выберите действие:\n");
        wprintf(L"1 - Ввести два слова\n");
        wprintf(L"2 - Провести замеры времени\n");
        wprintf(L"3 - Провести замеры времени (ручной ввод)\n");
        wprintf(L"4 - Построить графики\n");
        wprintf(L"5 - Выйти\n");
        wprintf(L"> ");

        // NOTE: We can either use scanf everywhere or wscanf. Otherwise crash.
        if (wscanf(L"%d", &c) != 1)
        {
            wprintf(L"Введите 1, 2, 3, 4 или 5.\n");
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

            /* wprintf(L"%-41ls: %ld\n", L"Levenshtein Iterative", li); */
            /* wprintf(L"%-41ls: %ld\n", L"Damerau-Levenshtein Iterative", dli); */
            /* wprintf(L"%-41ls: %ld\n", L"Damerau-Levenshtein Recursive No Cache", dlr); */
            /* wprintf(L"%-41ls: %ld\n", L"Damerau-Levenshtein Recursive With Cache", dlrc); */

            wprintf(L"%-45ls: %ld\n", L"Левенштейн Итеративный", li);
            wprintf(L"%-45ls: %ld\n", L"Дамерау-Левенштейн Итеративный", dli);
            wprintf(L"%-45ls: %ld\n", L"Дамерау-Левенштейн Рекурсивный", dlr);
            wprintf(L"%-45ls: %ld\n", L"Дамерау-Левенштейн Рекурсивный с кешированием", dlrc);
        }
        else if (c == 2)
        {
            benchmark();
        }
        else if (c == 3)
        {
            size_t start, stop, step, n;
            wprintf(L"Введите начальную длину слов, конечную, шаг изменения длины, и сколько замеров времени требуется провести для каждой длины:\n");
            input_sssn(&start, &stop, &step, &n);
            benchmark(start, stop, step, n);
        }
        else if (c == 4)
        {
            if (fork() == 0)
            {
                execlp("python", "python", CURDIR "plot.py", CURDIR "benchmark/data.csv", nullptr);
                exit(0);
            }
        }
        else if (c < 1 || c > 5)
        {
            wprintf(L"Введите цифру, соответствующую пункту меню.\n");
        }
    }

    if (rc != 0)
    {
        wprintf(L"Программа завершилась с ошибкой.\n");
    }

    return rc;
}

