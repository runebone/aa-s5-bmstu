size_t damerau_levenshtein_recursive_with_cache(const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2)
{
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;

    size_t **matrix = create_matrix(len1, len2);

    if (matrix == NULL) return -1;

    for (size_t i = 0; i < len1; i++)
        for (size_t j = 0; j < len2; j++)
            matrix[i][j] = U_INF;

    size_t result = damlev_rwc_helper(matrix, str1, len1, str2, len2);

    free_matrix(matrix, matrix[0]);

    return result;
}
