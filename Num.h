#ifndef NUMBER_H
#define NUMBER_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct digit {
    int data;
    struct digit *next;
    struct digit *prev;
}digit;

typedef struct number {
    int digits;
    int sign;
    digit *first;
    digit *last;
}number;

void initNum(number *n);
void insertDigit(number *n, int d);
void insertAtBeg(number *n, int d);
void destroyNum(number *n);
void printNum(number n);
void negation(number *num);
int isSmaller(number n, number m);
void remLeadZeroes(number *n);
number add(number *a, number *b);
number sub(number *b, number *a);
number multiply(number *a, number *b);
number divide(number *n, number *m, int choice);
number power(number *a, number *b);
number factorial(number *n);
void decToHex(number *n);
void decToOct(number *n);
void decToBin(number *n);
number gcd(number *n, number *m);
number lcm(number *n,number *m);

#endif
