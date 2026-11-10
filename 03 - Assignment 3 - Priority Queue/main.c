#define USE_PRIORITY_QUEUE
#include "../root.h"

int main(void)
{
    int choice, item, priority;
    int status;

    do
    {
        choice = 0;
        printf("\n===== PRIORITY QUEUE MENU =====\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        status = scanf("%d", &choice);
        clear_input_buffer();

        if (status == EOF)
        {
            printf("\nInput ended. Exiting program.\n");
            break;
        }
        if (status != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                printf("Enter item: ");
                status = scanf("%d", &item);
                clear_input_buffer();
                if (status == EOF)
                {
                    printf("\nInput ended. Exiting program.\n");
                    return 0;
                }
                if (status != 1)
                {
                    printf("Invalid item. Please enter an integer.\n");
                    break;
                }

                printf("Enter priority (1 = Low, 2 = Medium, 3 = High): ");
                status = scanf("%d", &priority);
                clear_input_buffer();
                if (status == EOF)
                {
                    printf("\nInput ended. Exiting program.\n");
                    return 0;
                }
                if (status != 1)
                {
                    printf("Invalid priority. Please enter an integer.\n");
                    break;
                }

                insert(item, priority);
                break;

            case 2:
                delete_item();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please select 1 to 4.\n");
        }

    } while (choice != 4);

    return 0;
}
