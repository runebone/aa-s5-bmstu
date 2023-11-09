#ifndef __SORT_BITONIC_H__
#define __SORT_BITONIC_H__

#include "sorting_utils.h"

void bitonic_merge(void *base, size_t nmemb, size_t size, cmp_fn_t cmp);
void bitonic_sort(void *base, size_t nmemb, size_t size, cmp_fn_t cmp);

#endif // __SORT_BITONIC_H__
