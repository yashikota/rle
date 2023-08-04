#include <stdio.h>
#include <stdlib.h>

#include "usage.h"

void usage(char *argv[]) {
    fprintf(stderr, "Usage: %s [OPTION] FILE\n", argv[0]);
    fprintf(stderr, "Option:\n");
    fprintf(stderr, "  -o <FILE>  output file\n");
    exit(EXIT_FAILURE);
}
