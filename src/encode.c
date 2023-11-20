#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "list.h"
#include "usage.h"
#include "option.h"

#define ONE_BYTE 256
#define LITERAL 0
#define FILL 1

unsigned char oneByteDecimalToHex(int decimal) {
    return (unsigned char)decimal;
}

unsigned char twoByteDecimalToHex(int decimal) {
    return (unsigned char)(decimal / ONE_BYTE);
}

void decimalToHex(FILE *fp, int decimal) {
    if (decimal < ONE_BYTE) {
        fprintf(fp, "%c", oneByteDecimalToHex(decimal));
    } else {
        fprintf(fp, "%c", 0x00);
        fprintf(fp, "%c", twoByteDecimalToHex(decimal));
        fprintf(fp, "%c", oneByteDecimalToHex(decimal % ONE_BYTE));
    }
}

int main(int argc, char *argv[]) {
    FILE *rfp, *wfp;

    char *outputFileName = parseOption(argc, argv);

    rfp = fileOpen(argv[getOptind()], "r");
    wfp = fileOpen(outputFileName, "wb");

    // skip P
    fgetc(rfp);

    // properties
    int type, width, height, brightness;
    fscanf(rfp, "%d %d %d %d", &type, &width, &height, &brightness);

    decimalToHex(wfp, type);
    decimalToHex(wfp, width);
    decimalToHex(wfp, height);
    decimalToHex(wfp, brightness);

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
                decimalToHex(wfp, getListLength(list));
                data = getAllListValue(list);
                for (int i = 0; i < list->length; i++) {
                    decimalToHex(wfp, data[i]);
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
                count++;
            } else if (mode == FILL) {
                decimalToHex(wfp, count);
                mode = LITERAL;
                count = 1;
            }
        }
        preChar = curChar;
    }
    if (mode == LITERAL) {
        pushList(list, preChar);
        decimalToHex(wfp, count);
        data = getAllListValue(list);
        for (int i = 0; i < list->length; i++) {
            decimalToHex(wfp, data[i]);
        }
    } else if (mode == FILL) {
        decimalToHex(wfp, count);
    }

    cleanList(list);
    fclose(rfp);
    fclose(wfp);

    return 0;
}
