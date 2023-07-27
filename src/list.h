#ifndef LIST_H
#define LIST_H

typedef struct {
    int size;
    int length;
    int *data;
} List;

List *createList(int size);
void pushList(List *list, int value);
int getListLength(List *list);
void cleanList(List *list);
int *getAllListValue(List *list);

#endif
