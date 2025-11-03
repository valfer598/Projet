#include "helpers.h"
Test(star_collapse, multiple_stars_equivalence)
{
    ck_eq("**", "", 0);
    ck_eq("**", "abc", 0);
    ck_eq("a**c", "ac", 0);
    ck_eq("a***c", "abbbc", 0);
}
Test(star_collapse, star_before_after_question)
{
    ck_eq("*?*", "x", 0);
    ck_eq("*?*", "abcd", 0);
}
