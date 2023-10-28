void matrix_roll_one_down(size_t **matrix, size_t matrix_size_in_rows)
{
    size_t n_rows = matrix_size_in_rows;
    size_t *tmp_row = matrix[n_rows - 1];
    size_t last_row_number = matrix[n_rows - 1][0];
    for (size_t i = n_rows - 1; i > 0; i--)
        matrix[i] = matrix[i - 1];

    matrix[0] = tmp_row;
    matrix[0][0] = last_row_number - n_rows;
}
