#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bitsquat_once(char *url)
{
    char *ans = malloc(256*sizeof(char));

    if (bs1(url, strlen(url), &ans)) {
        exit(-1);
    }

    printf("%s\n", ans);

    free(ans);
}

int main(int argc, char *argv[])
{
    int ntimes = 1;

    srand(time(NULL));

    if (argc < 2) {
        fprintf(stderr, "usage: %s sample.com [times]\n", argv[0]);
        exit(-1);
    }

    if (argc == 3) {
        ntimes = atoi(argv[2]);
        fprintf(stderr, "Repeating %d times.\n", ntimes);
    }

    if (ntimes == 1) {
        bitsquat_once(argv[1]);
    } else if (ntimes > 1) {
        int i;
        for (i=0; i<ntimes; i++)
            bitsquat_once(argv[1]);
    } else {
        fprintf(stderr, "Unable to repeat %d times.\n", ntimes);
        exit(-1);
    }

    return 0;
}
