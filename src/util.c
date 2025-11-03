#include "internal.h"

int ascii_tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

int tofold(int c, int flags)
{
    if ((flags & FNM_CASEFOLD) != 0 && c >= 0 && c <= 255)
        return ascii_tolower(c);
    return c;
}

int char_eq(int a, int b, int flags)
{
    int x;
    int y;

    x = tofold(a, flags);
    y = tofold(b, flags);
    return x == y;
}

int is_leading_period(const char *s0, const char *s, int flags)
{
    if ((flags & FNM_PERIOD) == 0)
        return 0;
    if (*s != '.')
        return 0;
    if (s == s0)
        return 1;
    if ((flags & FNM_PATHNAME) != 0 && s > s0 && *(s - 1) == '/')
        return 1;
    return 0;
}
