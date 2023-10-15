#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <vector>

#define BUFSIZE 255
#define U_INF -1 // Unsigned infinity

void pm(size_t **matrix, size_t r, size_t c);
void print_matrix_and_strings(size_t **matrix, size_t r, size_t c, const wchar_t *s1, const wchar_t *s2);

// Helper functions
int input_strings(wchar_t *s1, wchar_t *s2)
{
    int rc = 0;
    wchar_t buf[BUFSIZE];

    if (wscanf(L"%ls %ls", s1 + 1, s2 + 1) != 2)
    {
        fgetws(buf, sizeof(buf), stdin);
        rc = -1;
    }
    else
    {
        s1[0] = L'λ';
        s2[0] = L'λ';
    }

    return rc;
}

size_t **create_matrix(size_t n_rows, size_t n_columns)
{
    size_t *mem = (size_t*)malloc(n_rows * n_columns * sizeof(size_t));

    if (mem == NULL)
    {
        return NULL;
    }

    size_t **matrix = (size_t**)malloc(n_rows * sizeof(size_t*));

    if (matrix == NULL)
    {
        free(mem);
        return NULL;
    }

    for (size_t i = 0; i < n_rows; i++)
    {
        matrix[i] = mem + i * n_columns;
        matrix[i][0] = i;
    }

    for (size_t j = 1; j < n_columns; j++)
    {
        matrix[0][j] = j;
    }

    return matrix;
}

void free_matrix(size_t **matrix, size_t *first_row)
{
    free(first_row);
    free(matrix);
}

void matrix_roll_one_up(size_t **matrix, size_t matrix_size_in_rows)
{
    size_t n_rows = matrix_size_in_rows;
    size_t *tmp_row = matrix[0];
    size_t first_row_number = matrix[0][0];
    for (size_t i = 0; i < n_rows - 1; i++)
    {
        matrix[i] = matrix[i + 1];
    }
    // 0 1 2 3 4 5 6 7 8
    // 1 0 0 0 0 0 0 0 0
    // n_rows: 2
    // should be after roll:
    // 1 0 0 0 0 0 0 0 0
    // 2 1 2 3 4 5 6 7 8
    // so, first_row_number + n_rows
    matrix[n_rows - 1] = tmp_row;
    matrix[n_rows - 1][0] = first_row_number + n_rows;
}

void matrix_roll_one_down(size_t **matrix, size_t matrix_size_in_rows)
{
    size_t n_rows = matrix_size_in_rows;
    size_t *tmp_row = matrix[n_rows - 1];
    size_t last_row_number = matrix[n_rows - 1][0];
    for (size_t i = n_rows - 1; i > 0; i--)
    {
        matrix[i] = matrix[i - 1];
    }
    // 1 1 2 3 4 5 6 7 8
    // 2 0 0 0 0 0 0 0 0
    // n_rows: 2
    // should be after roll:
    // 0 0 0 0 0 0 0 0 0
    // 1 1 2 3 4 5 6 7 8
    // so, last_row_number - n_rows
    matrix[0] = tmp_row;
    matrix[0][0] = last_row_number - n_rows;
}

size_t *min3(size_t *a, size_t *b, size_t *c)
{
    size_t *result;
    size_t min = std::min(*a, std::min(*b, *c));

    if (min == *a)
    {
        result = a;
    }
    else if (min == *b)
    {
        result = b;
    }
    else
    {
        result = c;
    }

    return result;
}

size_t *min4(size_t *a, size_t *b, size_t *c, size_t *d)
{
    size_t *result;
    size_t min = std::min(std::min(*a, *b), std::min(*c, *d));

    if (min == *a)
    {
        result = a;
    }
    else if (min == *b)
    {
        result = b;
    }
    else if (min == *c)
    {
        result = c;
    }
    else
    {
        result = d;
    }

    return result;
}

