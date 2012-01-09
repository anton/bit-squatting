#ifdef UNIT_TEST

#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

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
        ok(0 == split_url(&name, &suffix, "github.com"));

        ok(0 == strcmp(name, "github"));
        ok(0 == strcmp(suffix, "com"));

        ok(0 != split_url(&name, &suffix, "www.github.com"));
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

    /* create_url */
    {
        struct Url m_url;
        m_url = create_url("github.com");
        ok(0 == strcmp(m_url.name, "github"));
        ok(0 == strcmp(m_url.suffix, "com"));
        free_url(m_url);
    }

    /* generate_entries and bitsquat_entries */
    {
        struct BSentries bs_entries;
        struct Url url = create_url("github.com");
        bs_entries = generate_entries(url, 3);
        ok(3 == bs_entries.n_names);
        ok(0 == strcmp(bs_entries.suffix, "com"));
        ok(0 == strcmp(bs_entries.names[0], "github"));

        bitsquat_entries(bs_entries);
        ok(0 != strcmp(bs_entries.names[0], "github"));

        free_url(url);
        free_bs_entries(bs_entries);
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
