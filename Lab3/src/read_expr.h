#ifndef READ_H
#define READ_H
#include <stdio.h>
#include <stdlib.h>

char* read_expr() {
    char* expression = NULL;
    size_t len = 0;
    ssize_t readed;
    while ((readed = getline(&expression, &len, stdin)) != -1) {
        if (readed > 0 && expression[readed - 1] == '\n') {
            expression[readed - 1] = '\0';
            return expression;
        }
    }

    return expression;

}




#endif