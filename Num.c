
#include "Num.h"
#include "stack.h"

void initNum(number *n) {
    n->digits = n->sign = 0;
    n->first = n->last = NULL;
    return;
}

void negation(number *num) {
    num->sign = 1;
    return;
}

void insertDigit(number *n, int d) {
    digit *nn = (digit *)malloc(sizeof(digit));

    if(nn == NULL)
        return;
    nn->data = d;
    nn->next = nn->prev = NULL;
    if(n->first == NULL) {
        n->first = nn;
        n->last = nn;
        n->digits++;
        return;
    }

    n->last->next = nn;
    nn->prev = n->last;
    n->last = nn;
    n->digits++;

    return;
}


void insertAtBeg(number *n, int d) {
    digit *nn = (digit *)malloc(sizeof(digit));

    if(nn == NULL)
        return;
    nn->data = d;
    nn->next = nn->prev = NULL;
    if(n->first == NULL) {
        n->first = nn;
        n->last = nn;
        n->digits++;
        return;
    }

    nn->next = n->first;
    n->first->prev = nn;
    n->first = nn;
    n->digits++;
    return;
}


void printNum(number n) {
    if(n.first != NULL){
        if(n.sign)
            printf("-");
        while(n.first != NULL) {
            printf("%d",n.first->data);
            n.first = n.first->next;
        }
    }
    else
        printf("%d",0);
    return;
}

void destroyNum(number *n){
    digit *q = NULL;
    n->sign = 0;
    if(n->digits == 0)
        return;
    while(n->first->next != NULL) {
        q = n->first;
        n->first = n->first->next;
        n->digits--;
        free(q);
        n->first->prev = NULL;
    }

    n->first = NULL;
   // free(n->last);
    n->last = NULL;
    n->digits--;
    return;
}


number add(number *a, number *b) {
    remLeadZeroes(a);
    remLeadZeroes(b);
    number res, n = *a, m = *b;
    initNum(&res);
    if(n.sign == 1 && m.sign ==1) {
        a->sign = 0;
        b->sign = 0;
        res.sign = 1;
    }
    else if(n.sign == 1) {
        a->sign = 0;
        return sub(b,a);
    }
    else if(m.sign == 1) {
        b->sign = 0;
        return sub(a,b);
    }


    digit *p = n.last;
    digit *q = m.last;
    int carry = 0, sum;
    while(p && q) {
        sum = p->data + q->data + carry;
        carry = sum / 10;
        insertAtBeg(&res,sum % 10);
        p = p->prev;
        q = q->prev;
    }
    while(p != NULL) {
        sum = p->data + carry;
        carry = sum / 10;
        insertAtBeg(&res,sum % 10);
        p = p->prev;
    }
     while(q != NULL) {
        sum = q->data +carry;
        carry = sum / 10;
        insertAtBeg(&res,sum % 10);
        q = q->prev;
    }
    if(carry)
        insertAtBeg(&res, carry);

    return res;
}



number sub(number *a, number *b) {
    remLeadZeroes(a);
    remLeadZeroes(b);
    number res, n = *a, m = *b;
    initNum(&res);

    if(n.sign == 1 && m.sign ==1) {
        n = *b;
        m = *a;
	n.sign = 0;
	m.sign = 0;
    }
    else if(n.sign == 1) {
        a->sign = 0;
        res = add(a,b);
        res.sign = 1;
        return res;
    }
    else if(m.sign == 1) {
        b->sign = 0;
        return add(a,b);
    }
    if(n.digits == 0){
        m.sign = 1;
        return m;
    }
    else if(m.digits == 0)
        return n;

    if(isSmaller(n,m)==2)
        return res;
    number p , q;

    int  diff, isBorrow = 0, dig1, dig2, i =0 ;
    if(isSmaller(n, m)==1) {
        p = m;
        q = n;
        res.sign = 1;
    }
    else{
        p = n;
        q = m;
    }


    while(i < q.digits){
        dig1 = p.last->data;
        dig2 = q.last->data;
        if(isBorrow) {
            dig1--;
            isBorrow = 0;
        }

        if(dig1 >= dig2) {
            diff = dig1 - dig2;
            insertAtBeg(&res, diff);
            p.last = p.last->prev;
            q.last = q.last->prev;
        }
        else {
            diff = (dig1 + 10) - dig2;
            insertAtBeg(&res, diff);
            isBorrow = 1;
            p.last = p.last->prev;
            q.last = q.last->prev;
        }

        i++;
    }

    while(i < p.digits) {
        if(isBorrow) {
            if(!p.last->data)
                insertAtBeg(&res, 9);
            else {
                insertAtBeg(&res, p.last->data - 1);
                isBorrow = 0;
            }
        }
        else
            insertAtBeg(&res, p.last->data);
        p.last = p.last->prev;
        i++;
    }
    remLeadZeroes(&res);
    return res;
}


