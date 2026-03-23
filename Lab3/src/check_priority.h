#ifndef CH_P_H
#define CH_P_H
#include <stdio.h>
// #include "validation.h"
// #include "rpn.h"


// char* change_opers(char* validated_str) {
//     for (int i = 0; validated_str[i] != '\0'; ++i) {
        
//         if (isoper(validated_str[i])) {
//             if (validated_str[i] == '+') {
//                 validated_str[i] = initiate_oper()
//             }
//         }
//     }


// }

int priority_check(char op) {
    if (op == '-' || op == '+') {
        return 1;
    }

    if (op == '*' || op == '/') {
        return 2;
    }

    if (op == '^') {
        return 3;
    }
    
    return 0;
}





#endif