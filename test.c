#include "bs.h"
#include <stdio.h>

#define ok(a) if ((a)) { printf("ok\n"); } else \
{ printf("not ok - row %s:%d\n", __FILE__, __LINE__); }

int main()
{
    /* toggle_bit */
    ok(7 == toggle_bit(0b0101, 1));
    ok(0b0100 == toggle_bit(0b0101, 0));
    ok(0b0111 == toggle_bit(0b1111, 3));

    /* split_url */
    {
        char name[256], *suffix;
        ok(0 == split_url(name, &suffix, "github.com", 10));

        ok(0 == strcmp(name, "github"));
        ok(0 == strcmp(suffix, "com"));

        ok(0 != split_url(name, &suffix, "www.github.com", 10));
    }

    /* is_valid_str */
    ok(is_valid_str("github", 6));
    ok(!is_valid_str("github.com", 10));
    ok(is_valid_str("g1thub", 6));

    return 0;
}
