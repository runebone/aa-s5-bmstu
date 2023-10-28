size_t damerau_levenshtein_recursive_no_cache(const wchar_t *str1, size_t len1, const wchar_t *str2, size_t len2)
{
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;

    size_t insert = damerau_levenshtein_recursive_no_cache(str1, len1, str2, len2 - 1) + 1;
    size_t del = damerau_levenshtein_recursive_no_cache(str1, len1 - 1, str2, len2) + 1;
    size_t replace = damerau_levenshtein_recursive_no_cache(str1, len1 - 1, str2, len2 - 1)
        + (str1[len1 - 1] == str2[len2 - 1] ? 0 : 1);
    size_t swap = (len1 >= 2 && len2 >= 2)
        ? (
                (str1[len1 - 1] == str2[len2 - 2] && str1[len1 - 2] == str2[len2 - 1])
                ? damerau_levenshtein_recursive_no_cache(str1, len1 - 2, str2, len2 - 2) + 1
                : U_INF
          )
        : U_INF;

    return *min4(&insert, &del, &replace, &swap);
}
