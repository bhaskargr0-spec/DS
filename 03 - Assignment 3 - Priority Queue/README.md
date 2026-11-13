# Assignment 3 - Priority Queue Using Arrays

## Aim

To implement a priority queue using three separate linear queues represented by arrays.

## Priority Levels

- Priority 1: Low
- Priority 2: Medium
- Priority 3: High

Deletion is performed from the High Priority Queue first, followed by Medium and then Low.

## Project Files

- `priorityqueue.h` - Contains the structure definition and all priority queue function definitions.
- `main.c` - Declares the queue variable locally and provides the menu-driven program.

## Coding Standard

- No global variables.
- The queue is declared locally in `main()` as `struct PriorityQueue queue`.
- Queue functions receive a pointer to the structure.
- Function definitions are kept in `priorityqueue.h`.
- `main.c` handles the menu and calls the functions.
- No header guards are used, as required for this assignment format.

## Data Items

The queue accepts integer values, single alphabets, and words. Items are stored as text in fixed-size character arrays. Each item can contain up to 31 characters.

## Operations

1. **Insert:** Adds an item to the selected priority queue.
2. **Delete:** Removes an item from the highest-priority non-empty queue.
3. **Display:** Shows the contents of High, Medium, and Low priority queues.
4. **Exit:** Terminates the program.

## Compile and Run

Run from this assignment directory:

```bash
gcc -Wall -Wextra -Wpedantic -Werror -std=c11 main.c -o priority_queue
./priority_queue
```

## Queue Conditions

For each queue:

- Initially, `front = 0` and `rear = -1`.
- The queue is empty when `front > rear`.
- The queue is full when `rear == MAX - 1`.

## Limitations

This implementation uses simple linear queues, not circular queues. Once the rear reaches the last array position, no more items can be inserted into that queue, even if earlier items have been deleted. Strict priority service can also delay lower-priority items when higher-priority items keep arriving.
