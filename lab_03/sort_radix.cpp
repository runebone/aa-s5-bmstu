#include "sort_radix.h"

#include <memory.h>
#include <cstdio>

typedef unsigned char byte;

unsigned int get_msbit_idx(byte x)
{
    unsigned int msbit_idx = 7;

    while ((x & (1 << msbit_idx)) == 0)
        msbit_idx--;

    return msbit_idx;
}

unsigned int find_msbit(void *base, size_t nmemb, size_t size)
{
    byte byte_ptr = size - 1;
    byte sum = 0;

    while (sum == 0 && byte_ptr >= 0) {
        for (size_t i = 0; i < nmemb; i++) {
            byte *elem = (byte*)base + size * i;
            elem += byte_ptr;

            sum |= *elem;
        }

        if (sum == 0)
            byte_ptr--;
    }

    if (byte_ptr < 0)
        return -1; // All elements = 0

    unsigned int msbit_idx = 8 * byte_ptr + get_msbit_idx(sum);

    return msbit_idx;
}

void radix_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
    unsigned int msbit_idx = find_msbit(base, nmemb, size);

    printf("%u\n", msbit_idx);
}

