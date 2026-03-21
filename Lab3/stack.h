#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct OBJ {
    char data;
    struct OBJ* next;
} OBJ;

OBJ* stack_init() {
    OBJ* temp = (OBJ*)malloc(sizeof(OBJ));
    temp->data = '@';
    temp->next = NULL;
    return temp;
}

void push(OBJ** top, char data) {
    OBJ* ptr = (OBJ*)malloc(sizeof(OBJ));
    ptr->data = data;
    ptr->next = *top;
    *top = ptr;
}

char pop(OBJ** top) {
    if(*top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    OBJ* temp = *top;
    char value = temp->data;
    *top = temp->next;
    free(temp);
    return value;
}

void show(OBJ* top) {
    if (top == NULL) {
        printf("\n");
        return;
    }

    show(top->next);
    if (top->data != '@') {
        printf("%c", top->data);
    }
}

char top(OBJ* top) {
    return top->data;
}

#endif