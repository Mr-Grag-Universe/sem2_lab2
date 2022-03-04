#ifdef TYPE
#include "stdio.h"
#include "stdlib.h"
#include "func_template.h"
#include "Errors.h"
#include "template.h"
//TYPE TEMPLATE(stack_get, TYPE)(Stack * stack);
//Stack TEMPLATE(stack_init, TYPE)(int depth, Type type);
//void TEMPLATE(stack_free, TYPE)(Stack * stack);
//void TEMPLATE(stack_clear, TYPE)(Stack * stack);
//void TEMPLATE(stack_put, TYPE)(Stack * stack, TYPE x);
//int TEMPLATE(number_of_elements, TYPE)(Stack stack);
//void TEMPLATE(stack_print, TYPE)(Stack stack);

#define _GLU(X, Y) X##_##Y
#define GLU(X, Y) _GLU(X, Y)

#define ST GLU(Stack, TYPE)
#define LT GLU(L_el, TYPE)
ST TEMPLATE(stack_init, TYPE)(int depth, Type type) {
    ST stack;
    stack.STACK_DEPTH = depth;

    stack.type = type;

    stack.head = malloc(sizeof(LT));
    stack.head->next = NULL;

    stack.number_of_elements = 0;
    return stack;
}

void TEMPLATE(stack_put, TYPE)(ST * stack, TYPE x) {
    // printf("noe: %d\n", stack->number_of_elements);
    if (stack->number_of_elements >= stack->STACK_DEPTH) {
        fprintf(stderr, "\nThis stack is overflow!\n");
        return;
        exit(STACK_IS_OVERFLOW);
    }

    LT * y = stack->head;
    stack->head = malloc(sizeof(LT));

    stack->head->item = x;

    stack->head->next = y;

    stack->number_of_elements++;
}

void TEMPLATE(stack_delete_el, TYPE)(ST * stack) {
    if (stack->number_of_elements == 0) {
        fprintf(stderr, "This stack is empty!\n");
        exit(STACK_IS_EMPTY);
    }

    LT * x = stack->head;

    // free(stack->head->item);

    stack->head = x->next;
    stack->number_of_elements--;
    free(x);
}

void TEMPLATE(stack_clear, TYPE)(ST * stack) {
    for (int i = 0; i < stack->number_of_elements; ++i) {
        TEMPLATE(stack_delete_el, TYPE)(stack);
    }
}

void TEMPLATE(stack_free, TYPE)(ST * stack) {
    TEMPLATE(stack_clear, TYPE)(stack);
    free(stack->head);
    // free(stack);
}
/*
TYPE TEMPLATE(stack_get, TYPE)(ST * stack) {
    if (stack->number_of_elements == 0) {
        fprintf(stderr, "\nThis stack is empty!\n");
        exit(STACK_IS_EMPTY);
    }

    TYPE res = stack->head->item;

    // stack->head->item = malloc(sizeof(char));
    // ((char*) stack->head->item)[0] = *((char*) x);

    stack_delete_el(stack);

    return res;
}*/

int TEMPLATE(number_of_elements, TYPE)(ST stack) {
    return stack.number_of_elements;
}

TYPE TEMPLATE(stack_get, TYPE)(ST * stack) {
    if (stack->number_of_elements == 0) {
        fprintf(stderr, "\nThis stack is empty!\n");
        exit(STACK_IS_EMPTY);
    }

    TYPE res = stack->head->item;
    TEMPLATE(stack_delete_el, TYPE)(stack);
    // stack->head->item = malloc(sizeof(TYPE));
    // stack->head->item = *((TYPE*) x);

    return res;
}
#endif