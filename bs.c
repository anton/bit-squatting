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
char toggle_bit(char c, size_t b)
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
        bs_char = toggle_bit(c, rand()%8);
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
size_t random_loc(const char *str)
{
    if (str == NULL) return 0;

    size_t len = strlen(str);
    if (len == 0)
        return 0;

    return (size_t)( (unsigned)rand() % (unsigned)len );
}

/**
 * Split url
 *
 * Split a string containing an url into two parts: The part before the dot is
 * the name and the part after the dot is the suffix. If a url contains more
 * than one dot an error will be generated. name and suffix has to be allocated
 * beforehand. The function will return 0 on success. -1 if failure.
 *
 * @param name_buf Return value, the part in front of the dot.
 * @param name_buf_sz Size of return buffer.
 * @param suffix_out Return value, the part after the dot.
 * @param url The string with url that should be considered.
 * @return The function will return 0 on success.
 */

int split_url(char *name_buf, size_t name_buf_sz, char **suffix_out, const char *url)
{
    const char *dot;
    const char *second_dot;
    size_t name_len;

    if (name_buf == NULL || name_buf_sz == 0 || suffix_out == NULL || url == NULL)
        return -1;

    dot = strchr(url, '.');
    if (dot == NULL) /* no dot */
        return -1;

    /* ensure there's no second dot in the suffix */
    second_dot = strchr(dot + 1, '.');
    if (second_dot != NULL)
        return -1;

    name_len = (size_t)(dot - url);
    if (name_len + 1 > name_buf_sz) /* +1 for NUL */
        return -1;

    if (name_len > 0)
        memcpy(name_buf, url, name_len);
    name_buf[name_len] = '\0';

    *suffix_out = (char *)(dot + 1); /* points inside url; caller must ensure url remains valid */
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
    char *tmp_buf = NULL;

    m_url.name = NULL;
    m_url.suffix = NULL;

    if (buf == NULL)
        return m_url;

    tmp_buf = malloc(256);
    if (tmp_buf == NULL)
        return m_url;

    if (split_url(tmp_buf, 256, &m_url.suffix, buf) != 0) {
        free(tmp_buf);
        return m_url;
    }

    m_url.name = strdup(tmp_buf);
    free(tmp_buf);

    if (m_url.name == NULL) {
        m_url.suffix = NULL;
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
 * Take a struct BSentries and bitsquat them.
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

// vim:sw=4:ts=4:sts=4:expandtab:
