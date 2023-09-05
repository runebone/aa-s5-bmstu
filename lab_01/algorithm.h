#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "typedefs.h"

u32 lev_recursive(const char *str1, u32 len1, const char *str2, u32 len2);
u32 lev_iterative(const char *str1, u32 len1, const char *str2, u32 len2);
u32 damlev_iterative_with_matrix(const char *str1, u32 len1, const char *str2, u32 len2);

#endif // __ALGORITHM_H__
