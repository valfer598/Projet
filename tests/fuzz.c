#include "helpers.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fnmatch.h>
static const char ALPHA[] = "abcxyz012345/._-";
static const char META[] = "*?[]\\";
static int rnd(int max) { return rand() % max; }
static char rnd_alpha(void) { return ALPHA[rnd((int)sizeof(ALPHA) - 1)]; }
static char rnd_meta(void) { return META[rnd((int)sizeof(META) - 1)]; }
static void gen_pattern(char *buf, int maxlen)
{
    int n;
    int target;
    n = 0;
    target = 1 + rnd(maxlen - 2);
    while (n < target) {
        int t;
        char c;
        t = rnd(10);
        if (t < 6) c = rnd_alpha(); else c = rnd_meta();
        if (c == '[' && n + 4 < maxlen) {
            buf[n++] = '[';
            buf[n++] = 'a';
            buf[n++] = '-';
            buf[n++] = 'z';
            buf[n++] = ']';
            continue;
        }
        buf[n++] = c;
    }
    buf[n] = '\0';
}
static void gen_string(char *buf, int maxlen)
{
    int n;
    int target;
    n = 0;
    target = 1 + rnd(maxlen - 2);
    while (n < target) {
        buf[n++] = rnd_alpha();
    }
    buf[n] = '\0';
}
static int gen_flags(void)
{
    int f;
    f = 0;
    if (rnd(2)) f |= FNM_PATHNAME;
    if (rnd(2)) f |= FNM_NOESCAPE;
    if (rnd(2)) f |= FNM_PERIOD;
    if (rnd(2)) f |= FNM_CASEFOLD;
    return f;
}
Test(fuzz, random_compare_to_system)
{
    const char *seed_env;
    const char *iters_env;
    unsigned int seed;
    int iters;
    char pat[256];
    char str[256];
    int i;
    seed_env = getenv("FUZZ_SEED");
    iters_env = getenv("FUZZ_ITERS");
    seed = (unsigned int)(seed_env ? strtoul(seed_env, NULL, 10) : (unsigned int)time(NULL));
    iters = iters_env ? atoi(iters_env) : 2000;
    srand(seed);
    cr_log_info("FUZZ seed=%u iters=%d\n", seed, iters);
    for (i = 0; i < iters; i++) {
        int f;
        int ref;
        int got;
        gen_pattern(pat, 255);
        gen_string(str, 255);
        f = gen_flags();
        ref = fnmatch(pat, str, f);
        got = my_fnmatch(pat, str, f);
        if (got != (ref == 0 ? 0 : 1)) {
            cr_log_error("Mismatch at iter=%d seed=%u\n", i, seed);
            cr_log_error("pat='%s' str='%s' flags=%d ref=%d got=%d\n", pat, str, f, ref == 0 ? 0 : 1, got);
            cr_assert_fail("Fuzzer found a mismatch");
        }
    }
}
