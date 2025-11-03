#include "helpers.h"
Test(fnm_escape, backslash_literals_default)
{
    ck_eq("\\*", "*", 0);
    ck_eq("\\?", "?", 0);
    ck_eq("\\[", "[", 0);
    ck_eq("\\\\", "\\", 0);
}
Test(fnm_escape, backslash_ignored_with_noescape)
{
    ck_eq("\\*", "\\*", FNM_NOESCAPE);
    ck_eq("\\[", "\\[", FNM_NOESCAPE);
}
Test(fnm_escape, trailing_backslash_is_invalid)
{
    ck_eq("\\", "x", 0);
}
Test(fnm_escape, escape_inside_set_literal)
{
    ck_eq("[\\]]", "]", 0);
}
