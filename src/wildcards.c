#include "internal.h"

static int at_slash(const char *s, int flags)
{
    if ((flags & FNM_PATHNAME) != 0 && *s == '/')
        return 1;
    return 0;
}

static int any_slash_rest(const char *s, int flags)
{
    if ((flags & FNM_PATHNAME) == 0)
        return 0;
    while (*s != '\0') {
        if (*s == '/')
            return 1;
        s++;
    }
    return 0;
}

static int tail_match(const char *p, const char *s, const char *s0, int flags)
{
    if (do_match(p, s, s0, flags) == 0)
        return 1;
    return 0;
}

int star_advance(const char *p, const char *s, const char *s0, int flags, int *matched)
{
    const char *pp;

    pp = p;
    while (*pp == '*')
        pp++;

    if (*pp == '\0') {
        if (any_slash_rest(s, flags) != 0 || is_leading_period(s0, s, flags) != 0)
            *matched = 0;
        else
            *matched = 1;
        return 0;
    }

    while (1) {
        if (*s == '\0') {
            *matched = tail_match(pp, s, s0, flags);
            return 0;
        }
        if (at_slash(s, flags) != 0) {
            *matched = tail_match(pp, s, s0, flags);
            return 0;
        }
        if (is_leading_period(s0, s, flags) != 0) {
            *matched = tail_match(pp, s, s0, flags);
            return 0;
        }
        if (tail_match(pp, s, s0, flags) != 0) {
            *matched = 1;
            return 0;
        }
        s++;
    }
}
