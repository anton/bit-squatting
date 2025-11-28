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
    int ntimes = 1;
    struct Url url;
    struct BSentries bs_entries;

    srand(time(NULL));

    if (argc < 2) {
        fprintf(stderr, "usage: %s sample.com [times]\n", argv[0]);
        exit(-1);
    }

    if (argc == 3) {
        ntimes = atoi(argv[2]);
        fprintf(stderr, "Repeating %d times.\n", ntimes);
    }

    if (ntimes < 0) {
        fprintf(stderr, "Unable to repeat %d times.\n", ntimes);
        exit(-1);
    }

    url = create_url(argv[1]);
    bs_entries = generate_entries(url, ntimes);
    bitsquat_entries(bs_entries);
    print_bs_entries(bs_entries);

    return 0;
}
