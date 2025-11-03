#include "helpers.h"
Test(path_combos, nested_segments)
{
    ck_eq("*/*/*", "a/b/c", FNM_PATHNAME);
    ck_eq("*/*/*", "a/b/c/d", FNM_PATHNAME);
    ck_eq("*/*", "ab/cd", FNM_PATHNAME);
}
Test(path_combos, mixed_question_star)
{
    ck_eq("a?/*", "ab/x", FNM_PATHNAME);
    ck_eq("?" "?" "/" "*", "ab/c", FNM_PATHNAME);
    ck_eq("?" "*" "/" "?", "ab/c", FNM_PATHNAME);
}

