#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE sizeof(unsigned char)
#define WORD 1

void usage(char *argv[]) {
    fprintf(stderr, "Usage: %s [OPTION] FILE\n", argv[0]);
    fprintf(stderr, "Option:\n");
    fprintf(stderr, "  -o <FILE>  output file\n");
    exit(EXIT_FAILURE);
}

void changeOutputFileName(char *outputFileName, int type) {
    char *p = strrchr(outputFileName, '.');
    if (p != NULL) {
        *p = '\0';
    }
    if (type == 2) {
        strcat(outputFileName, ".pgm");
    } else if (type == 3) {
        strcat(outputFileName, ".ppm");
    }
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
    }

    rfp = fopen(argv[optind], "rb");
    if (rfp == NULL) {
        perror("Read file open error");
        return EXIT_FAILURE;
    }

    unsigned char type;
    fread(&type, BYTE, WORD, rfp);
    type = (int) type;

    switch(type) {
        case 2:
            changeOutputFileName(outputFileName, type);
            break;
        case 3:
            changeOutputFileName(outputFileName, type);
            break;
        default:
            fprintf(stderr, "Not supported file type\n");
            return EXIT_FAILURE;
    }

    wfp = fopen(outputFileName, "w");
    if (wfp == NULL) {
        perror("Write file open error");
        return EXIT_FAILURE;
    }

    unsigned char width, height, brightness;
    fread(&width, BYTE, WORD, rfp);
    fread(&height, BYTE, WORD, rfp);
    fread(&brightness, BYTE, WORD, rfp);
    width = (int) width;
    height = (int) height;
    brightness = (int) brightness;

    fprintf(wfp, "P%d\n", type);
    fprintf(wfp, "%d\n", brightness);

    fclose(wfp);
    fclose(rfp);
    return 0;
}
