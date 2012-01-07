#include "bs.h"
#include <ctype.h>
#include <string.h>

inline int toggle_bit(char c, int b)
{
    return c ^ (1 << b);
}

int split_url(char *name, char **suffix, char *buf, int len)
{
    *suffix = strchr(buf, '.');
    ++*suffix;

    if (strchr(*suffix, '.'))
        return -1;

    strncpy(name, buf, strlen(buf) - strlen(*suffix) - 1);

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
