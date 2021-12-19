#include <stdio.h>
#include <stdlib.h>
#include "mainFunc.h"


int main() {
    printf("   *#* MY BINARY CALCULATOR *#*   \n");
    printf("Enter Quit to exit the calculator");
    printf("\nOperations : 1.ADDITION(+)  2.SUBTRACTION(-)  3.MULTIPLICATION(*)  4.DIVISION(/)  5.MODULUS(%)  6.POWER(^)  7.FACTORIAL(!)  8.DEC-TO-HEX(Ox)  9.DEC-TO-OCT(Oo)  10.DEC-TO-BIN(Ob)  11.length(expr)  12.gcd(a,b)  13.Lcm(a,b)\N");

    while(1) {
        printf("\nEnter : ");
        list entries;
        manageTokens info;
        init(&entries);
        initIdent(&info);


        char ch;
        while ((ch = getchar()) != '\n') {
            append(&entries, ch);
        }
        if(touch(entries) == 'Q') {
            printf("Quit");
            exit(0);
        }

        append(&entries, '\0');

        numStack val;
        char_stack s;

        initNumStack(&val);
        initCharStack(&s);

        number result, temp, op1, op2, fact;
        initNum(&temp);
        initNum(&result);
        init(&fact);

        char operan, c;
        int i = 0, j = 0, unarySign = 0, isConversion = 0, isFunc = 0, length = 0;

        get_token(&info, &entries);

        checkErrors(&info, &entries, &val);


        while(info.token != '\0'){
            c = info.token;

            if(isdigit(c)){
                insertDigit(&temp, c - '0');

                if(!isdigit(touch(entries))) {
                    if(info.unarySign) {
                        negation(&temp);
                        info.unarySign = 0;
                    }
                    pushNum(&val, temp);
                    initNum(&temp);

                }
            }

            else if(c == 'l') {
                while(get_next(&entries) != 'h');
                length = 1;
            }
            else if(c == 'g') {
                while(get_next(&entries) != 'd');
                isFunc = 1;
            }
            else if(c == 'L') {
                while(get_next(&entries) != 'm');
                isFunc = 2;
            }
            else if(c == '(') {
                pushChar(&s,'(');

                if (!isOperator(info.token = info.lastState)) {
                    printf("Syntax errors.\n");
                    exit(1);
                }

            }

            else if(c == ')') {
                while(!isEmptyChar(s) && peekChar(s)!= '(') {
                    op2 = popNum(&val);
                    op1 = popNum(&val);
                    operan = popChar(&s);
                    pushNum(&val, eval(&op1, &op2, operan, isFunc));
                }

                if(peekChar(s) == '(')
                    popChar(&s);
            }

            else if(c == 'O') {
                get_token(&info,&entries);
                pushChar(&s,info.token);
                isConversion = 1;
            }

            else if(c == '!') {
                fact = popNum(&val);
                pushNum(&val,factorial(&fact));
            }

            else {
                if (isOperator(c)) {
                    if(isEmptyChar(s))
                        pushChar(&s, c);
                    else {
                        while(!isEmptyChar(s) && precedence(peekChar(s)) >= precedence(c)) {
                            op2 = popNum(&val);
                            op1 = popNum(&val);
                            operan = popChar(&s);
                            pushNum(&val, eval(&op1, &op2, operan, isFunc));
                        }
                        pushChar(&s, c);

                    }
                }

                else
                    error();
            }

            get_token(&info, &entries);

            checkErrors(&info, &entries, &val);
        }

        if(isConversion) {
            number dec = popNum(&val);
            convert(&dec,popChar(&s));
        }

        while(!isEmptyChar(s)){
            op2 = popNum(&val);
            op1 = popNum(&val);
            operan = popChar(&s);
            pushNum(&val, eval(&op1, &op2, operan,isFunc));
        }
        if(!isConversion) {
        result = popNum(&val);
        printf("\n= ");
        if(length)
            printf("%d", result.digits);
        else
            printNum(result);
        }
        printf("\n");

    }
        return 0;
}


