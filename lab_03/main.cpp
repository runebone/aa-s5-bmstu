#include <algorithm>
#include <cstdio>
#include <vector>
#include <wchar.h>
#include <iostream>

#include "sort.h"

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
