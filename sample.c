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
