//
//  main.c
//  asn3pt1
//
//  Created by Ben Tilden on 2018-10-30.
//  Copyright © 2018 Ben Tilden. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

float get_num(){
    float num;
    scanf("%f", &num);
    return num;
}

char get_op(){
    char l_op;
    scanf("%c", &l_op);
    while (l_op == ' '){
        scanf("%c", &l_op);
    }
    return l_op;
}

float m_exp(float sub_exp, char op){
    float nextNum = get_num();
    char nextOp = get_op();
    if(nextOp == '+' || nextOp == '-' || nextOp == '\n'){
        ungetc(nextOp, stdin);
        return nextNum;
    }
    sub_exp = nextNum;
    op = nextOp;
    nextNum = get_num();
    nextOp = get_op();
    if(op == '/'){
        nextNum = (sub_exp / nextNum);
        if(nextOp == '+' || nextOp == '-' || nextOp == '\n'){
            ungetc(nextOp, stdin);
            return nextNum;
        }
        return nextNum;
    }
    else if(op == '*'){
        nextNum = (sub_exp * nextNum);
        if(nextOp == '+' || nextOp == '-' || nextOp == '\n'){
            ungetc(nextOp, stdin);
            return nextNum;
        }
        return nextNum;
    }
    else{
        printf("No operators or an invalid operator has been entered. Please try again \n");
        main();
    }
    return m_exp(sub_exp, nextOp);
}

float s_exp(float sub_exp, char op){
    float nextNum;
    char nextOp;
    if(op == '\n'){
        return sub_exp;
    }
    nextNum = m_exp(sub_exp, op);
    nextOp = get_op();
    if(op == '+'){
        nextNum = (sub_exp + nextNum);
        return s_exp(nextNum, nextOp);
    }
    else if(op == '-'){
        nextNum = (sub_exp - nextNum);
        return s_exp(nextNum, nextOp);
    }
    else{
        printf("No operators or an invalid operator has been entered. Please try again. \n");
        main();
    }
    return s_exp(sub_exp, nextOp);
}

int main() {
    while(1){
        char nextOp = '+';
        char response;
        float result;
        float nextNum = 0;
        printf("Enter a simple arithmatic expression: \n");
        result = s_exp(nextNum, nextOp);
        printf("Answer: %.2f \n", result);
        printf("Would you like to continue? \n");
        scanf(" %c", &response);
        if(response == 'Y'){
            main();
        }
        else if(response == 'N'){
            exit(EXIT_FAILURE);
        }
        else{
            continue;
        }
    }
    return 0;
}

