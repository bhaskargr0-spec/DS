#include <stdio.h>

#define MAX 5
#define ITEM_SIZE 32

/* All priority queue data is grouped inside this structure. */
struct PriorityQueue
{
    char low[MAX][ITEM_SIZE];
    char medium[MAX][ITEM_SIZE];
    char high[MAX][ITEM_SIZE];

    int front_low;
    int rear_low;
    int front_medium;
    int rear_medium;
    int front_high;
    int rear_high;
};

/* Initialize all three queues. */
void initQueue(struct PriorityQueue *q)
{
    q->front_low = 0;
    q->rear_low = -1;
    q->front_medium = 0;
    q->rear_medium = -1;
    q->front_high = 0;
    q->rear_high = -1;
}

/* Remove remaining characters from the input line. */
void clear_input_buffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* Discard remaining input. */
    }
}

/* Insert an integer or alphabetic item into the selected queue. */
void insert(struct PriorityQueue *q, const char item[], int priority)
{
    if (priority == 1)
    {
        if (q->rear_low == MAX - 1)
            printf("Low priority queue is full.\n");
        else
        {
            snprintf(q->low[++q->rear_low], ITEM_SIZE, "%s", item);
            printf("%s inserted into Low Priority Queue.\n", item);
        }
    }
    else if (priority == 2)
    {
        if (q->rear_medium == MAX - 1)
            printf("Medium priority queue is full.\n");
        else
        {
            snprintf(q->medium[++q->rear_medium], ITEM_SIZE, "%s", item);
            printf("%s inserted into Medium Priority Queue.\n", item);
        }
    }
    else if (priority == 3)
    {
        if (q->rear_high == MAX - 1)
            printf("High priority queue is full.\n");
        else
        {
            snprintf(q->high[++q->rear_high], ITEM_SIZE, "%s", item);
            printf("%s inserted into High Priority Queue.\n", item);
        }
    }
    else
        printf("Invalid priority. Enter 1, 2, or 3.\n");
}

/* Delete from the highest-priority non-empty queue. */
void delete_item(struct PriorityQueue *q)
{
    if (q->front_high <= q->rear_high)
    {
        printf("Deleted item: %s (High Priority)\n",
               q->high[q->front_high]);
        q->front_high++;
    }
    else if (q->front_medium <= q->rear_medium)
    {
        printf("Deleted item: %s (Medium Priority)\n",
               q->medium[q->front_medium]);
        q->front_medium++;
    }
    else if (q->front_low <= q->rear_low)
    {
        printf("Deleted item: %s (Low Priority)\n",
               q->low[q->front_low]);
        q->front_low++;
    }
    else
        printf("Priority Queue is empty. Deletion not possible.\n");
}

/* Display all waiting items in service order. */
void display(const struct PriorityQueue *q)
{
    int i;

    printf("\n--- Priority Queue Contents ---\n");

    printf("High Priority: ");
    if (q->front_high > q->rear_high)
        printf("Empty");
    else
        for (i = q->front_high; i <= q->rear_high; i++)
            printf("%s ", q->high[i]);

    printf("\nMedium Priority: ");
    if (q->front_medium > q->rear_medium)
        printf("Empty");
    else
        for (i = q->front_medium; i <= q->rear_medium; i++)
            printf("%s ", q->medium[i]);

    printf("\nLow Priority: ");
    if (q->front_low > q->rear_low)
        printf("Empty");
    else
        for (i = q->front_low; i <= q->rear_low; i++)
            printf("%s ", q->low[i]);

    printf("\n");
}
