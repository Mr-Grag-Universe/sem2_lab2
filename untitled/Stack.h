#define S2

#ifdef VECTOR
#ifndef STACK_V
#define STACK_V
typedef struct Stack {
    int STACK_DEPTH;
    int * ptr;
    int head;
} Stack;
#endif
#endif // VECTOR

#ifndef LIST
#ifndef STACK_L
#define STACK_L
typedef struct L_el {
    int item;
    struct L_el * next;
} L_el;

typedef struct Stack {
    int STACK_DEPTH;
    L_el * head;
    int number_of_elements;
} Stack;
#endif
#endif // LIST

#ifndef STACK_F
#define STACK_F
Stack stack_init(int depth);
void stack_free(Stack * stack);
void stack_clear(Stack * stack);
void stack_put(Stack * stack, int x);
int stack_get(Stack * stack);
int number_of_elements(Stack stack);
void stack_print(Stack stack);
#endif