#include "internal.h"

static int handle_escape(const char **pp, const char **ss, int flags)
{
    const char *p;
    const char *s;
    p = *pp;
    s = *ss;
    if ((flags & FNM_NOESCAPE) != 0 || *p != '\\')
        return -1;
    p++;
    if (*p == '\0' || *s == '\0')
        return 1;
    if (char_eq(*p, *s, flags) == 0)
        return 1;
    *pp = p + 1;
    *ss = s + 1;
    return 0;
}

static int handle_question(const char **pp, const char **ss, const char *s0, int flags)
{
    const char *p;
    const char *s;
    p = *pp;
    s = *ss;
    if (*p != '?')
        return -1;
    if (*s == '\0')
        return 1;
    if ((flags & FNM_PATHNAME) != 0 && *s == '/')
        return 1;
    if (is_leading_period(s0, s, flags) != 0)
        return 1;
    *pp = p + 1;
    *ss = s + 1;
    return 0;
}

static int handle_set(const char **pp, const char **ss, const char *s0, int flags)
{
    const char *p, *s, *q;
    int res;
    p = *pp;
    s = *ss;
    if (*p != '[') return -1;
    if (*s == '\0') return 1;
    if ((flags & FNM_PATHNAME) != 0 && *s == '/') return 1;
    if (is_leading_period(s0, s, flags) != 0) return 1;
    q = p + 1;
    res = match_set(&q, *s, flags);
    if (res == -2) return 1;
    if (res == -1) {
        if (char_eq('[', *s, flags) == 0) return 1;
        *pp = p + 1;
        *ss = s + 1;
        return 0;
    }
    if (res == 0) return 1;
    *pp = q;
    *ss = s + 1;
    return 0;
}


static int handle_literal(const char **pp, const char **ss, int flags)
{
    const char *p;
    const char *s;
    int pc;
    p = *pp;
    s = *ss;
    pc = *p;
    if (*s == '\0')
        return 1;
    if ((flags & FNM_PATHNAME) != 0 && pc == '/' && *s != '/')
        return 1;
    if (char_eq(pc, *s, flags) == 0)
        return 1;
    *pp = p + 1;
    *ss = s + 1;
    return 0;
}

int do_match(const char *pat, const char *s, const char *s0, int flags)
{
    const char *p;
    p = pat;
    while (1) {
        int r;
        if (*p == '\0')
            return *s == '\0' ? 0 : 1;
        r = handle_escape(&p, &s, flags);
        if (r >= 0) {
            if (r != 0)
                return 1;
            continue;
        }
        if (*p == '*') {
            int m;
            star_advance(p, s, s0, flags, &m);
            return m == 1 ? 0 : 1;
        }
        r = handle_question(&p, &s, s0, flags);
        if (r >= 0) {
            if (r != 0)
                return 1;
            continue;
        }
        r = handle_set(&p, &s, s0, flags);
        if (r >= 0) {
            if (r != 0)
                return 1;
            continue;
        }
        r = handle_literal(&p, &s, flags);
        if (r != 0)
            return 1;
    }
}
