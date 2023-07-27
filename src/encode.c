#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "list.h"

#define ONE_BYTE 256
#define LITERAL 0
#define FILL 1

void usage(char *argv[]) {
    fprintf(stderr, "Usage: %s [OPTION] FILE\n", argv[0]);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -o <FILE>  output file\n");
    exit(EXIT_FAILURE);
}

unsigned char OneByteDecimalToHex(int decimal) {
    return (unsigned char)decimal;
}

unsigned char TwoByteDecimalToHex(int decimal) {
    return (unsigned char)(decimal / ONE_BYTE);
}

void DecimalToHex(FILE *fp, int decimal) {
    if (decimal < ONE_BYTE) {
        fprintf(fp, "%c", OneByteDecimalToHex(decimal));
    } else {
        fprintf(fp, "%c", 0x00);
        fprintf(fp, "%c", TwoByteDecimalToHex(decimal));
        fprintf(fp, "%c", OneByteDecimalToHex(decimal % ONE_BYTE));
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

        p = strrchr(outputFileName, '.');
        if (p != NULL) {
            *p = '\0';
        }
        strcat(outputFileName, ".rle");
    }

    rfp = openReadTextFile(argv[optind]);
    wfp = openWriteBinaryFile(outputFileName);

    // skip P
    fgetc(rfp);

    // properties
    int type, width, height, brightness;
    fscanf(rfp, "%d %d %d %d", &type, &width, &height, &brightness);

    DecimalToHex(wfp, type);
    DecimalToHex(wfp, width);
    DecimalToHex(wfp, height);
    DecimalToHex(wfp, brightness);

    // data
    int mode = LITERAL;
    int preChar, curChar;
    int count = 1;
    int *data;
    List *list = createList(1);

    fscanf(rfp, "%d", &preChar);
    while (fscanf(rfp, "%d", &curChar) != EOF) {
        if (preChar == curChar) {
            if (mode == LITERAL) {
                pushList(list, preChar);
                DecimalToHex(wfp, getListLength(list));
                data = getAllListValue(list);
                for (int i = 0; i < list->length; i++) {
                    DecimalToHex(wfp, data[i]);
                }
                cleanList(list);
                list = createList(1);
                count = 1;
                mode = FILL;
            } else if (mode == FILL) {
                count++;
            }
        } else {
            if (mode == LITERAL) {
                pushList(list, preChar);
            } else if (mode == FILL) {
                DecimalToHex(wfp, count);
                mode = LITERAL;
                count = 1;
            }
        }
        preChar = curChar;
    }
    if (mode == LITERAL) {
        pushList(list, preChar);
        DecimalToHex(wfp, count);
        data = getAllListValue(list);
        for (int i = 0; i < list->length; i++) {
            DecimalToHex(wfp, data[i]);
        }
    } else if (mode == FILL) {
        DecimalToHex(wfp, count);
    }

    cleanList(list);
    fclose(rfp);
    fclose(wfp);

    return 0;
}
