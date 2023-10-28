void free_matrix(size_t **matrix, size_t *first_row)
{
    free(first_row);
    free(matrix);
}
