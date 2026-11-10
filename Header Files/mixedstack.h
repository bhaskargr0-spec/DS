#ifndef MIXEDSTACK_H
#define MIXEDSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_CHAR,
  TYPE_STRING
} DataType;

typedef union {
  int i;
  float f;
  char c;
  char *s;
} Data;

typedef struct Node {
  DataType type;
  Data       value;
  struct Node *next;
} Node;

typedef struct {
  Node *top;
  size_t size;
} MixedStack;

static inline void initStack(MixedStack *st)
{
   st->top = NULL;
   st->size = 0;
}

static inline int isEmpty(const MixedStack *st)
{
   return st->top == NULL;
}

static inline void printNode(const Node *n)
{
    switch (n->type) {
      case TYPE_INT: printf("int: %d", n->value.i);     break;
      case TYPE_FLOAT: printf("float: %.2f", n->value.f); break;
      case TYPE_CHAR: printf("char: '%c'", n->value.c); break;
      case TYPE_STRING: printf("string: \"%s\"", n->value.s); break;
    }
}

static inline int push(MixedStack *st, DataType type, Data value)
{
   Node *n = (Node *)malloc(sizeof(Node));
   if (n == NULL) {
      fprintf(stderr, "Error: out of memory (node)\n");
      return 0;
   }

    n->type = type;

    if (type == TYPE_STRING) {
       size_t len = strlen(value.s) + 1;
       n->value.s = (char *)malloc(len);
       if (n->value.s == NULL) {
          fprintf(stderr, "Error: out of memory (string)\n");
          free(n);
          return 0;
       }
       memcpy(n->value.s, value.s, len);
    } else {
       n->value = value;
    }

    n->next = st->top;
    st->top = n;
    st->size++;
    return 1;
}

static inline int pushInt(MixedStack *st, int x)
{
   Data d; d.i = x;
   return push(st, TYPE_INT, d);
}

static inline int pushFloat(MixedStack *st, float x)
{
   Data d; d.f = x;
   return push(st, TYPE_FLOAT, d);
}

static inline int pushChar(MixedStack *st, char x)
{
   Data d; d.c = x;
   return push(st, TYPE_CHAR, d);
}

static inline int pushString(MixedStack *st, const char *x)
{
   Data d; d.s = (char *)x;
   return push(st, TYPE_STRING, d);
}

static inline int peek(const MixedStack *st)
{
   if (isEmpty(st)) {
      fprintf(stderr, "Stack underflow: nothing to peek\n");
      return 0;
    }
    printf("Top -> ");
    printNode(st->top);
    printf("\n");
    return 1;
}

static inline int pop(MixedStack *st)
{
   Node *n;

    if (isEmpty(st)) {
       fprintf(stderr, "Stack underflow: nothing to pop\n");
       return 0;
    }

    n = st->top;
    printf("Popped -> ");
    printNode(n);
    printf("\n");

    st->top = n->next;
    if (n->type == TYPE_STRING)
       free(n->value.s);
    free(n);
    st->size--;
    return 1;
}

static inline void freeStack(MixedStack *st)
{
   Node *n = st->top;
    while (n != NULL) {
       Node *next = n->next;
       if (n->type == TYPE_STRING)
          free(n->value.s);
       free(n);
       n = next;
    }
    st->top = NULL;
    st->size = 0;
}

#endif
