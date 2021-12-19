
#include "list.h"

void init(list *l){
   *l = NULL;
    return;
}

void append(list *l, char d){
    node *p, *newnode;
    newnode = (node*)malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
        newnode->next = NULL;
    }
    else return;

    if(*l == NULL){
        *l = newnode;
        return;
    }
    p = *l;
    while(p -> next) {
        p = p->next;
        }
        p->next = newnode;
        return;
}


char get_next(list *l) {
    if(*l == NULL)
        return INT_MAX;
    char c ;
    node *p = *l;
    c = p->data;
    *l = p->next;
    free(p);
    return c;
}

int isEmpty(list l) {
    if(l == NULL)
        return 1;
    else
        return 0;
}


char touch(list l) {
    if(l)
        return l->data;
    else
        return INT_MAX;
}

void traverse(list l){
    printf("[");
    node *p;
    p = l;
    while(p){
      //  if(p->data == '\0')
            printf("Hi%c ", p->data);
        p = p->next;
    }
    printf("]\n");
    return;
}
