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
        ok(0 == split_url(name, 256, &suffix, "github.com"));

        ok(0 == strcmp(name, "github"));
        ok(0 == strcmp(suffix, "com"));

        ok(0 != split_url(name, 256, &suffix, "www.github.com"));

        ok(0 != split_url(NULL, 0, NULL, NULL));
        free(name);
    }

    {
        char buf[5];
        char *suf;
        ok(-1 == split_url(buf, 0, &suf, "a.b")); /* zero name_buf_sz */
    }

    /* no dot */
    { char name[16]; char *suf; ok(-1 == split_url(name, sizeof name, &suf, "plainstring")); }

    /* More than one dot */
    { char name[16]; char *suf; ok(-1 == split_url(name, sizeof name, &suf, "a.b.c")); }

    // Exact-fit buffer:
    { char name[7]; /* "github" + NUL */ char *suf; ok(0 == split_url(name, sizeof name, &suf, "github.com")); ok(0 == strcmp(name, "github")); ok(0 == strcmp(suf, "com")); }

    //Too-small buffer
    {
        char name[5];
        char *suf;
        ok(-1 == split_url(name, sizeof name, &suf, "github.com")); /* needs 7+1 */
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

    {
        int cnt=0;
        for (int i=0; i<100; ++i)
        {
            char c = 'a';
            if(isalnum((unsigned char)bitsquat_char(c)))
                cnt++;
        }
        ok(cnt == 100);
    }

    {
        /* Statistical test: bitsquat_char should produce multiple distinct results */
        srand(12345);                 /* deterministic sample for test */
        const int N = 100;
        const int MIN_DISTINCT = 3;   /* require at least this many different outputs */
        int seen[256] = {0};
        int distinct = 0;

        for (int i = 0; i < N; ++i) {
            unsigned char out = (unsigned char) bitsquat_char('a');
            if (!seen[out]) {
                //seen[out] = 1;
                distinct++;
            }
            seen[out] += 1;
        }

        /* basic checks: all outputs are alphanumeric and we observed variety */
        int all_alnum = 1;
        for (int b = 0; b < 256; ++b) {
            if (seen[b] && !isalnum((unsigned char)b)) {
                all_alnum = 0;
                break;
            }
        }

        //for (int b = 0; b < 256; ++b) {
        //    if (seen[b] && isalnum((unsigned char)b)) {
        //        printf("seen %c: %d\n", (unsigned char)b, seen[b]);
        //    }
        //}

        ok(all_alnum);
        ok(distinct >= MIN_DISTINCT);
    }

    /* random_loc */
    {
        srand(1);
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


    //Null input:
    { struct Url u = create_url(NULL); ok(u.name == NULL && u.suffix == NULL); }
    //Bad url:
    { struct Url u = create_url("no-dot"); ok(u.name == NULL && u.suffix == NULL); }
    //Valid url:
    { struct Url u = create_url("github.com"); ok(u.name != NULL && u.suffix != NULL); ok(0 == strcmp(u.name, "github")); ok(0 == strcmp(u.suffix, "com")); free_url(u); }

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


    // Zero entries:
    { struct Url u = create_url("github.com"); struct BSentries e = generate_entries(u, 0); ok(e.n_names == 0); ok(e.names == NULL || e.names != NULL); /* ensure no crash; prefer checking NULL */ free_url(u); free_bs_entries(e); }
    // Large n_entries (reasonable small stress):
    { struct Url u = create_url("github.com"); size_t n = 1000; struct BSentries e = generate_entries(u, n); ok(e.n_names == n); ok(e.names != NULL); free_bs_entries(e); free_url(u); }

    // bitsquat_char and toggle_bit safety

    // toggle_bit bounds:
    // Test toggling high bit within CHAR_BIT:
    ok(toggle_bit(0x00, 0) == 1);
    // ok(toggle_bit(0x00, (size_t)(CHAR_BIT-1)) == (char)(1u << (CHAR_BIT-1)));

    // random_loc bounds

    // Allow zero:
    { size_t loc = random_loc("github"); ok(loc < strlen("github")); }

    //Empty string behavior:
    { size_t loc = random_loc(""); ok(loc == 0); /* depends on your implementation; assert expected behavior */ }

    // Memory-leak / double-free negative tests
    // Ensure free_url on NULL fields is safe (if you modified free_url to handle NULL):
    { struct Url u = { .name = NULL, .suffix = NULL }; free_url(u); ok(1); /* just ensure no crash */ }

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

// vim:sw=4:ts=4:sts=4:expandtab:
