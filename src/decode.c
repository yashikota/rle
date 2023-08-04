#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "usage.h"

#define LITERAL 0
#define FILL 1
#define BYTE sizeof(unsigned char)
#define WORD 1

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

int readByte(FILE *fp) {
    unsigned char byte;
    fread(&byte, BYTE, WORD, fp);
    if (feof(fp)) return EOF;
    if (byte == 0x00) {
        unsigned short int multiByte;
        unsigned char firstByte, secondByte;
        fread(&firstByte, BYTE, WORD, fp);
        fread(&secondByte, BYTE, WORD, fp);
        multiByte = (firstByte << 8) | secondByte;
        return (int)multiByte;
    }
    return (int)byte;
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

    rfp = openReadBinaryFile(argv[optind]);

    unsigned char type;
    fread(&type, BYTE, WORD, rfp);
    type = (int)type;

    switch (type) {
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

    wfp = openWriteTextFile(outputFileName);

    int width, height, brightness;
    width = readByte(rfp);
    height = readByte(rfp);
    brightness = readByte(rfp);
    fprintf(wfp, "P%d\n%d\n%d\n%d\n", type, width, height, brightness);

    // data
    int mode = LITERAL;
    int count;
    unsigned char ch;

    while (1) {
        count = readByte(rfp);
        if (count == EOF) break;
        if (mode == LITERAL) {
            for (int j = 0; j < count; j++) {
                fread(&ch, BYTE, WORD, rfp);
                fprintf(wfp, "%d\n", ch);
            }
            mode = FILL;
        } else if (mode == FILL) {
            for (int j = 0; j < count; j++) {
                fprintf(wfp, "%d\n", ch);
            }
            mode = LITERAL;
        }
    }

    fclose(wfp);
    fclose(rfp);

    return 0;
}
