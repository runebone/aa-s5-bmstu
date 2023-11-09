#include <algorithm>
#include <cstdio>
#include <vector>
#include <wchar.h>
#include <iostream>
#include <string>

#include "sort.h"

int main()
{
    std::vector<int> vec{3, 6, 5, 7, 4, 1, 8, 2, 12, 54, 754, -1029, 34, 0, -1, 8, 38};
    /* std::vector<int> vec{3, 6, 5, 255, 4, 1, 12, 2, 32, 0, 8}; */
    /* std::vector<int> vec{3, 6, 5, 7, 4, 1, 8, 2, 18}; */
    /* std::vector<int> vec{3, 6, 5, 7, 4, 1, 8, 2}; */
    /* std::vector<int> vec{-1, 3, 2}; */
    /* std::vector<int> vec{3, 256, 2}; */
    /* std::vector<char> vec{'c', 'e', 'h', 'a', 'y', 'i', 'o', 'x', 'b', 'd', 'q', 't'}; */
    /* bitonic_sort(&vec[0], vec.size(), sizeof(vec[0]), asc<decltype(vec[0])>); */
    /* bubble_sort(&vec[0], vec.size(), sizeof(vec[0]), asc<decltype(vec[0])>); */
    /* radix_sort(&vec[0], vec.size(), sizeof(vec[0]), inverse(asc<decltype(vec[0])>)); */

    radix_sort(&vec[0], vec.size(), sizeof(vec[0]), (asc<char[sizeof(vec[0])]>));

    {
        char str[][255] = {
            "aabb",
            "qwerty",
            "abcd",
            "a",
            "bbbb",
            "bbbbb",
            "aaaa",
            "x",
            "xxxx",
            "X"
        };
        radix_sort(&str[0][0], 10, 255, asc<decltype(str[0])>);
        for (int i = 0; i < 10; i++)
            printf("%s ", str[i]);
        printf("\n");
    }

    for (auto v : vec)
        printf("%d ", v);
    printf("\n");
}