void print_lev_trace(size_t **matrix, size_t r, size_t c)
{
    std::vector<char> trace;
    size_t *who;

    for (int i = r - 1, j = c - 1; (i + j) > 0;)
    {
        size_t left = (j > 0) ? matrix[i][j - 1] : U_INF;
        size_t diag = (i > 0 && j > 0) ? matrix[i - 1][j - 1] : U_INF;
        size_t up = (i > 0) ? matrix[i - 1][j] : U_INF;

        who = min3(&left, &diag, &up);

        if (*who == diag)
        {
            if (matrix[i][j] == diag)
            {
                trace.push_back('M');
            }
            else
            {
                trace.push_back('R');
            }
            --i;
            --j;
        }
        else if (*who == left)
        {
            trace.push_back('I');
            --j;
        }
        else
        {
            trace.push_back('D');
            --i;
        }
    }

    for (size_t i = 0; i < trace.size(); i++)
    {
        wprintf(L"%lc", trace.at(trace.size() - 1 - i));
    }
    wprintf(L"\n");
}

void print_damlev_trace(size_t **matrix, size_t r, size_t c, const wchar_t *s1, const wchar_t *s2)
{
    std::vector<char> trace;
    size_t *who;

    for (int i = r - 1, j = c - 1; (i + j) > 0;)
    {
        size_t left = (j > 0) ? matrix[i][j - 1] : U_INF;
        size_t diag = (i > 0 && j > 0) ? matrix[i - 1][j - 1] : U_INF;
        size_t up = (i > 0) ? matrix[i - 1][j] : U_INF;
        size_t swap = (i >= 2 && j >= 2)
            ? (
                    (s1[i] == s2[j - 1] && s1[i - 1] == s2[j])
                    ? matrix[i - 2][j - 2]
                    : U_INF
              )
            : U_INF;

        who = min4(&left, &diag, &up, &swap);

        if (*who == diag)
        {
            if (matrix[i][j] == diag)
            {
                trace.push_back('M');
            }
            else
            {
                trace.push_back('R');
            }
            --i;
            --j;
        }
        else if (*who == left)
        {
            trace.push_back('I');
            --j;
        }
        else if (*who == up)
        {
            trace.push_back('D');
            --i;
        }
        else
        {
            trace.push_back('S');
            i -= 2;
            j -= 2;
        }
    }

    for (size_t i = 0; i < trace.size(); i++)
    {
        wprintf(L"%lc", trace.at(trace.size() - 1 - i));
    }
    wprintf(L"\n");
}

// Algorithms
int levenshtein_iterative_matrix(const wchar_t *s1, const wchar_t *s2)
{
    size_t len1 = wcsnlen(s1, BUFSIZE); // n_rows
    size_t len2 = wcsnlen(s2, BUFSIZE); // n_columns

    size_t **matrix = create_matrix(2, len2);
    size_t *first_row = matrix[0];

    if (matrix == NULL) return -1;

    int result = 0;
    size_t insert_cost, delete_cost, replace_cost, *who;
    bool cond;

    for (size_t i = 1; i < len1; i++)
    {
        for (size_t j = 1; j < len2; j++)
        {
            insert_cost = matrix[1 - 1][j] + 1;
            delete_cost = matrix[1][j - 1] + 1;
            cond = (s1[i] == s2[j]);
            replace_cost = matrix[1 - 1][j - 1] + (cond ? 0 : 1);
            who = min3(&insert_cost, &delete_cost, &replace_cost);
            matrix[1][j] = *who;
        }
        matrix_roll_one_up(matrix, 2);
    }

    result = matrix[0][len2 - 1];

    /* wprintf(L"%d\n", result); */

    free_matrix(matrix, first_row);

    return result;
}

int levenshtein_iterative_full_matrix(const wchar_t *s1, const wchar_t *s2)
{
    size_t len1 = wcsnlen(s1, BUFSIZE); // n_rows
    size_t len2 = wcsnlen(s2, BUFSIZE); // n_columns

    size_t **matrix = create_matrix(len1, len2);

    if (matrix == NULL) return -1;

    int result = 0;
    bool cond;
    size_t insert_cost, delete_cost, replace_cost, *who;

    for (size_t i = 1; i < len1; i++)
    {
        for (size_t j = 1; j < len2; j++)
        {
            insert_cost = matrix[i - 1][j] + 1;
            delete_cost = matrix[i][j - 1] + 1;
            cond = (s1[i] == s2[j]);
            replace_cost = matrix[i - 1][j - 1] + (cond ? 0 : 1);
            who = min3(&insert_cost, &delete_cost, &replace_cost);
            matrix[i][j] = *who;
        }
    }

    result = matrix[len1 - 1][len2 - 1];

    // Printing stuff
    print_matrix_and_strings(matrix, len1, len2, s1, s2);
    print_lev_trace(matrix, len1, len2);
    wprintf(L"%d\n", result);

    free_matrix(matrix, matrix[0]);

    return result;
}

