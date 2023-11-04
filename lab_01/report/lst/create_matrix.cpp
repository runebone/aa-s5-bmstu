size_t **create_matrix(size_t n_rows, size_t n_columns)
{
    if (n_rows < 1 || n_columns < 1)
        return NULL;

    size_t *mem = (size_t*)malloc(n_rows * n_columns * sizeof(size_t));

    if (mem == NULL)
        return NULL;

    size_t **matrix = (size_t**)malloc(n_rows * sizeof(size_t*));

    if (matrix == NULL) {
        free(mem);
        return NULL;
    }

    for (size_t i = 0; i < n_rows; i++) {
        matrix[i] = mem + i * n_columns;
        matrix[i][0] = i;
    }

    for (size_t j = 1; j < n_columns; j++)
        matrix[0][j] = j;

    return matrix;
}
