#include "file.h"

#include <stdlib.h>
#include <string.h>

FILE *fileOpen(const char *fileName, const char *mode) {
    FILE *fp = fopen(fileName, mode);
    if (fp == NULL) {
        perror(fileName);
        exit(EXIT_FAILURE);
    }

    return fp;
}

char *outputFileName(char *fileName, const char *extention) {
    char *p = strrchr(fileName, '/');
    if (p != NULL) {
        fileName = p + 1;
    }
    fileName = strdup(fileName);

    p = strrchr(fileName, '.');
    if (p != NULL) {
        *p = '\0';
    }
    strcat(fileName, ".");
    strcat(fileName, extention);

    return fileName;
}
