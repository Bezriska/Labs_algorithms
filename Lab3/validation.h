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
    char prev = '@';
    int bracket_count = 0;
    
    for(int i = 0; str[i] != '\0'; ++i) {
        if (prev == '@') {
            prev = str[i];

            if (str[i] == '(') {
                ++bracket_count;
            }

            if (!(isalnum(str[i]) || str[i] == '(')) {
                return 0;
            }

        } else {
            
            if (!(isalnum(str[i]) || isoper(str[i]))) {
                return 0;
            }

            // Проверка чередования не может быть два оператора или две цифры подряд (кроме скобок)
            if ((isoper(prev) && prev != '(' && prev != ')') && (isoper(str[i]) && str[i] != '(' && str[i] != ')')) {
                return 0;
            }
            if (isalnum(prev) && isalnum(str[i])) {
                return 0;
            }

            // После открывающей скобки должна быть цифра или другая открывающая скобка
            if (prev == '(' && !(isalnum(str[i]) || str[i] == '(')) {
                return 0;
            }

            // Перед закрывающей скобкой должна быть цифра или другая закрывающая скобка
            if (str[i] == ')' && !(isalnum(prev) || prev == ')')) {
                return 0;
            }

            // После закрывающей скобки должен быть оператор, закрывающая скобка или конец строки
            if (prev == ')' && !(isoper(str[i]) || str[i + 1] == '\0')) {
                return 0;
            }

            // Перед открывающей скобкой должен быть оператор или другая открывающая скобка
            if (str[i] == '(' && !(isoper(prev) || prev == '(')) {
                return 0;
            }

            // Оператор не может быть в конце (кроме закрывающей скобки)
            if (isoper(str[i]) && str[i] != ')' && str[i + 1] == '\0') {
                return 0;
            }

            // Подсчет скобок
            if (str[i] == '(') {
                ++bracket_count;
            }

            if (str[i] == ')') {
                --bracket_count;
                // Проверка, что закрывающих скобок не больше, чем открывающих
                if (bracket_count < 0) {
                    return 0;
                }
            }

            prev = str[i];
            
        }
    }
    
    if (bracket_count == 0) {
        return 1;
    } else {
        return 0;
    }
        

}




#endif