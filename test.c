#ifdef UNIT_TEST

#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ok(a) if ((a)) { printf("ok\n"); } else \
{ printf("not ok - row %s:%d\n", __FILE__, __LINE__); }

int is_valid_str(char *buf, int len);

int main()
{
    /* toggle_bit */
    ok(7 == toggle_bit(0b0101, 1));
    ok(0b0100 == toggle_bit(0b0101, 0));
    ok(0b0111 == toggle_bit(0b1111, 3));

    /* split_url */
    {
        char *name, *suffix;
        name = malloc(256*sizeof(char));
        ok(0 == split_url(&name, &suffix, "github.com", 10));

        ok(0 == strcmp(name, "github"));
        ok(0 == strcmp(suffix, "com"));

        ok(0 != split_url(&name, &suffix, "www.github.com", 10));
        free(name);
    }

    /* is_valid_str */
    ok(is_valid_str("github", 6));
    ok(!is_valid_str("github.com", 10));
    ok(is_valid_str("g1thub", 6));

    /* bitsquat_char */
    {
        char c = 'a';
        ok('a' != bitsquat_char(c));
    }

    /* random_loc */
    {
        size_t loc = random_loc("github");
        ok(loc > 0 && loc < 6);
    }

    /* bs1 */
    {
        char *ans, *suffix;
        srand(time(NULL));

        ans = malloc(256*sizeof(char));
        ok(0 == bs1("github.com", 10, &ans));
        ok(is_valid_str(ans, 6));
        printf("res: %s\n", ans);
        free(ans);
    }

    /* create_url */
    {
        struct url m_url;
        m_url = create_url("github.com");
        ok(0 == strcmp(m_url.name, "github"));
        ok(0 == strcmp(m_url.suffix, "com"));
    }

    return 0;
}

int is_valid_str(char *buf, int len)
{
    int is_valid = 1;
    int i;
    for (i=0; i<len; ++i) {
        if (!isalnum(buf[i])) {
            is_valid = 0;
        }
    }
    return is_valid;
}

#endif /* UNIT_TEST */
