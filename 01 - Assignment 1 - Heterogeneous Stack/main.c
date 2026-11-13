#include <stdio.h>
#include "mixedstack.h"

int main(void)
{
    struct MixedStack stack;
    int choice;
    int status;
    int running = 1;

    initStack(&stack);

    while (running)
    {
        printf("\n====================================\n");
        printf("       HETEROGENEOUS STACK\n");
        printf("====================================\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        status = readInteger("Enter your choice: ", &choice);

        if (status == 0)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (status == -1)
        {
            printf("\nEnd of input. Exiting program.\n");
            break;
        }

        switch (choice)
        {
            case 1:
                status = pushElement(&stack);

                if (status == 0)
                {
                    printf("\nEnd of input. Exiting program.\n");
                    running = 0;
                }
                else if (status == -1)
                {
                    printf("Input is too long. Please try again.\n");
                }
                break;

            case 2:
                pop(&stack);
                break;

            case 3:
                displayStack(&stack);
                break;

            case 4:
                printf("Exiting Heterogeneous Stack.\n");
                running = 0;
                break;

            default:
                printf("Invalid choice. Please select 1 to 4.\n");
        }
    }

    freeStack(&stack);
    return 0;
}
