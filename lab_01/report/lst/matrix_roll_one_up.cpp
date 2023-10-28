void matrix_roll_one_up(size_t **matrix, size_t matrix_size_in_rows)
{
    size_t n_rows = matrix_size_in_rows;
    size_t *tmp_row = matrix[0];
    size_t first_row_number = matrix[0][0];
    for (size_t i = 0; i < n_rows - 1; i++)
        matrix[i] = matrix[i + 1];

    matrix[n_rows - 1] = tmp_row;
    matrix[n_rows - 1][0] = first_row_number + n_rows;
}
