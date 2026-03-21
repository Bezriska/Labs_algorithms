#include <stdio.h>
#include "validation.h"
#include "rpn.h"
#define MAX_LENGHS  256



// opers priority:
// '+' || '-': 1
// '*' || '/': 2
// '^': 3


int main() {

    char str[MAX_LENGHS] = "(2+2-1)*2";

    if (validation(str)) {
        char* validated_str = str;
        OBJ* rp = rpn(validated_str);
        show(rp);
        printf("\n");
    } else {
        printf("String is not valid\n");
        return 0;
    }

    




}