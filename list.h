#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include<stdlib.h>

typedef struct node{
    char data;
    struct node *next;
}node;

typedef node* list;

void append(list *l, char d);
char get_next(list *l);
int isEmpty(list l);
void traverse(list l);

#endif