number multiply(number *a, number *b) {
    remLeadZeroes(a);
    remLeadZeroes(b);
    number n = *a, m = *b;
    number num1, num2;
    initNum(&num1);
    initNum(&num2);
    if(n.digits == 0 || m.digits == 0) {
        insertDigit(&num2, 0);
        return num2;
    }

    int temp1, temp2, i = 0, j, carry = 0, lim = 0;
    digit *p, *q, *r;


    if(n.digits > m.digits) {
        p = m.last;
        r = n.last;
        while(lim != n.digits + 1) {
            insertAtBeg(&num2 ,0);
            lim++;
        }
    }
    else {
        p = n.last;
        r = m.last;
        while(lim != m.digits + 1) {
            insertAtBeg(&num2 ,0);
            lim++;
        }
    }

    while(p) {
        temp1 = p->data;
        q = r;
        carry = 0;

        while(q) {
            temp2 = temp1*(q->data) + carry;
            carry = temp2/10;
            temp2 = temp2 % 10;
            insertAtBeg(&num1, temp2);
            q = q->prev;
        }


        if(carry)
            insertAtBeg(&num1, carry);

        j = 0;
        while(j++ != i)
           insertDigit(&num1,0);


        num2 = add(&num1 , &num2);
        remLeadZeroes(&num2);
        p = p->prev;
        destroyNum(&num1);
        i+=1;
    }
    remLeadZeroes(&num2);
    return num2;
}

number divide(number *n, number *m, int choice) {

    remLeadZeroes(n);
    remLeadZeroes(m);
    number a = *n, b = *m;
    number quo, mp, temp, rem, ab;
    initNum(&quo);
    initNum(&mp);
    initNum(&temp);
    initNum(&rem);
    initNum(&ab);


    if(b.digits == 0) {
        printf("Syntax Error : Division by zero is indefinite");
        exit(1);
    }
    if(a.digits < b.digits) {
        if(!choice) {
            insertDigit(&quo, 0);
            return quo;
        }
        else
            return a;
    }
    if(a.digits == 0) {
        insertDigit(&quo,0);
        return quo;
    }

    int i;
    digit *aa = a.first;
    digit *bb = b.first;
    digit *d, *e;


    for (i = 0; i < b.digits; i++) {
        insertDigit(&rem, aa->data);
        aa = aa->next;
    }

    for (i = 1; i < 10; i++) {
        insertDigit(&mp, i);
        temp = multiply(&b, &mp);
        if(isSmaller(rem, temp)==1)
            break;
        destroyNum(&mp);
        destroyNum(&temp);
    }

    destroyNum(&mp);
    destroyNum(&temp);


    insertDigit(&mp, i - 1);

    temp = multiply(&b, &mp);

    rem = sub(&rem, &temp);

    insertDigit(&quo, i-1);

    remLeadZeroes(&quo);


    destroyNum(&mp);
    destroyNum(&temp);

    while (aa != NULL) {
        insertDigit(&rem, aa->data);
        remLeadZeroes(&rem);
        if(rem.digits == 0) {
            insertDigit(&quo, 0);
            aa = aa->next;
            continue;
        }
        for (i = 1; i < 10; i++) {
            insertDigit(&mp, i);
            temp = multiply(&b, &mp);
            if (isSmaller(rem, temp)==1)
                break;
            destroyNum(&mp);
            destroyNum(&temp);

        }

        initNum(&mp);
        initNum(&temp);

        insertDigit(&mp, i - 1);
        temp = multiply(&b, &mp);
        rem = sub(&rem, &temp);


        insertDigit(&quo, i-1);
        remLeadZeroes(&quo);

        destroyNum(&mp);
        destroyNum(&temp);
        initNum(&mp);
        initNum(&temp);

        aa = aa->next;
    }

    if(choice)
        return rem;
    else
        return quo;
}


int isSmaller(number n, number m) {
    if(n.digits>m.digits)
        return 0;
    else if(n.digits < m.digits)
        return 1;
    else {
        while(n.first) {
        if(n.first->data < m.first->data)
            return 1;
        else if (n.first->data > m.first->data)
            return 0;
        n.first = n.first->next;
        m.first = m.first->next;
        }
        return 2;
    }
}

void remLeadZeroes(number *n) {
    digit *p = NULL;
    if(n->digits == 0)
        return;
    while(n->first->data == 0 && n->first != NULL){

        p = n->first;

        n->first = n->first->next;
        n->digits--;
        free(p);
        if(n->first == NULL)
            break;
        n->first->prev = NULL;
    }

    if(n->digits == 0)
        initNum(n);
    return;
}


