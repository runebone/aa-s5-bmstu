size_t damerau_levenshtein_iterative_full_matrix(const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2)
{
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;

    ++len1;
    ++len2;
    const wchar_t *s1 = str1 - 1;
    const wchar_t *s2 = str2 - 1;

    size_t **matrix = create_matrix(len1, len2);
    if (matrix == NULL) return -1;

    size_t result = damlev_ifm_helper(matrix, s1, len1, s2, len2);

    free_matrix(matrix, matrix[0]);

    return result;
}
