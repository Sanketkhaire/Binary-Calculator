
#include "stack.h"

void initNumStack(numStack *s) {
	(*s) = NULL;
}

void initCharStack(char_stack *s) {
    (*s) = NULL;
}

void pushNum(numStack *head, number num) {
        numStack nn;
        nn = (Numbers*)malloc(sizeof(Numbers));
        if(nn) {
                nn->num = num;
                nn->next = NULL;
        }
        else return;

        if(*head == NULL) {
                *head = nn;
                return;
        }
        nn->next = *head;
        *head = nn;
        return;
}

void pushChar(char_stack *head, char num) {
        char_stack nn;
        nn = (char_node*)malloc(sizeof(char_node));
        if(nn) {
                nn->num = num;
                nn->next = NULL;
        }
        else return;

        if(*head == NULL) {
                *head = nn;
                return;
        }
        nn->next = *head;
        *head = nn;
        return;
}


number popNum(numStack *head) {
        number empty, num;
        numStack temp;
        /*To indicate stack is empty*/
        empty.sign = -1;
        if (*head == NULL)
                return empty;
        temp = *head;
        num = (*head)->num;
        *head = (*head)->next;
        free(temp);
        return num;
}

char popChar(char_stack *head) {
	char empty, num;
	char_stack temp;
	/*To indicate stack is empty*/
	empty = 255;
	if (*head == NULL)
		return empty;
	temp = *head;
	num = (*head)->num;
	*head = (*head)->next;
	free(temp);
	return num;
}



number peekNum(numStack st) {
	if(st)
		return st->num;
	else{
		number tmp;
		tmp.sign = -1;
		return tmp;
	}
}

char peekChar(char_stack st) {
        if(st)
                return st->num;
	else return -128;
}


int isEmptyNum(numStack st) {
    if(peekNum(st).sign == -1)
        return 1;
	else return 0;
}

int isEmptyChar(char_stack st) {
	if(peekChar(st) == -128){
		return 1;
    }
	else return 0;
}
