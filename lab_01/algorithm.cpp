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

static u32 dl(Data &data, u32 col) {
    // XXX: col = 0?; ugly
    char letter_vert = data.str1[data.row2[0] + 1];
    char letter_hor = data.str2[col]; // col = 0 => 1st letter

    u32 top_left = data.row1[col];
    u32 top_right = data.row1[col + 1];
    u32 bottom_left = data.row2[col];

    /* u32 step_right_insert = bottom_left + 1; */
    u32 x = bottom_left + 1;

    /* u32 step_down_delete = top_right + 1; */
    u32 y = top_right + 1;

    /* u32 step_diagonal = top_left + (letter_vert == letter_hor ? 0 : 1); */
    u32 z = top_left + (letter_vert == letter_hor ? 0 : 1);

    u32 min3 = (x < y ? (x < z ? x : z) : (y < z ? y : z));

    return min3;
}

// FIXME: not working correctly
u32 lev_iterative(const char *str1, u32 len1, const char *str2, u32 len2) {
    if (len1 == 0) {
        return len2;
    } else if (len2 == 0) {
        return len1;
    }

    u32 row1[len2 + 1];
    u32 row2[len2 + 1];

    for (u32 i = 0; i <= len2; row1[i] = i, i++);
    row2[0] = 1;

    Data data = {
        .str1 = str1,
        .str2 = str2,
        .row1 = row1,
        .row2 = row2
    };

    for (u32 row = 0; row < len1; row++) {
        for (u32 col = 0; col < len2; col++) {
            row2[col + 1] = dl(data, col);
        }

        swap(data.row1, data.row2);
        data.row2[0] += 2;
    }

    // XXX: ugly
    return data.row1[len2];
}

u32 damlev_iterative_with_matrix(char *str1, u32 len1, char *str2, u32 len2) {
    return 0;
}

u32 damlev_recursive_no_cache(char *str1, u32 len1, char *str2, u32 len2) {
    return 0;
}

u32 damlev_recursive_with_cache(char *str1, u32 len1, char *str2, u32 len2) {
    return 0;
}

