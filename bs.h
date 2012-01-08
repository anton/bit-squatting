#ifdef UNIT_TEST
#include <string.h>

inline char toggle_bit(char c, size_t b);
int split_url(char **name, char **suffix, char *buf, size_t len);
int bs1(char *url, size_t len, char **ans);
inline size_t random_loc(const char *str);
char bitsquat_char(char c);
#endif /* UNIT_TEST */
