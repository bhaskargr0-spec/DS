#define USE_STACK
#include "../root.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define INPUT_SIZE 256

/*
 * Read one line from standard input.
 * Returns 1 on success, 0 on end-of-file, and -1 if the line is too long.
 */
static int readLine(char *buffer, size_t size)
{
    size_t length;

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return 1;
    }

    if (!feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Discard the remainder of an overlong input line. */
        }
        return -1;
    }

    return 1;
}

static char *skipWhitespace(char *text)
{
    while (isspace((unsigned char)*text)) {
        text++;
    }
    return text;
}

static int hasOnlyTrailingWhitespace(const char *text)
{
    while (isspace((unsigned char)*text)) {
        text++;
    }
    return *text == '\0';
}

/* Returns 1 for a valid integer, 0 for invalid input, and -1 for EOF. */
static int readInteger(const char *prompt, int *value)
{
    char input[INPUT_SIZE];
    char *end;
    long parsed;
    int status;

    printf("%s", prompt);
    status = readLine(input, sizeof(input));

    if (status <= 0) {
        return status;
    }

    errno = 0;
    parsed = strtol(input, &end, 10);
    end = skipWhitespace(end);

    if (input == end || errno == ERANGE || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

/* Returns 1 for a valid float, 0 for invalid input, and -1 for EOF. */
static int readFloat(const char *prompt, float *value)
{
    char input[INPUT_SIZE];
    char *end;
    float parsed;
    int status;

    printf("%s", prompt);
    status = readLine(input, sizeof(input));

    if (status <= 0) {
        return status;
    }

    errno = 0;
    parsed = strtof(input, &end);

    if (input == end || errno == ERANGE ||
        !hasOnlyTrailingWhitespace(end)) {
        return 0;
    }

    *value = parsed;
    return 1;
}

static void displayStack(const MixedStack *st)
{
    const Node *current;
    size_t position = 1;

    if (isEmpty(st)) {
        printf("\nStack is empty.\n");
        return;
    }

    printf("\nStack elements (top to bottom):\n");

    for (current = st->top; current != NULL; current = current->next) {
        printf("%zu. ", position++);
        printNode(current);
        printf("\n");
    }

    printf("Total elements: %zu\n", st->size);
}

static int pushElement(MixedStack *st)
{
    int choice;
    int integerValue;
    float floatValue;
    char input[INPUT_SIZE];
    int status;
    char *character;

    printf("\n========== SELECT DATA TYPE ==========\n");
    printf("1. Integer\n");
    printf("2. Float\n");
    printf("3. Character\n");
    printf("4. String\n");
    printf("======================================\n");

    status = readInteger("Enter your choice: ", &choice);

    if (status == 0) {
        printf("Invalid input. Please enter a number from 1 to 4.\n");
        return 1;
    }

    if (status == -1) {
        return 0;
    }

    switch (choice) {
        case 1:
            status = readInteger("Enter an integer: ", &integerValue);
            if (status == -1) {
                return 0;
            }
            if (status == 0) {
                printf("Invalid integer. No element was pushed.\n");
                break;
            }
            if (pushInt(st, integerValue)) {
                printf("Integer pushed successfully.\n");
            } else {
                printf("Unable to push the integer.\n");
            }
            break;

        case 2:
            status = readFloat("Enter a float: ", &floatValue);
            if (status == -1) {
                return 0;
            }
            if (status == 0) {
                printf("Invalid float. No element was pushed.\n");
                break;
            }
            if (pushFloat(st, floatValue)) {
                printf("Float pushed successfully.\n");
            } else {
                printf("Unable to push the float.\n");
            }
            break;

        case 3:
            printf("Enter a single character: ");
            status = readLine(input, sizeof(input));
            if (status == 0) {
                return 0;
            }
            if (status == -1) {
                printf("Input is too long. No element was pushed.\n");
                break;
            }

            character = skipWhitespace(input);
            if (*character == '\0' || character[1] != '\0') {
                printf("Please enter exactly one character.\n");
                break;
            }

            if (pushChar(st, *character)) {
                printf("Character pushed successfully.\n");
            } else {
                printf("Unable to push the character.\n");
            }
            break;

        case 4:
            printf("Enter a string: ");
            status = readLine(input, sizeof(input));
            if (status == 0) {
                return 0;
            }
            if (status == -1) {
                printf("String is too long. No element was pushed.\n");
                break;
            }
            if (input[0] == '\0') {
                printf("Empty strings are not accepted.\n");
                break;
            }

            if (pushString(st, input)) {
                printf("String pushed successfully.\n");
            } else {
                printf("Unable to push the string.\n");
            }
            break;

        default:
            printf("Invalid data type choice. Please select 1 to 4.\n");
            break;
    }

    return 1;
}

int main(void)
{
    MixedStack st;
    int choice;
    int status;
    int running = 1;

    initStack(&st);

    while (running) {
        printf("\n====================================\n");
        printf("          HETEROGENEOUS STACK\n");
        printf("====================================\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("====================================\n");

        status = readInteger("Enter your choice: ", &choice);

        if (status == 0) {
            printf("Invalid input. Please enter a number from 1 to 4.\n");
            continue;
        }

        if (status == -1) {
            printf("\nEnd of input. Exiting the program.\n");
            break;
        }

        switch (choice) {
            case 1:
                running = pushElement(&st);
                break;

            case 2:
                if (!pop(&st)) {
                    printf("The stack is empty; nothing was removed.\n");
                }
                break;

            case 3:
                displayStack(&st);
                break;

            case 4:
                running = 0;
                printf("Exiting Heterogeneous Stack.\n");
                break;

            default:
                printf("Invalid choice. Please select 1 to 4.\n");
                break;
        }
    }

    freeStack(&st);
    return 0;
}
