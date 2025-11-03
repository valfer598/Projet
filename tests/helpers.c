#include "helpers.h"
void ck_eq(const char *pat, const char *s, int f)
{
    int ref;
    int got;
    int ref01;
    ref = fnmatch(pat, s, f);
    got = my_fnmatch(pat, s, f);
    ref01 = (ref == 0) ? 0 : 1;
    cr_assert_eq(got, ref01, "pat='%s' s='%s' flags=%d -> got=%d ref=%d", pat, s, f, got, ref01);
}
