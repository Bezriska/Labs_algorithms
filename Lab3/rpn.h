#ifndef RPN_H
#define RPN_H
#include <stdio.h>
#include <ctype.h>
#include "stack.h"
#include "validation.h"
#include "check_priority.h"

// typedef struct {
//     char oper;
//     int prior;
// } Oper;

// Oper* initiate_oper() {
//     Oper* op = (Oper*)malloc(sizeof(Oper));
//     op->oper = NULL;
//     op->prior = NULL;
//     return op;
// }


OBJ* rpn(char* str) {
    OBJ* out_top = NULL;
    OBJ* oper_top = stack_init();

    for (int i = 0; str[i] != '\0'; ++i) {
        if (isalnum(str[i])) {
            push(&out_top, str[i]);
            continue;
        }

        if (isoper(str[i])) {
            if (str[i] == '(') {
                push(&oper_top, str[i]);
                continue;
            }
            
            if (str[i] == ')') {
                while (top(oper_top) != '(') {
                    push(&out_top, pop(&oper_top));
                }
                pop(&oper_top);
                continue;
            }

            while (top(oper_top) != '@' && top(oper_top) != '(' && 
                   priority_check(top(oper_top)) >= priority_check(str[i])) {
                push(&out_top, pop(&oper_top));
            }
            push(&oper_top, str[i]);
        }
    }

    while (top(oper_top) != '@') {
        push(&out_top, pop(&oper_top));
    }

    return out_top;

}









#endif