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

#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int ntimes = 1; // Number of bitsquatted entries (default 1)

    struct Url url;
    struct BSentries bs_entries;

    // Seed the PRNG using current time (caller may override for deterministic tests)
    srand(time(NULL));

    if (argc < 2) {
        fprintf(stderr, "usage: %s sample.com [times]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 3) {
        ntimes = atoi(argv[2]);
        fprintf(stderr, "Repeating %d times.\n", ntimes);
    }

    if (ntimes < 0) {
        fprintf(stderr, "Unable to repeat %d times.\n", ntimes);
        return EXIT_FAILURE;
    }

    // Parse the input URL into name and suffix.
    // create_url returns a struct Url where:
    //  - url.name is heap-allocated and must be freed via free_url()
    //  - url.suffix points into the original input buffer (argv[1]) or is NULL on failure
    url = create_url(argv[1]);
    if (url.name == NULL || url.suffix == NULL) {
        fprintf(stderr, "Invalid URL: %s\n", argv[1]);
        /* create_url leaves fields NULL on failure; nothing to free */
        return EXIT_FAILURE;
    }

    // Generate ntimes entries (names duplicated / allocated inside generate_entries).
    // Caller owns bs_entries and must call free_bs_entries() when done.
    bs_entries = generate_entries(url, ntimes);

    // bitsquat_entries modifies bs_entries in-place, only 1 bit is flipped
    bitsquat_entries(bs_entries, 1);

    // Print results as name.suffix lines
    print_bs_entries(bs_entries);

    // Free all allocated resources in the correct order:
    // - free generated entries
    // - free URL name
    free_bs_entries(bs_entries);
    free_url(url);

    return EXIT_SUCCESS;
}
