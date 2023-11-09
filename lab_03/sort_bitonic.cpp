#include "sort_bitonic.h"

void bitonic_merge(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
    if (nmemb > 1) {
        size_t k = nmemb / 2;

        for (int i = 0; i < k; i++) {
            void *a = (char*)base + size * i;
            void *b = (char*)base + size * (i + k);
            if (cmp(a, b))
                swap(a, b, size);
        }

        bitonic_merge(base, k, size, cmp);
        bitonic_merge((char*)base + size * k, k, size, cmp);
    }
}

// NOTE: nmemb should be a power of 2
void bitonic_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
    if (nmemb > 1) {
        size_t k = nmemb / 2;

        bitonic_sort(base, k, size, cmp);
        bitonic_sort((char*)base + size * k, k, size, inverse(cmp));
        bitonic_merge(base, nmemb, size, cmp);
    }
}

