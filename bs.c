#include "bs.h"
#include <ctype.h>
#include <stdio.h>

int bs1(char *url, size_t len, char **ans)
{
    char *suffix;
    if (split_url(ans, &suffix, url, len))
        return 1;

    size_t loc = random_loc(*ans);

    (*ans)[loc] = bitsquat_char((*ans)[loc]);

    return 0;
}

char bitsquat_char(char c)
{
    size_t try_cnt = 0;
    do {
        c = toggle_bit(c, rand()%4);
        try_cnt++;
    } while(!isalnum(c));
#ifdef DEBUG
    fprintf(stderr, "Toggled %d bits before finding valid letter (%c).\n", (int)try_cnt, c);
#endif
    return c;
}

inline size_t random_loc(const char *str)
{
    return (size_t) rand() % strlen(str);
}

inline char toggle_bit(char c, size_t b)
{
    return c ^ (1 << b);
}

int split_url(char **name, char **suffix, char *url, size_t len)
{
    *suffix = strchr(url, '.');
    ++*suffix;

    if (strchr(*suffix, '.'))
        return -1;

    strncpy(*name, url, strlen(url) - strlen(*suffix) - 1);

    return 0;
}
