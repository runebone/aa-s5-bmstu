#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <memory.h>
#include <wchar.h>

using cmp_fn_t = std::function<int(const void *, const void*)>;

int asc(const void *a, const void *b)
{
    return *((int*)a) > *((int*)b);
}

int desc(const void *a, const void *b)
{
    return *((int*)a) < *((int*)b);
}

inline void swap(void *a, void *b, size_t size)
{
    char t[size];
    memcpy(t, a, size);
    memcpy(a, b, size);
    memcpy(b, t, size);
}

/* void bitonic_merge(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *)) */
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
/* void bitonic_sort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *)) */
void bitonic_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
    if (nmemb > 1) {
        size_t k = nmemb / 2;
        cmp_fn_t inverse_cmp = [cmp](const void *a, const void *b){ return cmp(b, a); };

        bitonic_sort(base, k, size, cmp);
        bitonic_sort((char*)base + size * k, k, size, inverse_cmp);
        bitonic_merge(base, nmemb, size, cmp);
    }
}

/* void radix_sort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *)) */
void radix_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
}

/* void bubble_sort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *)) */
void bubble_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp)
{
}

int main()
{
    int arr[] = {3, 6, 5, 7, 4, 1, 8, 2};

    /* std::vector<int> vec{3, 6, 5, 7, 4, 1, 8, 2, 12, 54, 754, 34, 0, -1, 8, 38}; */
    /* std::vector<int> vec{3, 6, 5, 7}; */
    /* std::vector<int> vec{6, 5}; */

    /* std::vector<int> vec{3, 5, 7, 4}; */

    std::vector<wchar_t> vec{L'c', L'f', L'e', L'g', L'd', L'a', L'h', L'b'};

    /* for (int i = 0; i < 8; i++) */
    /* for (auto v : vec) */
        /* printf("%d ", v); */
        /* printf("%d ", arr[i]); */
    /* printf("\n"); */

    bitonic_sort(&vec[0], vec.size(), sizeof(int), asc);
    /* bitonic_merge(&vec[0], vec.size(), sizeof(int), desc); */

    /* for (int i = 0; i < 8; i++) */
    for (auto v : vec)
        wprintf(L"%lc ", v);
        /* printf("%d ", arr[i]); */
    /* printf("\n"); */
}
