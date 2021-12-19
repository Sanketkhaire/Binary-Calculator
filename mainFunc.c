#include "mainFunc.h"

void initIdent(manageTokens *info) {
        info->unarySign = 0;
        info->lastState = 0;
        info->token = '+';
        info->next_token = 0;
        return;
}


int precedence(char c) {
    switch(c) {
        case '(':
                return 10;
        case '+':
                return 20;
        case '-':
                return 20;
        case '*':
                return 30;
        case '/':
                return 30;
        case '%':
                return 30;
        case '^':
                return 40;
        case ',':
                return 50;
        default:
                return 0;

    }
}



void error() {
        printf("Syntax Error.\n");
        exit(1);
}


int isOperator(char c) {
	switch(c) {
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
            return 1;
        case '/':
            return 1;
		case '%':
            return 1;
        case '^':
            return 1;
        case ',':
            return 1;
        case 'g':
            return 1;
        case 'l':
            return 1;
        case 'L':
            return 1;
		default:
			return 0;
	}
}

number eval(number *op1, number *op2, char operan, int isFunc) {
        switch(operan){
                case('+'):
                        return add(op1, op2);
                case('-'):
                        return sub(op1, op2);
                case('*'):
                        return multiply(op1, op2);
                case('/'):
                        return divide(op1, op2, 0);
                case('%'):
                        return divide(op1, op2, 1);
                case('^'):
                        return power(op1, op2);
                case(','):
                        if(isFunc == 1)
                            return gcd(op1,op2);
                        if(isFunc == 2)
                            return lcm(op1,op2);

        }
}


int get_token(manageTokens *info, list *inp) {
        info->lastState = info->token;
        for( ; touch(*inp) != '\0' && touch(*inp) == ' '; get_next(inp));
        info->token = get_next(inp);
        for( ; touch(*inp) != '\0' && touch(*inp) == ' '; get_next(inp));
        info->next_token = touch(*inp);
        return 0;
}


void checkErrors(manageTokens *info, list *inp, numStack *val) {
        switch(info->token) {
                case '/':
                        if(isOperator(info->lastState))
                                error();
                        break;
                case '*':
                        if(isOperator(info->lastState))
                                error();
                        break;
                case '^':
                        if(isOperator(info->lastState))
                                error();
                        break;
                case '-':
                        if(isOperator(info->lastState) && isdigit(info->next_token)) {
                                info->unarySign = 1;
                                info->token = info->next_token;
                                info->next_token = get_token(info, inp);
                        }
                        else if(isOperator(info->lastState) && isOperator(info->next_token))
                                error();
                        break;
                case '+':
                        if(isOperator(info->lastState) && isdigit(info->next_token)) {
                                info->token = info->next_token;
                                info->next_token = get_token(info, inp);

                        }
                        else if(isOperator(info->lastState) && isOperator(info->next_token))
                                error();
                        break;
                case '\0':
                        if(isOperator(info->lastState)) {
                                printf("Syntax Error OR Nothing is Entered.\n");
                                exit(1);
                        }
                        break;


        }
        return;
}

void convert(number *n, char c) {

    switch(c) {
        case 'x':
            decToHex(n);
            break;
        case 'o':
            decToOct(n);
            break;
        case 'b':
            decToBin(n);
            break;
    }
    return ;
}

