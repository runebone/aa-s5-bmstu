size_t *min3(size_t *a, size_t *b, size_t *c)
{
    size_t *result;
    size_t min = std::min(*a, std::min(*b, *c));

    if (min == *a)
        result = a;
    else if (min == *b)
        result = b;
    else
        result = c;

    return result;
}
