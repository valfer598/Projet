#include "internal.h"

int my_fnmatch(const char *pattern, const char *string, int flags)
{
    if (pattern == NULL || string == NULL)
        return 1;
    return do_match(pattern, string, string, flags);
}
