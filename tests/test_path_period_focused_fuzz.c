#include "helpers.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fnmatch.h>
static int rndi(int m) { return rand() % m; }
static void gen_seg(char *dst, int len, int leading_dot)
{
    int i;
    if (len <= 0) { dst[0] = '\0'; return; }
    dst[0] = leading_dot ? '.' : (char)('a' + rndi(26));
    for (i = 1; i < len; i++)
        dst[i] = (char)('a' + rndi(26));
    dst[len] = '\0';
}
static void gen_path(char *buf, int maxlen)
{
    int nseg;
    int i;
    char seg[16];
    size_t pos;
    nseg = 1 + rndi(5);
    pos = 0;
    for (i = 0; i < nseg; i++) {
        int ld;
        size_t ls;
        ld = rndi(6) == 0 ? 1 : 0;
        gen_seg(seg, 1 + rndi(5), ld);
        if (pos != 0 && pos + 1 < (size_t)maxlen)
            buf[pos++] = '/';
        ls = strlen(seg);
        if (pos + ls < (size_t)maxlen) {
            memcpy(buf + pos, seg, ls);
            pos += ls;
        }
    }
    buf[pos] = '\0';
}

static void gen_pat(char *buf, int maxlen)
{
    const char *atoms[] = {"*", "?", "[a-z]", "[!a-z]", "\\*", "\\?", ".", "/" "*", "/?"};
    int i;
    size_t pos;
    pos = 0;
    for (i = 0; i < 5 && pos + 4 < (size_t)maxlen; i++) {
        const char *a;
        size_t la;
        a = atoms[rndi((int)(sizeof(atoms) / sizeof(atoms[0])))];
        la = strlen(a);
        memcpy(buf + pos, a, la);
        pos += la;
        if (rndi(2) && pos + 1 < (size_t)maxlen)
            buf[pos++] = '/';
    }
    buf[pos] = '\0';
}


Test(focus_fuzz, pathname_period_focus)
{
    unsigned int seed;
    int iters;
    int i;
    char pat[256];
    char str[256];
    int flags;
    seed = (unsigned int)time(NULL);
    iters = 5000;
    flags = FNM_PATHNAME | FNM_PERIOD;
    srand(seed);
    cr_log_info("focus seed=%u iters=%d\n", seed, iters);
    for (i = 0; i < iters; i++) {
        int ref;
        int got;
        gen_pat(pat, 255);
        gen_path(str, 255);
        ref = fnmatch(pat, str, flags);
        got = my_fnmatch(pat, str, flags);
        if (got != (ref == 0 ? 0 : 1)) {
            cr_log_error("Mismatch seed=%u iter=%d\npat=%s\nstr=%s\nflags=%d\n", seed, i, pat, str, flags);
            cr_assert_fail("focus fuzz mismatch");
        }
    }
}
