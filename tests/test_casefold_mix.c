#include "helpers.h"
Test(casefold_mix, sets_and_literals)
{
    ck_eq("[a-z]X", "eX", FNM_CASEFOLD);
    ck_eq("[A-Z]x", "ex", FNM_CASEFOLD);
    ck_eq("Te*St", "tEzzzst", FNM_CASEFOLD);
}
Test(casefold_mix, question_star_casefold)
{
    ck_eq("?*", "Ä", FNM_CASEFOLD);
    ck_eq("a?c", "AbC", FNM_CASEFOLD);
}
