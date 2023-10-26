void print_damlev_trace(size_t **matrix, size_t r, size_t c, const wchar_t *str1, const wchar_t *str2)
{
    std::vector<char> trace;
    size_t *who;

    const wchar_t *s1 = str1 - 1;
    const wchar_t *s2 = str2 - 1;

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
