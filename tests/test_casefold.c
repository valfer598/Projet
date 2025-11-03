#include "helpers.h"
Test(fnm_casefold, ascii_insensitive)
{
    int f;
    f = FNM_CASEFOLD;
    ck_eq("aBc", "AbC", f);
    ck_eq("[a-f]", "E", f);
    ck_eq("ab*", "ABcd", f);
}
