/**
 * LICENSE
 *
 * Use this software at your own risk. The author(s) and contributors provide the
 * code "as is", without warranty of any kind, express or implied, including but
 * not limited to warranties of merchantability, fitness for a particular purpose,
 * or non-infringement. The author(s) and contributors are not liable for any
 * direct, indirect, incidental, special, exemplary, or consequential damages
 * (including, without limitation, procurement of substitute goods or services;
 * loss of use, data, or profits; or business interruption) arising out of the use
 * or inability to use the software, even if advised of the possibility of such
 * damages.
 *
 * This project performs operations on input strings and allocates memory;
 * improper use, malformed input, or modification of the code may cause crashes,
 * memory corruption, data loss, or security vulnerabilities. You are responsible
 * for reviewing, testing, and securing the code before using it in production or
 * on sensitive systems.
 *
 * If you redistribute or modify the software, you must do so under the terms of
 * its license and retain this disclaimer in accompanying documentation.
 *
 **/

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
