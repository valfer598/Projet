#include "helpers.h"
#include <string.h>
static void repeat(char *dst, const char *pat, int times)
{
    int i;
    size_t len;
    len = strlen(pat);
    for (i = 0; i < times; i++)
        memcpy(dst + (size_t)i * len, pat, len);
    dst[(size_t)times * len] = '\0';
}
Test(fnm_long, long_star_runs)
{
    char p[4096];
    char s[4096];
    repeat(p, "*", 2000);
    repeat(s, "ab", 1800);
    ck_eq(p, s, 0);
}
Test(fnm_long, deep_slash_segments_pathname)
{
    char p[4096];
    char s[4096];
    strcpy(p, "*/*/*/*/*/*/*/*/*/*");
    strcpy(s, "a/b/c/d/e/f/g/h/i/j");
    ck_eq(p, s, FNM_PATHNAME);
}
Test(fnm_long, many_sets)
{
    char p[4096];
    char s[4096];
    int i;
    char *q;
    q = p;
    for (i = 0; i < 1000; i++) {
        *q++ = '[';
        *q++ = 'a';
        *q++ = ']';
    }
    *q = '\0';
    memset(s, 'a', 1000);
    s[1000] = '\0';
    ck_eq(p, s, 0);
}
