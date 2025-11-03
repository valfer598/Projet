#include "helpers.h"
Test(escape_sets_extra, escaped_closing_and_dash)
{
    ck_eq("[\\]]", "]", 0);
    ck_eq("[\\-]", "-", 0);
    ck_eq("[a\\-z]", "-", 0);
}
Test(escape_sets_extra, noescape_disables_escape)
{
    ck_eq("[\\]]", "\\", FNM_NOESCAPE);
    ck_eq("[\\-]", "\\", FNM_NOESCAPE);
    ck_eq("[a\\-z]", "\\", FNM_NOESCAPE);
}
