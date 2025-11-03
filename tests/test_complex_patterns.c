#include "helpers.h"
Test(complex_patterns, mingle_all)
{
    ck_eq("[!a-c]*?x[.-z]", "defx.", 0);
    ck_eq("[!a-c]*?x[.-z]", "xyzx-", 0);
}
Test(complex_patterns, pathname_period_flags)
{
    int f;
    f = FNM_PATHNAME | FNM_PERIOD;
    ck_eq("*.[a-z]/*", "a.b/c", f);
    ck_eq("?*/*.[ch]", "src/x/main.c", f);
}
