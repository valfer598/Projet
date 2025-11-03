#include "helpers.h"
Test(dotmix, period_at_start_no_flag)
{
    ck_eq("*", ".a", 0);
    ck_eq("?.txt", ".a.txt", 0);
    ck_eq("[.]*", ".bashrc", 0);
}
Test(dotmix, period_inside_segment_period_flag)
{
    ck_eq("a.*.c", "a..c.c", FNM_PERIOD);
    ck_eq("*.*", "a.b", FNM_PERIOD);
    ck_eq("*.*", "a..b", FNM_PERIOD);
}
