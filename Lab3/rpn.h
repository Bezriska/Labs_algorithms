#ifndef RPN_H
#define RPN_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
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


char* rpn(char* str) {
    OBJ* oper_top = stack_init();
    size_t n = strlen(str);
    char* out = (char*)malloc(4 * n + 1);
    int k = 0;

    if (out == NULL) {
        return NULL;
    }

    for (int i = 0; str[i] != '\0'; ++i) {
        if (isspace((unsigned char)str[i])) {
            continue;
        }

        if (isdigit((unsigned char)str[i])) {
            while (isdigit((unsigned char)str[i])) {
                out[k++] = str[i++];
            }
            out[k++] = ' ';
            --i;
            continue;
        }

        if (isoper(str[i])) {
            if (str[i] == '(') {
                push(&oper_top, str[i]);
                continue;
            }
            
            if (str[i] == ')') {
                while (top(oper_top) != '(') {
                    out[k++] = pop(&oper_top);
                    out[k++] = ' ';
                }
                pop(&oper_top);
                continue;
            }

            while (top(oper_top) != '@' && top(oper_top) != '(' && 
                   (priority_check(top(oper_top)) > priority_check(str[i]) ||
                    (priority_check(top(oper_top)) == priority_check(str[i]) && str[i] != '^'))) {
                out[k++] = pop(&oper_top);
                out[k++] = ' ';
            }
            push(&oper_top, str[i]);
        }
    }

    while (top(oper_top) != '@') {
        out[k++] = pop(&oper_top);
        out[k++] = ' ';
    }

    if (k > 0) {
        out[k - 1] = '\0';
    } else {
        out[0] = '\0';
    }

    return out;

}




#endif