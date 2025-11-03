#include "helpers.h"
Test(fnm_unclosed, left_bracket_literal_if_unclosed)
{
    ck_eq("[", "[", 0);
    ck_eq("[abc", "[abc", 0);
    ck_eq("x[abc", "x[abc", 0);
}
Test(fnm_unclosed, range_unfinished_treated_as_literal)
{
    ck_eq("[a-", "[a-", 0);
    ck_eq("[!-", "[!-", 0);
}
