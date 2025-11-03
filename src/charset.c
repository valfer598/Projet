#include "internal.h"

static void fold3(int *a, int *b, int *c, int flags)
{
    if ((flags & FNM_CASEFOLD) != 0) {
        if (*a >= 0 && *a <= 255) *a = ascii_tolower(*a);
        if (*b >= 0 && *b <= 255) *b = ascii_tolower(*b);
        if (*c >= 0 && *c <= 255) *c = ascii_tolower(*c);
    }
}

static int take_char(const char **p, int flags, int *out, int *escaped)
{
    const char *q;
    q = *p;
    *escaped = 0;
    if ((flags & FNM_NOESCAPE) == 0 && *q == '\\' && q[1] != '\0') {
        *out = q[1];
        *p = q + 2;
        *escaped = 1;
        return 1;
    }
    if (*q == '\0') return 0;
    *out = *q;
    *p = q + 1;
    return 1;
}

static const char *prolog(const char *p, int c, int *neg, int *ok, int *prev, int *seen)
{
    if (*p == '!') { *neg = 1; p++; }
    if (*p == ']') { if (c == ']') *ok = 1; p++; *prev = ']'; *seen = 1; }
    return p;
}

static int scan(const char **p, int c, int flags, int forbid, int *ok, int *prev, int *seen, int *want_unfinished_range)
{
    int cur, esc;
    while (**p != '\0' && **p != ']') {
        if (take_char(p, flags, &cur, &esc) == 0) break;
        *seen = 1;
        if (cur == '-' && esc == 0 && *prev != -2) {
            int endc, esce;
            if (**p == '\0' || **p == ']') { *want_unfinished_range = 1; cur = '-'; goto LIT; }
            if (take_char(p, flags, &endc, &esce) == 0) return -1;
            if (forbid == 0) { int aa, bb, cc; aa = *prev; bb = endc; cc = c; fold3(&aa, &bb, &cc, flags); if (aa <= cc && cc <= bb) *ok = 1; }
            *prev = -2;
            continue;
        }
LIT:
        if (forbid == 0 && char_eq(cur, c, flags) != 0) *ok = 1;
        *prev = cur;
    }
    return 0;
}

int match_set(const char **pp, int c, int flags)
{
    const char *p;
    int neg, ok, forbid, prev, st, seen, want_unfinished_range;
    p = *pp;
    neg = 0;
    ok = 0;
    forbid = ((flags & FNM_PATHNAME) != 0 && c == '/');
    prev = -2;
    seen = 0;
    want_unfinished_range = 0;
    p = prolog(p, c, &neg, &ok, &prev, &seen);
    st = scan(&p, c, flags, forbid, &ok, &prev, &seen, &want_unfinished_range);
    if (st < 0) return -1;
    if (*p != ']') {
        if (want_unfinished_range != 0) return -2;
        return -1;
    }
    *pp = p + 1;
    if (neg != 0) ok = ok ? 0 : 1;
    return ok;
}
