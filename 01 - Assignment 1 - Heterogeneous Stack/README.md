# Assignment 1 - Heterogeneous Stack

## Aim

To implement a heterogeneous stack using a linked list, structures, unions, pointers, and dynamic memory allocation.

## Project Files

- `mixedstack.h` - Contains the structure definitions and all stack/input helper function definitions.
- `main.c` - Declares the stack variable locally and provides the menu-driven program.

## Data Types Supported

- Integer
- Float
- Character
- String

## Coding Standard

- No global variables.
- The stack is declared locally in `main()` as `struct MixedStack stack`.
- Stack functions receive a pointer to the structure.
- Function definitions are kept in `mixedstack.h`.
- `main.c` handles the menu and calls the functions.
- No header guards are used, as required for this assignment format.

## Concepts Used

- Structures, unions, and enumerated data types
- Pointers and linked nodes
- Dynamic memory allocation using `malloc()`
- Memory deallocation using `free()`
- LIFO (Last In, First Out)

## Compile and Run

Run from this assignment directory:

```bash
gcc -Wall -Wextra -Wpedantic -Werror -std=c11 main.c -o mixedstack
./mixedstack
```

## Operations

1. **Push:** Select a data type and insert a value.
2. **Pop:** Remove the top element.
3. **Display:** Show all elements from top to bottom.
4. **Exit:** Free allocated memory and terminate the program.
