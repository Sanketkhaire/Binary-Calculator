#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "num.h"
#include "stack.h"
#include "list.h"

typedef struct manageTokens {
        char unarySign;
        char lastState;
        char token;
        char next_token;
} manageTokens;


void initIdent(manageTokens *info);

int precedence(char c);

void error();

int isOperator(char c);

number eval(number *op1, number *op2, char operan, int isFunc);

int get_token(manageTokens *info, list *inp);

void checkErrors(manageTokens *info, list *inp, numStack *val);

void convert(number *n, char c);

#endif

