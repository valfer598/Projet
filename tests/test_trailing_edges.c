#include "helpers.h"
Test(trailing_edges, trailing_backslash)
{
    ck_eq("\\", "\\", 0);
    ck_eq("a\\", "a\\", 0);
}
Test(trailing_edges, trailing_open_bracket)
{
    ck_eq("[", "[", 0);
    ck_eq("x[", "x[", 0);
}
