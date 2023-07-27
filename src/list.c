#include "list.h"

#include <stdio.h>
#include <stdlib.h>

void memoryError() {
    fprintf(stderr, "Error: memory allocation failed.\n");
    exit(EXIT_FAILURE);
}

List *createList(int size) {
    List *list = (List *)calloc(1, sizeof(List));
    if (list == NULL) memoryError();
    list->size = size;
    list->length = 0;
    list->data = (int *)calloc(size, sizeof(int));
    if (list->data == NULL) memoryError();
    return list;
}

void resizeList(List *list, int size) {
    int *temp;
    if (size < list->length) {
        list->length = size;
    }
    temp = (int *)realloc(list->data, size * sizeof(int));
    if (temp == NULL) memoryError();
    list->data = temp;
    list->size = size;
}

void pushList(List *list, int value) {
    if (list->length == list->size) {
        resizeList(list, list->size * 2);
    }
    list->data[list->length++] = value;
}

int getListLength(List *list) {
    return list->length;
    }

void cleanList(List *list) {
    free(list->data);
    free(list);
}

int *getAllListValue(List *list) {
    int *data = (int *)calloc(list->length, sizeof(int));
    if (data == NULL) memoryError();
    for (int i = 0; i < list->length; i++) {
        data[i] = list->data[i];
    }
    return data;
}
