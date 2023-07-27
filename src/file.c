#include "file.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

long getFileSize(const char *fileName) {
    FILE *fp;
    long fileSize;
    struct stat stbuf;
    int fd;

    fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "cant open file : %s\n", fileName);
    }

    fp = fdopen(fd, "rb");
    if (fp == NULL) {
        fprintf(stderr, "cant open file : %s\n", fileName);
    }

    if (fstat(fd, &stbuf) == -1) {
        fprintf(stderr, "cant get file state : %s\n", fileName);
    }

    fileSize = stbuf.st_size;

    if (fclose(fp) != 0) {
        fprintf(stderr, "cant close file : %s\n", fileName);
    }

    return fileSize;
}

FILE *openReadTextFile(const char *fileName) {
    FILE *fp;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "cant open file : %s\n", fileName);
        return NULL;
    }

    return fp;
}

FILE *openReadBinaryFile(const char *fileName) {
    FILE *fp;

    fp = fopen(fileName, "rb");
    if (fp == NULL) {
        fprintf(stderr, "cant open file : %s\n", fileName);
        return NULL;
    }

    return fp;
}

FILE *openWriteTextFile(const char *fileName) {
    FILE *fp;

    fp = fopen(fileName, "w");
    if (fp == NULL) {
        fprintf(stderr, "cant open file : %s\n", fileName);
        return NULL;
    }

    return fp;
}

FILE *openWriteBinaryFile(const char *fileName) {
    FILE *fp;

    fp = fopen(fileName, "wb");
    if (fp == NULL) {
        fprintf(stderr, "cant open file : %s\n", fileName);
        return NULL;
    }

    return fp;
}
