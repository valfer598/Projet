#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H
#include <criterion/criterion.h>
#include <fnmatch.h>
#include "../src/my_fnmatch.h"
void ck_eq(const char *pat, const char *s, int f);
#endif
