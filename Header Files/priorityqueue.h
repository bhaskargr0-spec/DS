#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdio.h>

#define MAX 5

/* Three separate linear queues */
int low[MAX], medium[MAX], high[MAX];

/* Front and rear positions for each queue */
int front_low = 0, rear_low = -1;
int front_medium = 0, rear_medium = -1;
int front_high = 0, rear_high = -1;

/* Remove invalid characters from the input line */
void clear_input_buffer(void)
{
    int ch;
    while ((ch = getchar()) != '\\n' && ch != EOF)
    {
        /* discard remaining input */
    }
}

/* Insert an item into the selected priority queue */
void insert(int item, int priority)
{
    if (priority == 1)
    {
        if (rear_low == MAX - 1)
            printf("Low priority queue is full.\\n");
        else
        {
            low[++rear_low] = item;
            printf("%d inserted into Low Priority Queue.\\n", item);
        }
    }
    else if (priority == 2)
    {
        if (rear_medium == MAX - 1)
            printf("Medium priority queue is full.\\n");
        else
        {
            medium[++rear_medium] = item;
            printf("%d inserted into Medium Priority Queue.\\n", item);
        }
    }
    else if (priority == 3)
    {
        if (rear_high == MAX - 1)
            printf("High priority queue is full.\\n");
        else
        {
            high[++rear_high] = item;
            printf("%d inserted into High Priority Queue.\\n", item);
        }
    }
    else
        printf("Invalid priority. Enter 1, 2, or 3.\\n");
}

/* Delete from the highest-priority non-empty queue */
void delete_item(void)
{
    if (front_high <= rear_high)
    {
        printf("Deleted item: %d (High Priority)\\n", high[front_high]);
        front_high++;
    }
    else if (front_medium <= rear_medium)
    {
        printf("Deleted item: %d (Medium Priority)\\n", medium[front_medium]);
        front_medium++;
    }
    else if (front_low <= rear_low)
    {
        printf("Deleted item: %d (Low Priority)\\n", low[front_low]);
        front_low++;
    }
    else
        printf("Priority Queue is empty. Deletion not possible.\\n");
}

/* Display all waiting items in service order */
void display(void)
{
    int i;

    printf("\\n--- Priority Queue Contents ---\\n");

    printf("High Priority: ");
    if (front_high > rear_high)
        printf("Empty");
    else
        for (i = front_high; i <= rear_high; i++)
            printf("%d ", high[i]);

    printf("\\nMedium Priority: ");
    if (front_medium > rear_medium)
        printf("Empty");
    else
        for (i = front_medium; i <= rear_medium; i++)
            printf("%d ", medium[i]);

    printf("\\nLow Priority: ");
    if (front_low > rear_low)
        printf("Empty");
    else
        for (i = front_low; i <= rear_low; i++)
            printf("%d ", low[i]);

    printf("\\n");
}

#endif
