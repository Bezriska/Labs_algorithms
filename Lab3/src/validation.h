#ifndef VAL_H
#define VAL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isoper(char ch) {
    if (ch == '-' || ch == '+' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')') {
        return 1;
    } else {
        return 0;
    }
}


int validation(char* str) {
    int bracket_count = 0;
    int expecting_operand = 1; // 1 - ждем операнд или (, 0 - ждем опертор или )

    for (int i = 0; str[i] != '\0'; ++i) {
        if (isspace((unsigned char)str[i])) {
            continue;
        }

        if (isdigit((unsigned char)str[i]) || isalpha((unsigned char)str[i])) {
            if (!expecting_operand) {
                return 0;
            }

            while (isdigit((unsigned char)str[i + 1]) || isalpha((unsigned char)str[i + 1])) {
                ++i;
            }
            expecting_operand = 0;
            continue;
        }

        if (str[i] == '(') {
            if (!expecting_operand) {
                return 0;
            }
            ++bracket_count;
            continue;
        }

        if (str[i] == ')') {
            if (expecting_operand || bracket_count == 0) {
                return 0;
            }
            --bracket_count;
            expecting_operand = 0;
            continue;
        }

        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {
            if (expecting_operand) {
                return 0;
            }
            expecting_operand = 1;
            continue;
        }

        return 0;
    }

    return (bracket_count == 0 && !expecting_operand);
        

}




#endif