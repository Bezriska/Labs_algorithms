#include <stdio.h>
#include <stdlib.h>
#include "validation.h"
#include "rpn.h"
#define MAX_LENGHS  256



// opers priority:
// '+' || '-': 1
// '*' || '/': 2
// '^': 3


int main() {

    char str[MAX_LENGHS] = "(12+23-1)*20";

    if (validation(str)) {
        char* validated_str = str;
        char* rp = rpn(validated_str);
        if (rp == NULL) {
            printf("Memory allocation error\n");
            return 1;
        }
        printf("%s\n", rp);
        free(rp);
    } else {
        printf("String is not valid\n");
        return 0;
    }

    




}