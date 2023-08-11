#ifndef FILE_H
#define FILE_H

#include<stdio.h>

FILE *fileOpen(const char *fileName, const char *mode);
char *outputFileName(char *fileName, const char *extention);

#endif
