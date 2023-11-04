size_t lev_ifm_helper(size_t **matrix, const wchar_t *s1, size_t len1, const wchar_t *s2, size_t len2)
{
    size_t result = 0;
    bool replace_skip_cond;
    size_t insert_cost, delete_cost, replace_cost, *who;

    for (size_t i = 1; i < len1; i++) {
        for (size_t j = 1; j < len2; j++) {
            insert_cost = matrix[i - 1][j] + 1;
            delete_cost = matrix[i][j - 1] + 1;
            replace_skip_cond = (s1[i] == s2[j]);
            replace_cost = matrix[i - 1][j - 1] + (replace_skip_cond ? 0 : 1);
            who = min3(&insert_cost, &delete_cost, &replace_cost);
            matrix[i][j] = *who;
        }
    }

    result = matrix[len1 - 1][len2 - 1];

    return result;
}
