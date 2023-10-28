size_t *min4(size_t *a, size_t *b, size_t *c, size_t *d)
{
    size_t *result;
    size_t min = std::min(std::min(*a, *b), std::min(*c, *d));

    if (min == *a)
        result = a;
    else if (min == *b)
        result = b;
    else if (min == *c)
        result = c;
    else
        result = d;

    return result;
}
