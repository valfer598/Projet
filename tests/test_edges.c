#include "helpers.h"
Test(fnm_edges, oddities)
{
    ck_eq("[!]", "!", 0);
    ck_eq("[!]", "a", 0);
    ck_eq("[", "[", 0);
    ck_eq("\\", "x", 0);
    ck_eq("", "", 0);
}
