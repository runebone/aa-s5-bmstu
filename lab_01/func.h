#ifndef __FUNC_H__
#define __FUNC_H__

#include <wchar.h>

size_t **create_matrix(size_t n_rows, size_t n_columns);
void free_matrix(size_t **matrix, size_t *first_row);
void matrix_roll_one_up(size_t **matrix, size_t matrix_size_in_rows);
void matrix_roll_one_down(size_t **matrix, size_t matrix_size_in_rows);

size_t *min3(size_t *a, size_t *b, size_t *c);
size_t *min4(size_t *a, size_t *b, size_t *c, size_t *d);

void pm(size_t **matrix, size_t r, size_t c);
void print_matrix_and_strings(size_t **matrix, size_t r, size_t c, const wchar_t *str1, const wchar_t *str2);

void print_lev_trace(size_t **matrix, size_t r, size_t c);
void print_damlev_trace(size_t **matrix, size_t r, size_t c, const wchar_t *str1, const wchar_t *str2);

size_t levenshtein_iterative_matrix(const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2);
size_t levenshtein_iterative_full_matrix(const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2);
size_t damerau_levenshtein_iterative_full_matrix(const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2);
size_t damerau_levenshtein_recursive_no_cache(const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2);
size_t damlev_rwc_helper(size_t **matrix, const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2);
size_t damerau_levenshtein_recursive_with_cache(const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2);

#endif // __FUNC_H__
