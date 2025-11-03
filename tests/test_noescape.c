#include "helpers.h"
Test(fnm_noescape, backslash_behavior)
{
    ck_eq("\\*", "*", 0);
    ck_eq("\\*", "\\abc", FNM_NOESCAPE);
}
