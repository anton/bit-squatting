#include "bs.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Toggle one bit
 *
 * Toggle one bit in a character
 *
 * @param c The character which bit should be toggled.
 * @param b The position of the bit that should be toggled.
 * @return The character with the bit toggled.
 */
inline char toggle_bit(char c, size_t b)
{
    return c ^ (1 << b);
}

/**
 * Bitsquat a character
 *
 * Choose a random bit in the character and toggle it. The function only return
 * when an alphanumeric character is found.
 *
 * @param c Character that should be bitsquatted.
 * @return The bitsquatted character.
 */
char bitsquat_char(char c)
{
    size_t try_cnt = 0;
    char bs_char;
    do {
        bs_char = toggle_bit(c, rand()%4);
        try_cnt++;
    } while(!isalnum(bs_char));
#ifdef DEBUG
    fprintf(stderr, "Toggled %d bits before finding valid letter (%c).\n", (int)try_cnt, c);
#endif
    return bs_char;
}

/**
 * Random location
 *
 * Choose a random location of a letter in a string and return the location of
 * it.
 *
 * @param str The string to choose from.
 * @return Location of random letter.
 */
inline size_t random_loc(const char *str)
{
    return (size_t) rand() % strlen(str);
}

/**
 * Split url
 *
 * Split a string containing an url into two parts: The part before the dot is
 * the name and the part after the dot is the suffix. If a url contains more
 * than one dot an error will be generated. name and suffix has to be allocated
 * beforehand. The function will return 0 on success. -1 if failure.
 *
 * @param name Return value, the part in front of the dot.
 * @param suffix Return value, the part after the dot.
 * @param url The string with url that should be considered.
 * @return The function will return 0 on success.
 */
int split_url(char **name, char **suffix, char *url)
{
    *suffix = strchr(url, '.');
    ++*suffix;

    if (strchr(*suffix, '.'))
        return -1;

    strncpy(*name, url, strlen(url) - strlen(*suffix) - 1);

    return 0;
}

/**
 * Create url
 *
 * The function will create a struct Url from a string containing an url.
 *
 * @param buf The string containing an url.
 * @return The url as a struct Url.
 */
struct Url create_url(char *buf)
{
    struct Url m_url;

    m_url.name = malloc(256*sizeof(char));

    if (split_url(&m_url.name, &m_url.suffix, buf)) {
        free(m_url.name);
    }

    return m_url;
}

/**
 * Generate entries
 *
 * Take a struct Url and generate the specified number of entries as a struct
 * BSentries.
 *
 * @param url The struct Url.
 * @param n_entries Number of entries to be generated.
 * @return The generated struct.
 */
struct BSentries generate_entries(struct Url url, size_t n_entries)
{
    struct BSentries bs_entries;
    size_t i;

    bs_entries.suffix = url.suffix;
    bs_entries.n_names = n_entries;
    bs_entries.names = calloc(n_entries, sizeof(char *));
    bs_entries.namelen = strlen(url.name);

    for (i=0; i<n_entries; ++i) {
        bs_entries.names[i] = strdup(url.name);
    }

    return bs_entries;
}

/**
 * Bitsquat entries
 *
 * Take a stuct BSentries and bitsquat them.
 *
 * @param bs_entries The struct BSentries to be bitsquatted.
 */
void bitsquat_entries(struct BSentries bs_entries)
{
    size_t i;

    for (i=0; i<bs_entries.n_names; ++i) {
        char *entry = bs_entries.names[i];
        size_t loc = random_loc(entry);
        entry[loc] = bitsquat_char(entry[loc]);
    }

    return;
}

/**
 * Free url
 *
 * Deallocated space.
 *
 * @param url The struct Url to be free'd.
 */
void free_url(struct Url url)
{
    free(url.name);
    return;
}

/**
 * Free BSentries
 *
 * Deallocated space.
 *
 * @param url The struct BSentries to be free'd.
 */
void free_bs_entries(struct BSentries bs_entries)
{
    size_t i;
    for (i=0; i<bs_entries.n_names; ++i) {
        free(bs_entries.names[i]);
    }
    free(bs_entries.names);
    return;
}

/**
 * Print BSentries
 *
 * Print a struct BSentries to stdout.
 *
 * @param bs_entries The BSentries struct to be printed.
 */
void print_bs_entries(struct BSentries bs_entries)
{
    size_t i;

    for (i=0; i<bs_entries.n_names; ++i) {
        printf("%s.%s\n", bs_entries.names[i], bs_entries.suffix);
    }

    return;
}
