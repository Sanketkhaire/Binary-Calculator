#ifndef STACK_CH
#define STACK_CH

#include <stdio.h>
#include <stdlib.h>
#include "Num.h"

typedef struct Numbers{
        number num;
        struct Numbers* next;
}Numbers;

typedef struct char_node{
        char num;
        struct char_node* next;
} char_node;


typedef Numbers* numStack;

typedef char_node* char_stack;



void initNumStack(numStack *s);
void initCharStack(char_stack *s);

void pushNum(numStack *head, number num);
void pushChar(char_stack *head, char num);

number popNum(numStack *head);
char popChar(char_stack *head);


number peekNum(numStack st);
char peekChar(char_stack st);

int isEmptyNum(numStack st);
int isEmptyChar(char_stack st);

#endif
