#include "helpers.h"
Test(fnm_pathname, slash_handling)
{
    int f;
    f = FNM_PATHNAME;
    ck_eq("a/*/c", "a/b/c", f);
    ck_eq("a*", "a/b", f);
    ck_eq("*/x", "a/b/x", f);
    ck_eq("a[/]b", "a/b", f);
}
