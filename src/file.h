#ifndef FILE_H
#define FILE_H

#include<stdio.h>

long getFileSize(const char *fileName);
FILE *openReadTextFile(const char *fileName);
FILE *openReadBinaryFile(const char *fileName);
FILE *openWriteTextFile(const char *fileName);
FILE *openWriteBinaryFile(const char *fileName);

#endif
