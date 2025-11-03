#include "helpers.h"
Test(fnm_basics, literals_and_sets)
{
    ck_eq("abc", "abc", 0);
    ck_eq("a?c", "abc", 0);
    ck_eq("a*c", "axxxc", 0);
    ck_eq("*", "", 0);
    ck_eq("[]-]", "]", 0);
    ck_eq("[?*]", "*", 0);
    ck_eq("[!x]", "a", 0);
    ck_eq("[a-f0-9]", "e", 0);
    ck_eq("[a-f0-9]", "7", 0);
}
