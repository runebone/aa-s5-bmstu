#include "sort_bubble.h"

void bubble_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
    for (size_t i = 0; i < nmemb; i++) {
        bool swapped = false;
        for (size_t j = 0; j < nmemb - i - 1; j++) {
            char *a = (char*)base + size * j;
            char *b = (char*)base + size * (j + 1);
            if (cmp(a, b)) {
                swap(a, b, size);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

