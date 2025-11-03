#include "internal.h"

int next_pchar(const char **pp, int *out, int flags)
{
    const char *p;

    p = *pp;
    if (*p == '\0') {
        *out = 0;
        return 0;
    }
    if ((flags & FNM_NOESCAPE) == 0 && *p == '\\') {
        p++;
        if (*p == '\0')
            return -1;
        *out = *p;
        *pp = p + 1;
        return 1;
    }
    *out = *p;
    *pp = p + 1;
    return 1;
}
