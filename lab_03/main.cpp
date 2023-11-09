#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <memory.h>
#include <wchar.h>
#include <iostream>

using cmp_fn_t = std::function<int(const void*, const void*)>;

template<typename T>
int asc(const void *a, const void *b)
{
    // Remove &
    using U = std::decay_t<T>;
    return *((U*)a) > *((U*)b);
}

cmp_fn_t inverse(cmp_fn_t cmp)
{
    return [cmp](const void *a, const void *b){ return cmp(b, a); };
}

inline void swap(void *a, void *b, size_t size)
{
    char t[size];
    memcpy(t, a, size);
    memcpy(a, b, size);
    memcpy(b, t, size);
}

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

/* Sort NMEMB elements of BASE, of SIZE bytes each, using CMP to perform the comparisons. */
void bitonic_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
    if (nmemb > 1) {
        size_t k = nmemb / 2;

        bitonic_sort(base, k, size, cmp);
        bitonic_sort((char*)base + size * k, k, size, inverse(cmp));
        bitonic_merge(base, nmemb, size, cmp);
    }
}

void radix_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
}

void bubble_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
}

int main()
{
    /* std::vector<int> vec{3, 6, 5, 7, 4, 1, 8, 2, 12, 54, 754, 34, 0, -1, 8, 38}; */
    std::vector<wchar_t> vec{L'c', L'f', L'e', L'g', L'd', L'a', L'h', L'b'};

    bitonic_sort(&vec[0], vec.size(), sizeof(vec[0]), inverse(asc<decltype(vec[0])>));
    /* bitonic_merge(&vec[0], vec.size(), sizeof(int), desc); */

    for (auto v : vec)
        /* printf("%d ", v); */
        wprintf(L"%lc ", v);
    /* printf("\n"); */
}
