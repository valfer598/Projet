#include "helpers.h"
Test(fnm_set_escape_more, closing_bracket_escaped)
{
    ck_eq("[\\]]", "]", 0);
    ck_eq("[!\\]]", "a", 0);
}
Test(fnm_set_escape_more, dash_escaped)
{
    ck_eq("[\\-]", "-", 0);
    ck_eq("[a\\-z]", "-", 0);
    ck_eq("[\\-z]", "-", 0);
    ck_eq("[\\-z]", "y", 0);
}
Test(fnm_set_escape_more, escape_disabled_with_noescape)
{
    ck_eq("[\\]]", "\\", FNM_NOESCAPE);
    ck_eq("[\\-]", "\\", FNM_NOESCAPE);
}
