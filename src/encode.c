#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char *argv[]) {
    fprintf(stderr, "Usage: %s [OPTION] FILE\n", argv[0]);
    fprintf(stderr, "Option:\n");
    fprintf(stderr, "  -o <FILE>  output file\n");
    exit(EXIT_FAILURE);
}

unsigned char decimalToHex(int decimal, int padding) {
    return (unsigned char)(decimal + padding);
}

int main(int argc, char *argv[]) {
    FILE *rfp, *wfp;
    int opt;
    char *outputFileName = NULL;

    while ((opt = getopt(argc, argv, "o:")) != -1) {
        switch (opt) {
            case 'o':
                outputFileName = optarg;
                break;
            default:
                usage(argv);
        }
    }

    if (argc - optind != 1) {
        usage(argv);
    }

    if (outputFileName == NULL) {
        char *p = strrchr(argv[optind], '/');
        if (p == NULL) {
            outputFileName = argv[optind];
        } else {
            outputFileName = p + 1;
        }
        outputFileName = strdup(outputFileName);

        p = strrchr(outputFileName, '.');
        if (p != NULL) {
            *p = '\0';
        }
        strcat(outputFileName, ".rle");
    }

    rfp = fopen(argv[optind], "r");
    if (rfp == NULL) {
        perror("Read file open error");
        return EXIT_FAILURE;
    }

    wfp = fopen(outputFileName, "w");
    if (wfp == NULL) {
        perror("Write file open error");
        return EXIT_FAILURE;
    }

    // skip P
    fgetc(rfp);

    // file descriptor
    int type, width, height, brightness;
    fscanf(rfp, "%d %d %d %d", &type, &width, &height, &brightness);
    fprintf(wfp, "%c", decimalToHex(type, 0x00));
    fprintf(wfp, "%c", decimalToHex(brightness, 0x00));

    printf("%d, %d, %d, %d\n", type, width, height, brightness);

    int preChar, curChar;
    int count = 1;

    fscanf(rfp, "%d", &preChar);

    while (fscanf(rfp, "%d", &curChar) != EOF) {
        if (preChar == curChar) {
            count++;
        } else {
            printf("%d, %d\n", count, preChar);
            count = 1;
        }
        preChar = curChar;
    }
    printf("%d, %d\n", count, preChar);

    fclose(rfp);
    fclose(wfp);
    return 0;
}
