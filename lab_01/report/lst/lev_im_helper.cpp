size_t lev_im_helper(size_t **matrix_2xN, const wchar_t *s1, size_t len1, const wchar_t *s2, size_t len2)
{
    size_t result = 0;
    size_t insert_cost, delete_cost, replace_cost, *who;
    bool replace_skip_cond;

    for (size_t i = 1; i < len1; i++) {
        for (size_t j = 1; j < len2; j++) {
            insert_cost = matrix_2xN[0][j] + 1;
            delete_cost = matrix_2xN[1][j - 1] + 1;
            replace_skip_cond = (s1[i] == s2[j]);
            replace_cost = matrix_2xN[0][j - 1] + (replace_skip_cond ? 0 : 1);
            who = min3(&insert_cost, &delete_cost, &replace_cost);
            matrix_2xN[1][j] = *who;
        }
        matrix_roll_one_up(matrix_2xN, 2);
    }

    result = matrix_2xN[0][len2 - 1];

    return result;
}
