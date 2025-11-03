#include "helpers.h"
Test(fnm_sets_ranges, simple_membership)
{
    ck_eq("[abc]", "a", 0);
    ck_eq("[abc]", "b", 0);
    ck_eq("[abc]", "d", 0);
}
Test(fnm_sets_ranges, leading_closing_bracket_and_dash)
{
    ck_eq("[]-]", "]", 0);
    ck_eq("[--/]", "-", 0);
    ck_eq("[--/]", ".", 0);
    ck_eq("[--/]", "/", 0);
}
Test(fnm_sets_ranges, negation)
{
    ck_eq("[!a]", "a", 0);
    ck_eq("[!a]", "b", 0);
    ck_eq("[!abc]", "d", 0);
}
Test(fnm_sets_ranges, ranges_ascii)
{
    ck_eq("[a-f0-9]", "a", 0);
    ck_eq("[a-f0-9]", "f", 0);
    ck_eq("[a-f0-9]", "0", 0);
    ck_eq("[a-f0-9]", "9", 0);
}
Test(fnm_sets_ranges, casefold_ranges)
{
    ck_eq("[a-f]", "E", FNM_CASEFOLD);
    ck_eq("[A-F]", "e", FNM_CASEFOLD);
}
