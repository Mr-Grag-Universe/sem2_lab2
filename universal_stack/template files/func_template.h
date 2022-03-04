//#include "Stack.h"
#include "TypesInStack.h"
#ifdef TYPE
#include "template.h"

#define _GLU(X, Y) X##_##Y
#define GLU(X, Y) _GLU(X, Y)

#define ST GLU(Stack, TYPE)
#define LT GLU(L_el, TYPE)

typedef struct LT {
    TYPE item;
    struct LT * next;
} LT;
typedef struct ST {
    int STACK_DEPTH;
    Type type;
    LT * head;
    int number_of_elements;
} ST;

TYPE TEMPLATE(stack_get, TYPE)(ST * stack);
ST TEMPLATE(stack_init, TYPE)(int depth, Type type);
void TEMPLATE(stack_free, TYPE)(ST * stack);
void TEMPLATE(stack_clear, TYPE)(ST * stack);
void TEMPLATE(stack_put, TYPE)(ST * stack, TYPE x);
int TEMPLATE(number_of_elements, TYPE)(ST stack);
void TEMPLATE(stack_print, TYPE)(ST stack);
#endif
