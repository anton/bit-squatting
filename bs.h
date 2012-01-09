#include <string.h>

struct Url {
    char *name;
    char *suffix;
};

struct BSentries {
    char *suffix;
    char **names;
    size_t namelen;
    size_t n_names;
};

struct Url create_url(char *);
struct BSentries generate_entries(struct Url url, size_t n_entries);
void bitsquat_entries(struct BSentries bs_entries);
void print_bs_entries(struct BSentries bs_entries);

void free_url(struct Url url);
void free_bs_entries(struct BSentries bs_entries);

#ifdef UNIT_TEST
inline char toggle_bit(char c, size_t b);
int split_url(char **name, char **suffix, char *buf);
inline size_t random_loc(const char *str);
char bitsquat_char(char c);
#endif /* UNIT_TEST */
