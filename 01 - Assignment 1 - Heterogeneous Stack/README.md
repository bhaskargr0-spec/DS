# Assignment 1 - Heterogeneous Stack

## Aim

To implement a heterogeneous stack in C supporting `push`, `pop`, `peek`, and `isEmpty` using structures, unions, pointers, and dynamic memory.

## Problem Statement

Write a complete header file, `mixedstack.h`, that allows push, pop, peek, and isEmpty operations for a heterogeneous stack.

## Project Files

- `../root.h` - Central assignment header selector.
- `mixedstack.h` - Contains the stack data types and stack operation functions.
- `main.c` - Demonstrates the stack operations and includes only `../root.h` as its header.

## Header Selection

The first two lines of `main.c` select the stack implementation:

```c
#define USE_STACK
#include "../root.h"
```

## Data Types Supported

- Integer
- Float
- Character
- String

## Concepts Used

- Structures and unions
- Enumerated data types
- Pointers and linked nodes
- Dynamic memory allocation using `malloc()`
- Memory deallocation using `free()`
- Header guards and a separate header file
- Conditional compilation through the central `root.h`

## Compile

Run from this assignment directory:

```bash
gcc -Wall -Wextra -std=c11 -pedantic main.c -o mixedstack
```

## Run

```bash
./mixedstack
```

## Operations Demonstrated

- Initialize the stack
- Check whether the stack is empty
- Push an integer, float, character, and string
- Peek at the top element
- Pop elements in LIFO order
- Test stack underflow
- Free allocated stack memory
