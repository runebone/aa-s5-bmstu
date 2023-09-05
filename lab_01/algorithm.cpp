#include "algorithm.h"

#include <algorithm>

static u32 d_rec(const char *str1, const char *str2, u32 i, u32 j) {
    if (i == 0) { return j; } else if (j == 0) { return i; }

    u32 d1 = d_rec(str1, str2, i, j - 1) + 1;
    u32 d2 = d_rec(str1, str2, i - 1, j) + 1;
    u32 m = str1[i] == str2[j] ? 0 : 1;
    u32 d3 = d_rec(str1, str2, i - 1, j - 1) + m;

    return std::min(d1, std::min(d2, d3));
}

u32 lev_recursive(const char *str1, u32 len1, const char *str2, u32 len2) {
    return d_rec(str1, str2, len1, len2);
}

u32 lev_iterative(const char *str1, u32 len1, const char *str2, u32 len2) {
    if (len1 == 0) { return len2; } else if (len2 == 0) { return len1; }

    u32 matrix[len1 + 1][len2 + 1];

    for (u32 i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }

    for (u32 i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }

    for (u32 row = 1; row <= len1; row++) {
        for (u32 col = 1; col <= len2; col++) {
            u32 tl = matrix[row - 1][col - 1] + (str1[row - 1] == str2[col - 1] ? 0 : 1);
            u32 bl = matrix[row][col - 1] + 1;
            u32 tr = matrix[row - 1][col] + 1;

            u32 min = std::min(tl, std::min(bl, tr));

            matrix[row][col] = min;
        }
    }

    return matrix[len1][len2];
}

u32 damlev_iterative_with_matrix(const char *str1, u32 len1, const char *str2, u32 len2) {
    if (len1 == 0) { return len2; } else if (len2 == 0) { return len1; }

    u32 matrix[len1 + 1][len2 + 1];

    for (u32 i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }

    for (u32 i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }

    for (u32 row = 1; row <= len1; row++) {
        for (u32 col = 1; col <= len2; col++) {
            u32 tl = matrix[row - 1][col - 1]
                + (str1[row - 1] == str2[col - 1] ? 0 : 1);
            u32 bl = matrix[row][col - 1] + 1;
            u32 tr = matrix[row - 1][col] + 1;

            u32 tltl;

            if (row > 1 && col > 1
                    && str1[row] == str2[col - 1]
                    && str1[row - 1] == str2[col]) {
                tltl = matrix[row - 2][col - 2]
                    + (str1[row - 1] == str2[col - 1] ? 0 : 1);
            }

            u32 min = std::min(tltl, std::min(tl, std::min(bl, tr)));

            matrix[row][col] = min;
        }
    }

    return matrix[len1][len2];
}

u32 damlev_recursive_no_cache(const char *str1, u32 len1, const char *str2, u32 len2) {
    return 0;
}

u32 damlev_recursive_with_cache(const char *str1, u32 len1, const char *str2, u32 len2) {
    return 0;
}

