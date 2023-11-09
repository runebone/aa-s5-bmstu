#include <algorithm>

int asc(const void *a, const void *b)
{
    return *((int*)a) < *((int*)b);
}

int desc(const void *a, const void *b)
{
    return *((int*)a) > *((int*)b);
}


void bitonic_merge(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
    if (nmemb > 1) {
        size_t k = nmemb / 2;

        for (int i = 0; i < k; i++) {
            const void *a = (char*)base + size * i;
            const void *b = (char*)base + size * (i + k);
            if (cmp(a, b))
                std::swap(a, b);
        }
    }
}

/* Sort NMEMB elements of BASE, of SIZE bytes each, using CMP to perform the comparisons. */
void bitonic_sort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
    if (nmemb > 1) {
        size_t k = nmemb / 2;

        bitonic_sort(base, k, size, asc);
        bitonic_sort((char*)base + size * k, k, size, desc);
    }
}

void radix_sort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
}

void bubble_sort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
}

int main()
{
}
