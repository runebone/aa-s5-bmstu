#include <algorithm>
#include <cstdio>
#include <vector>
#include <wchar.h>
#include <iostream>

#include "sort.h"

int main()
{
    std::vector<int> vec{3, 6, 5, 7, 4, 1, 8, 2, 12, 54, 754, 34, 0, -1, 8, 38};

    /* bitonic_sort(&vec[0], vec.size(), sizeof(vec[0]), asc<decltype(vec[0])>); */
    bubble_sort(&vec[0], vec.size(), sizeof(vec[0]), asc<decltype(vec[0])>);

    for (auto v : vec)
        printf("%d ", v);
    printf("\n");
}