/* int damerau_levenshtein_iterative_matrix(const wchar_t *s1, const wchar_t *s2) */
/* { */
/*     size_t len1 = wcsnlen(s1, BUFSIZE); */
/*     size_t len2 = wcsnlen(s2, BUFSIZE); */
/*     (void)len1; */
/*     (void)len2; */
/*     return 0; */
/* } */

int damerau_levenshtein_iterative_full_matrix(const wchar_t *s1, const wchar_t *s2)
{
    size_t len1 = wcsnlen(s1, BUFSIZE);
    size_t len2 = wcsnlen(s2, BUFSIZE);

    size_t **matrix = create_matrix(len1, len2);
    if (matrix == NULL) return -1;
    int result = 0;

    bool diag_cond, swap_cond;
    size_t insert_cost, delete_cost, replace_cost, swap_cost, *who;

    for (size_t i = 1; i < len1; i++)
    {
        for (size_t j = 1; j < len2; j++)
        {
            insert_cost = matrix[i - 1][j] + 1;
            delete_cost = matrix[i][j - 1] + 1;
            diag_cond = (s1[i] == s2[j]);
            replace_cost = matrix[i - 1][j - 1] + (diag_cond ? 0 : 1);
            if (i >= 2 && j >= 2) [[likely]]
            {
                swap_cond = (s1[i] == s2[j - 1] && s1[i - 1] == s2[j]);
                swap_cost = swap_cond ? matrix[i - 2][j - 2] + 1 : U_INF;
                who = min4(&insert_cost, &delete_cost, &replace_cost, &swap_cost);
            }
            else
            {
                who = min3(&insert_cost, &delete_cost, &replace_cost);
            }
            matrix[i][j] = *who;
        }
    }

    result = matrix[len1 - 1][len2 - 1];

    // Printing stuff
    print_matrix_and_strings(matrix, len1, len2, s1, s2);
    print_damlev_trace(matrix, len1, len2, s1, s2);
    wprintf(L"%d\n", result);

    free_matrix(matrix, matrix[0]);

    return result;
}

int damerau_levenshtein_recursive_no_cache(const wchar_t *s1, const wchar_t *s2)
{
    size_t len1 = wcsnlen(s1, BUFSIZE);
    size_t len2 = wcsnlen(s2, BUFSIZE);
    (void)len1;
    (void)len2;
    return 0;
}

int damerau_levenshtein_recursive_with_cache(const wchar_t *s1, const wchar_t *s2)
{
    size_t len1 = wcsnlen(s1, BUFSIZE);
    size_t len2 = wcsnlen(s2, BUFSIZE);
    (void)len1;
    (void)len2;
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

            levenshtein_iterative_matrix(s1, s2);
            levenshtein_iterative_full_matrix(s1, s2);
            damerau_levenshtein_iterative_full_matrix(s1, s2);
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

// Pretty printers for GDB
void pm(size_t **matrix, size_t r, size_t c)
{
    for (size_t i = 0; i < r; i++)
    {
        for (size_t j = 0; j < c; j++)
        {
            wprintf(L"%2d ", matrix[i][j]);
        }
        wprintf(L"\n");
    }
}

void print_matrix_and_strings(size_t **matrix, size_t r, size_t c, const wchar_t *s1, const wchar_t *s2)
{
    wprintf(L"%2lc ", ' ');
    for (size_t j = 0; j < c; j++)
    {
        wprintf(L"%2lc ", s2[j]);
    }
    wprintf(L"\n");
    for (size_t i = 0; i < r; i++)
    {
        wprintf(L"%2lc ", s1[i]);
        for (size_t j = 0; j < c; j++)
        {
            wprintf(L"%2d ", matrix[i][j]);
        }
        wprintf(L"\n");
    }
}
