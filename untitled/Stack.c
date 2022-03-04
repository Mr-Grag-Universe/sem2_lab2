#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "Errors.h"

#ifdef VECTOR
Stack stack_init(int depth) {
    Stack stack;
    stack.STACK_DEPTH = depth;
    stack.head = 0;
    stack.ptr = malloc(stack.STACK_DEPTH * sizeof(int));
    return stack;
}

void stack_free(Stack * stack) {
    free(stack->ptr);
    stack->head = 0;
    // free(stack);
}

void stack_clear(Stack * stack) {
    stack->head = 0;
    for (int i = 0; i < stack->STACK_DEPTH; ++i)
        stack->ptr[i] = 0;
}

void stack_put(Stack * stack, int x) {
    if (stack->head == stack->STACK_DEPTH-1) {
        fprintf(stderr, "\nThis stack is overflow!\n");
        return;
        exit(STACK_IS_OVERFLOW);
    }

    stack->ptr[stack->head] = x;
    stack->head++;
}

int stack_get(Stack * stack) {
    if (stack->head == 0) {
        fprintf(stderr, "\nThis stack is empty!\n");
        exit(STACK_IS_EMPTY);
    }

    stack->head -= 1;
    if (stack->head < 0)
        stack->head = stack->STACK_DEPTH-1;

    // steck->head--;
    
    int ind = stack->head;
    return stack->ptr[ind];
}

int number_of_elements(Stack stack) {
    return stack.head;
}

void stack_print(Stack stack) {
    for (int i = 0; i < stack.head; ++i) {
        printf("%d ", stack.ptr[i]);
    }
    printf("\n");
}
#endif // VECTOR

#ifndef LIST
Stack stack_init(int depth) {
    Stack stack;
    stack.STACK_DEPTH = depth;

    stack.head = malloc(sizeof(L_el));
    stack.head->next = NULL;
    stack.head->item = 0;

    stack.number_of_elements = 0;
    return stack;
}

void stack_put(Stack * stack, int x) {
    // printf("noe: %d\n", stack->number_of_elements);
    if (stack->number_of_elements >= stack->STACK_DEPTH) {
        fprintf(stderr, "\nThis stack is overflow!\n");
        return;
        exit(STACK_IS_OVERFLOW);
    }

    L_el * y = stack->head;
    stack->head = malloc(sizeof(L_el));
    stack->head->item = x;
    stack->head->next = y;

    stack->number_of_elements++;
}

void satck_delete_el(Stack * stack) {
    if (stack->number_of_elements == 0) {
        fprintf(stderr, "This stack is empty!\n");
        exit(STACK_IS_EMPTY);
    }

    L_el * x = stack->head;
    stack->head = x->next;
    stack->number_of_elements--;
    free(x);
}

void stack_clear(Stack * stack) {
    for (int i = 0; i < stack->number_of_elements; ++i) {
        satck_delete_el(stack);
    }

}

void stack_free(Stack * stack) {
    stack_clear(stack);
    free(stack->head);
    // free(stack);
}

int stack_get(Stack * stack) {
    if (stack->number_of_elements == 0) {
        fprintf(stderr, "\nThis stack is empty!\n");
        exit(STACK_IS_EMPTY);
    }

    int res = stack->head->item;
    satck_delete_el(stack);

    return res;
}

int number_of_elements(Stack stack) {
    return stack.number_of_elements;
}

void stack_print(Stack stack) {
    L_el * el = stack.head;
    for (int i = 0; i < stack.number_of_elements; ++i) {
        printf("%d ", el->item);
        el = el->next;
    }
    printf("\n");
}
#endif // LIST