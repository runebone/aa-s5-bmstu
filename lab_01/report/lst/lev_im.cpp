size_t levenshtein_iterative_matrix(const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2)
{
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;
    
    ++len1;
    ++len2;
    const wchar_t *s1 = str1 - 1;
    const wchar_t *s2 = str2 - 1;

    size_t **matrix = create_matrix(2, len2);
    size_t *first_row = matrix[0];

    if (matrix == NULL) return -1;

    size_t result = lev_im_helper(matrix, s1, len1, s2, len2);

    free_matrix(matrix, first_row);

    return result;
}
