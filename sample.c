#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define INITPROF struct timeval before, after;
#define STARTPROF gettimeofday(&before, NULL);
#define STOPPROF gettimeofday(&after, NULL);
#define REPORTPROF(a) printf("%06ld usec - %s\n", after.tv_usec - before.tv_usec, (a));

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

    INITPROF;

    STARTPROF;
    url = create_url(argv[1]);
    STOPPROF;
    REPORTPROF("create_url");

    STARTPROF;
    bs_entries = generate_entries(url, ntimes);
    STOPPROF;
    REPORTPROF("generate_entries");

    STARTPROF;
    bitsquat_entries(bs_entries);
    STOPPROF;
    REPORTPROF("bitsquat_entries");

    /* print_bs_entries(bs_entries); */

    return 0;
}
