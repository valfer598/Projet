#include "helpers.h"
Test(fnm_period_pathname, star_does_not_swallow_leading_dot)
{
    ck_eq("*", ".hidden", FNM_PERIOD);
    ck_eq(".*", ".hidden", FNM_PERIOD);
}
Test(fnm_period_pathname, question_and_set_with_period)
{
    ck_eq("?.txt", ".a.txt", FNM_PERIOD);
    ck_eq("[.]*", ".bashrc", FNM_PERIOD);
}
Test(fnm_period_pathname, pathname_with_slash_boundaries)
{
    int f;
    f = FNM_PATHNAME | FNM_PERIOD;
    ck_eq("*/.*", "src/.gitignore", f);
    ck_eq("*/*.c", "src/main.c", f);
    ck_eq("*/*", "a/.b", f);
    ck_eq("*/.", "a/.", f);
}
Test(fnm_pathname, star_does_not_cross_slash)
{
    ck_eq("a*", "a/b", FNM_PATHNAME);
    ck_eq("*/x", "a/b/x", FNM_PATHNAME);
    ck_eq("a/*/c", "a/b/c", FNM_PATHNAME);
}
