#ifndef __SORTING_UTILS_H__
#define __SORTING_UTILS_H__

#include <functional>
#include <memory.h>

using cmp_fn_t = std::function<int(const void*, const void*)>;

template<typename T>
int asc(const void *a, const void *b)
{
    using TNoRef = std::decay_t<T>;
    return *((TNoRef*)a) > *((TNoRef*)b);
}

inline cmp_fn_t inverse(cmp_fn_t cmp)
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

#endif // __SORTING_UTILS_H__
