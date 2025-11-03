#include "helpers.h"
Test(fnm_period, leading_dot_segments)
{
    int f;
    f = FNM_PERIOD;
    ck_eq("*", ".hidden", f);
    ck_eq(".hid*", ".hidden", f);
    ck_eq("*.rc", ".bashrc", f);
}
