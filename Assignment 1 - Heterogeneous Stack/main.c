#define USE_STACK
#include "../root.h"

int main(void)
{
   MixedStack st;
   initStack(&st);

    printf("Is stack empty? %s\n\n", isEmpty(&st) ? "Yes" : "No");

    printf("--- Pushing elements ---\n");
    pushInt(&st, 42);
    pushFloat(&st, 3.14f);
    pushChar(&st, 'A');
    pushString(&st, "Hello, Linux!");
    printf("Pushed 4 elements. Size = %zu\n", st.size);
    printf("Is stack empty? %s\n\n", isEmpty(&st) ? "Yes" : "No");

    printf("--- Peeking ---\n");
    peek(&st);
    printf("\n");

    printf("--- Popping everything (LIFO order) ---\n");
    while (!isEmpty(&st)) {
       pop(&st);
    }
    printf("\nIs stack empty? %s\n\n", isEmpty(&st) ? "Yes" : "No");

    printf("--- Testing underflow ---\n");
    peek(&st);
    pop(&st);

    freeStack(&st);
    return 0;
}