number power(number *a, number *b) {
    remLeadZeroes(a);
    remLeadZeroes(b);
    int limit;
    number n = *a, m = *b, counter, one, res;
    initNum(&counter);
    initNum(&one);
    initNum(&res);
    insertDigit(&one, 1);

    if(n.digits == 0 && m.digits == 0) {
        res.sign = 2;
        return res;
    }
    if(n.digits == 0) {
        insertDigit(&res,0);
        return res;
    }
    else if(m.digits == 0)
        return one;
    else if(n.digits == 1 && n.first->data == 1)
        return one;

    insertDigit(&counter,1);
    res = multiply(&n,&one);

    limit = isSmaller(counter, m);
    while(limit != 2){
        res = multiply(&res,&n);
        counter = add(&counter,&one);
        limit = isSmaller(counter, m);
    }
    return res;
}


number factorial(number *n) {
    remLeadZeroes(n);
    number a = *n, one, res, b, c;
    initNum(&res);
    initNum(&one);
    initNum(&b);
    initNum(&c);
    insertDigit(&one, 1);
    if(a.digits == 0)
        return one;
    if(a.digits == 1 && a.first->data == 1)
        return one;
    else {
        c = sub(&a,&one);
        b = factorial(&c);
        return multiply(&a,&b);
    }
}

void decToHex(number *n) {
    remLeadZeroes(n);
    char_stack hex;
    number quo = *n, rem, num;
    initCharStack(&hex);
    initNum(&num);
    initNum(&rem);
    insertDigit(&num, 1);
    insertDigit(&num, 6);
    digit *temp = NULL;
    char ch;

    while(quo.digits != 0) {
        rem = divide(&quo, &num, 1);
        quo = divide(&quo, &num, 0);
        remLeadZeroes(&quo);
        temp = rem.first;

        if(rem.digits == 0)
            pushChar(&hex, 48);
        else if(rem.digits == 1) {
            ch = temp->data + 48;
            pushChar(&hex,ch);
        }
        else {
            ch = temp->next->data + 55 +10;
            pushChar(&hex,ch);
        }
        if(quo.digits == 0)
            break;
    }
    while(!isEmptyChar(hex)) {
        printf("%c",popChar(&hex));
    }
    return;

}

void decToOct(number *n) {
    remLeadZeroes(n);
    char_stack oct;
    number quo = *n, rem, num;
    initCharStack(&oct);
    initNum(&num);
    initNum(&rem);
    insertDigit(&num, 8);
    char ch;

    while(quo.digits!=0) {
        rem = divide(&quo,&num,1);
        quo = divide(&quo,&num,0);
        remLeadZeroes(&quo);
        if(rem.digits == 0)
            pushChar(&oct,48);
        else {
            ch = rem.first->data + 48;
            pushChar(&oct,ch);
        }
        if(quo.digits == 0)
            break;
        }

    while(!isEmptyChar(oct)) {
        printf("%c",popChar(&oct));
    }
    return;

}

void decToBin(number *n) {
    remLeadZeroes(n);
    char_stack bin;
    number quo = *n, rem, num;
    initCharStack(&bin);
    initNum(&num);
    initNum(&rem);
    insertDigit(&num, 2);

    while(quo.digits!=0) {
        rem = divide(&quo,&num,1);
        quo = divide(&quo,&num,0);
        remLeadZeroes(&quo);
        if(rem.digits == 0)
            pushChar(&bin,48);
        else
            pushChar(&bin,49);
        if(quo.digits == 0)
            break;
        }

    printf("\n=");
    while(!isEmptyChar(bin)) {
        printf("%c",popChar(&bin));
    }
    return;
}

number gcd(number *n, number *m) {
    remLeadZeroes(n);
    remLeadZeroes(m);
    number a = *n,b=*m;
    if(a.digits == 0)
        return b;
    if(b.digits == 0)
        return a;
    if(isSmaller(a,b) == 2)
        return a;
    number res ;
    init(&res);
    if(isSmaller(a,b)) {
        res = divide(&b,&a,1);
        remLeadZeroes(&res);
        return gcd(&a,&res);
    }
    else {
        res = divide(&a,&b,1);
        remLeadZeroes(&res);
        return gcd(&b,&res);
    }
}

number lcm(number *n,number *m) {
    number a = *n, b = *m, gc, temp;
    initNum(&gc);
    initNum(&temp);
    gc = gcd(&a,&b);
    temp = multiply(&a,&b);
    temp = divide(&temp, &gc,0);
    return temp;
}

