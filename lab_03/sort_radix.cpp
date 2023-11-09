#include "sort_radix.h"

#include <memory.h>
#include <cstdio>

typedef unsigned char byte;

size_t get_msbit_idx(byte x)
{
    size_t msbit_idx = 7;

    while ((x & (1 << msbit_idx)) == 0)
        msbit_idx--;

    return msbit_idx;
}

size_t find_msbit(void *base, size_t nmemb, size_t size)
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

    size_t msbit_idx = 8 * byte_ptr + get_msbit_idx(sum);

    return msbit_idx;
}

void radix_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
    size_t msbit_idx = find_msbit(base, nmemb, size);
    size_t byte_ptr = 0;

    void *zero_elems[nmemb];
    void *one_elems[nmemb];

    size_t zero_ptr = 0;
    size_t zero_cnt = 0;
    size_t one_ptr = 0;
    size_t one_cnt = 0;
    size_t ptr = 0;

    byte a[size], b[size];
    memset(a, 0, size);
    memset(b, 255, size);
    int order_asc = cmp(a, b);

    byte base_copy[nmemb * size];
    memcpy(base_copy, base, nmemb * size);

    byte mask = 1;

    for (size_t curbit = 0; curbit <= msbit_idx; curbit++, mask <<= 1) {
        zero_ptr = 0;
        zero_cnt = 0;
        one_ptr = 0;
        one_cnt = 0;
        ptr = 0;

        if (curbit && (curbit % 8) == 0) {
            mask = 1;
            byte_ptr++;
        }

        for (size_t i = 0; i < nmemb; i++) {
            byte *elem = (byte*)base + size * i;
            elem += byte_ptr;

            // HACK Equivalent to (*elem & mask) when order_asc = 1, but when
            // order_asc = 0, we add ones to zero array to account for order
            // in the future, avoiding dublicating code.
            if (((*elem & mask) > 0) ^ !order_asc) {
                one_elems[one_ptr] = elem;
                one_ptr++;
            } else {
                zero_elems[zero_ptr] = elem;
                zero_ptr++;
            }
        }

        for (; zero_ptr; zero_ptr--) {
            void *dst = (byte*)base_copy + size * ptr;
            void *src = zero_elems[zero_cnt];
            memcpy(dst, src, size);
            zero_cnt++;
            ptr++;
        }
        for (; one_ptr; one_ptr--) {
            void *dst = (byte*)base_copy + size * ptr;
            void *src = one_elems[one_cnt];
            memcpy(dst, src, size);
            one_cnt++;
            ptr++;
        }

        memcpy(base, base_copy, nmemb * size);
    }

    printf("%lu\n", msbit_idx);
}

