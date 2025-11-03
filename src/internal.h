#ifndef INTERNAL_H
#define INTERNAL_H

#include <stddef.h>
#include "my_fnmatch.h"

int ascii_tolower(int c);
int tofold(int c, int flags);
int char_eq(int a, int b, int flags);
int is_leading_period(const char *s0, const char *s, int flags);

int next_pchar(const char **pp, int *out, int flags);

int match_set(const char **pp, int c, int flags);

int star_advance(const char *p, const char *s, const char *s0, int flags, int *matched);

int do_match(const char *pat, const char *s, const char *s0, int flags);

#endif /* !INTERNAL_H */
