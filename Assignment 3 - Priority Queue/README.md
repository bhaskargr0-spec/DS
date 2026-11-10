# Assignment 3 - Priority Queue Using Arrays

## Aim

To implement a priority queue using three separate linear queues represented by arrays.

## Priority Levels

- Priority 1: Low
- Priority 2: Medium
- Priority 3: High

A larger priority number represents a higher priority. Therefore, deletion is performed from the High Priority Queue first, followed by the Medium Priority Queue and then the Low Priority Queue.

## Project Files

- `../root.h` - Central assignment header selector.
- `priorityqueue.h` - Contains the queue arrays, front/rear variables, and queue operations.
- `main.c` - Contains the menu-driven program and includes only `../root.h` as its header.

## Header Selection

The first two lines of `main.c` select the priority queue implementation:

```c
#define USE_PRIORITY_QUEUE
#include "../root.h"
```

## Implementation

The program uses three integer arrays:

- `low[MAX]`
- `medium[MAX]`
- `high[MAX]`

Each queue has its own `front` and `rear` variables. The maximum capacity of each queue is 5.

The program provides the following operations:

1. **Insert:** Adds an item to the rear of the queue selected by the user.
2. **Delete:** Removes an item from the front of the highest-priority non-empty queue.
3. **Display:** Shows the current items in High, Medium and Low priority queues.
4. **Exit:** Terminates the program.

## Compile and Run

Run from this assignment directory:

```bash
gcc -Wall -Wextra -std=c11 -pedantic main.c -o priority_queue
./priority_queue
```

## Queue Conditions

For each queue:

- Initially, `front = 0` and `rear = -1`.
- The queue is empty when `front > rear`.
- The queue is full when `rear == MAX - 1`.

## Limitations

This implementation uses simple linear queues, not circular queues. Once the rear reaches the last array position, no more items can be inserted into that queue, even if earlier items have been deleted. Also, strict priority service can cause lower-priority items to wait for a long time if higher-priority items keep arriving.

## Header Design Note

`priorityqueue.h` currently contains global variable definitions and function definitions. Include it in exactly one `.c` file per program, as this assignment does. For a future multi-file implementation, move the definitions into a corresponding `.c` implementation file and leave declarations in the header.

## Input Handling and Known Limitations

The program reads the menu choice, the item and the priority with `scanf("%d")`.
After every `scanf`, `clear_input_buffer()` discards the rest of that input line,
so each prompt reads only the input typed for it. If `scanf` returns `EOF`
(the input has ended), the program exits cleanly.

Known limitations of this simple approach:

1. **Trailing characters are ignored.** Input such as `77abc` is read as 77, and
   `abc` is discarded.
2. **Extra values on one line are discarded.** Typing `1 10 3` at the menu uses
   only `1`; the item and priority are then asked for separately.
3. **Out-of-range numbers are not detected.** If a number does not fit in an
   `int`, `scanf("%d")` does not report an error. The C standard leaves the result
   undefined, so the behaviour depends on the compiler and platform. On some
   systems the value wraps around, which means a very large number could be read
   as a different value, including a valid priority of 1, 2 or 3. Detecting this
   reliably would require reading the line with `fgets` and converting it with
   `strtol`, which is beyond the scope of this assignment.
4. **Empty lines are skipped.** Pressing Enter without typing a number makes
   `scanf` keep waiting; no error message is shown.
5. **End of input** (Ctrl+D on Linux/macOS, Ctrl+Z then Enter on Windows) exits
   the program.
