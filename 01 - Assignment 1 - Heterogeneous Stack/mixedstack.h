#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define INPUT_SIZE 256

/* Data types supported by the heterogeneous stack. */
enum DataType
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING
};

/* Union stores one value according to its data type. */
union Data
{
    int integer;
    float decimal;
    char character;
    char *string;
};

/* Node of the linked-list stack. */
struct StackNode
{
    enum DataType type;
    union Data value;
    struct StackNode *next;
};

/* Stack structure. */
struct MixedStack
{
    struct StackNode *top;
    size_t size;
};

/* Initialize the stack. */
void initStack(struct MixedStack *stack)
{
    stack->top = NULL;
    stack->size = 0;
}

/* Check whether the stack is empty. */
int isEmpty(const struct MixedStack *stack)
{
    return stack->top == NULL;
}

/* Display one node according to its stored data type. */
void printNode(const struct StackNode *node)
{
    switch (node->type)
    {
        case TYPE_INT:
            printf("Integer: %d", node->value.integer);
            break;

        case TYPE_FLOAT:
            printf("Float: %.2f", node->value.decimal);
            break;

        case TYPE_CHAR:
            printf("Character: '%c'", node->value.character);
            break;

        case TYPE_STRING:
            printf("String: \"%s\"", node->value.string);
            break;
    }
}

/* Push a value into the stack. */
int push(struct MixedStack *stack, enum DataType type, union Data value)
{
    struct StackNode *node;

    node = malloc(sizeof(struct StackNode));

    if (node == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    node->type = type;

    if (type == TYPE_STRING)
    {
        size_t length = strlen(value.string) + 1;

        node->value.string = malloc(length);

        if (node->value.string == NULL)
        {
            free(node);
            printf("Memory allocation failed.\n");
            return 0;
        }

        memcpy(node->value.string, value.string, length);
    }
    else
    {
        node->value = value;
    }

    node->next = stack->top;
    stack->top = node;
    stack->size++;

    return 1;
}

int pushInt(struct MixedStack *stack, int value)
{
    union Data data;
    data.integer = value;
    return push(stack, TYPE_INT, data);
}

int pushFloat(struct MixedStack *stack, float value)
{
    union Data data;
    data.decimal = value;
    return push(stack, TYPE_FLOAT, data);
}

int pushChar(struct MixedStack *stack, char value)
{
    union Data data;
    data.character = value;
    return push(stack, TYPE_CHAR, data);
}

int pushString(struct MixedStack *stack, const char *value)
{
    union Data data;
    data.string = (char *)value;
    return push(stack, TYPE_STRING, data);
}

/* Remove the top element from the stack. */
int pop(struct MixedStack *stack)
{
    struct StackNode *node;

    if (isEmpty(stack))
    {
        printf("Stack underflow.\n");
        return 0;
    }

    node = stack->top;

    printf("Popped: ");
    printNode(node);
    printf("\n");

    stack->top = node->next;

    if (node->type == TYPE_STRING)
        free(node->value.string);

    free(node);
    stack->size--;

    return 1;
}

/* Display all elements from top to bottom. */
void displayStack(const struct MixedStack *stack)
{
    const struct StackNode *current;
    size_t position = 1;

    if (isEmpty(stack))
    {
        printf("\nStack is empty.\n");
        return;
    }

    printf("\nStack elements (top to bottom):\n");

    for (current = stack->top; current != NULL; current = current->next)
    {
        printf("%zu. ", position++);
        printNode(current);
        printf("\n");
    }

    printf("Total elements: %zu\n", stack->size);
}

/* Release all dynamically allocated stack memory. */
void freeStack(struct MixedStack *stack)
{
    struct StackNode *current = stack->top;

    while (current != NULL)
    {
        struct StackNode *next = current->next;

        if (current->type == TYPE_STRING)
            free(current->value.string);

        free(current);
        current = next;
    }

    stack->top = NULL;
    stack->size = 0;
}

/* Read one complete line. Returns 1, 0 for EOF, or -1 if too long. */
int readLine(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (fgets(buffer, (int)size, stdin) == NULL)
        return 0;

    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
        return 1;
    }

    if (!feof(stdin))
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            /* Discard extra input. */
        }

        return -1;
    }

    return 1;
}

int hasOnlyTrailingWhitespace(const char *text)
{
    while (isspace((unsigned char)*text))
        text++;

    return *text == '\0';
}

/* Read and validate an integer. */
int readInteger(const char *prompt, int *value)
{
    char input[INPUT_SIZE];
    char *end;
    long parsed;
    int status;

    printf("%s", prompt);
    status = readLine(input, sizeof(input));

    if (status == 0)
        return -1;
    if (status == -1)
        return 0;

    errno = 0;
    parsed = strtol(input, &end, 10);

    if (input == end || errno == ERANGE ||
        !hasOnlyTrailingWhitespace(end) ||
        parsed < INT_MIN || parsed > INT_MAX)
        return 0;

    *value = (int)parsed;
    return 1;
}

/* Read and validate a float. */
int readFloat(const char *prompt, float *value)
{
    char input[INPUT_SIZE];
    char *end;
    float parsed;
    int status;

    printf("%s", prompt);
    status = readLine(input, sizeof(input));

    if (status == 0)
        return -1;
    if (status == -1)
        return 0;

    errno = 0;
    parsed = strtof(input, &end);

    if (input == end || errno == ERANGE ||
        !hasOnlyTrailingWhitespace(end))
        return 0;

    *value = parsed;
    return 1;
}

/* Read the selected data type and push its value. */
int pushElement(struct MixedStack *stack)
{
    int choice;
    int integerValue;
    float floatValue;
    int status;
    char input[INPUT_SIZE];
    char *character;

    printf("\n========== SELECT DATA TYPE ==========\n");
    printf("1. Integer\n");
    printf("2. Float\n");
    printf("3. Character\n");
    printf("4. String\n");

    status = readInteger("Enter your choice: ", &choice);

    if (status <= 0)
        return status;

    switch (choice)
    {
        case 1:
            status = readInteger("Enter an integer: ", &integerValue);

            if (status == -1)
                return 0;
            if (status == 0)
            {
                printf("Invalid integer. No element was pushed.\n");
                break;
            }

            if (!pushInt(stack, integerValue))
                return 1;

            printf("Integer pushed successfully.\n");
            break;

        case 2:
            status = readFloat("Enter a float: ", &floatValue);

            if (status == -1)
                return 0;
            if (status == 0)
            {
                printf("Invalid float. No element was pushed.\n");
                break;
            }

            if (!pushFloat(stack, floatValue))
                return 1;

            printf("Float pushed successfully.\n");
            break;

        case 3:
            printf("Enter a single character: ");
            status = readLine(input, sizeof(input));

            if (status <= 0)
                return status;

            character = input;

            while (isspace((unsigned char)*character))
                character++;

            if (*character == '\0' || character[1] != '\0')
            {
                printf("Please enter exactly one character.\n");
                break;
            }

            if (!pushChar(stack, *character))
                return 1;

            printf("Character pushed successfully.\n");
            break;

        case 4:
            printf("Enter a string: ");
            status = readLine(input, sizeof(input));

            if (status <= 0)
                return status;

            if (input[0] == '\0')
            {
                printf("Empty strings are not accepted.\n");
                break;
            }

            if (!pushString(stack, input))
                return 1;

            printf("String pushed successfully.\n");
            break;

        default:
            printf("Invalid data type choice.\n");
    }

    return 1;
}
