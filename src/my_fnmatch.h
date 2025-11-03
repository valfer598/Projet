#ifndef MY_FNMATCH_H
#define MY_FNMATCH_H

#include <stddef.h>

#define MY_FNM_PATHNAME  (1 << 0)
#define MY_FNM_NOESCAPE  (1 << 1)
#define MY_FNM_PERIOD    (1 << 2)
#define MY_FNM_CASEFOLD  (1 << 4)

#ifndef FNM_PATHNAME
#  define FNM_PATHNAME  MY_FNM_PATHNAME
#endif
#ifndef FNM_NOESCAPE
#  define FNM_NOESCAPE  MY_FNM_NOESCAPE
#endif
#ifndef FNM_PERIOD
#  define FNM_PERIOD    MY_FNM_PERIOD
#endif
#ifndef FNM_CASEFOLD
#  define FNM_CASEFOLD  MY_FNM_CASEFOLD
#endif

int my_fnmatch(const char *pattern, const char *string, int flags);

#endif /* !MY_FNMATCH_H */

