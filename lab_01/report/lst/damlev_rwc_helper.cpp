size_t damlev_rwc_helper(size_t **matrix, const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2)
{
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;

    size_t i = len1 - 1;
    size_t j = len2 - 1;

    size_t insert = (((j > 0) && (matrix[i][j - 1] != U_INF))
        ? matrix[i][j - 1]
        : damlev_rwc_helper(matrix, str1, len1, str2, len2 - 1))
        + 1;

    size_t del = (((i > 0) && (matrix[i - 1][j] != U_INF))
        ? matrix[i - 1][j]
        : damlev_rwc_helper(matrix, str1, len1 - 1, str2, len2))
        + 1;

    size_t replace = (((i > 0 && j > 0) && (matrix[i - 1][j - 1] != U_INF))
        ? matrix[i - 1][j - 1]
        : damlev_rwc_helper(matrix, str1, len1 - 1, str2, len2 - 1))
        + (str1[i] == str2[j] ? 0 : 1);

    size_t swap = U_INF;
    if (i > 1 && j > 1 && matrix[i - 2][j - 2] != U_INF && (str1[i] == str2[j - 1] && str1[i - 1] == str2[j]))
    {
        swap = matrix[i - 2][j - 2] + 1;
    }
    else if (i >= 1 && j >= 1 && (str1[i] == str2[j - 1] && str1[i - 1] == str2[j]))
    {
        swap = damlev_rwc_helper(matrix, str1, len1 - 2, str2, len2 - 2) + 1;
    }

    size_t result = *min4(&insert, &del, &replace, &swap);

    if (matrix[i][j] == U_INF) matrix[i][j] = result;

    return result;
}
