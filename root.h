#ifndef ROOT_H
#define ROOT_H

#if defined(USE_STACK) && defined(USE_PRIORITY_QUEUE)
#error "root.h: define only ONE assignment selection macro."
#endif

#if defined(USE_STACK)
#include "01 - Assignment 1 - Heterogeneous Stack/mixedstack.h"
#elif defined(USE_PRIORITY_QUEUE)
#include "03 - Assignment 3 - Priority Queue/priorityqueue.h"
#else
#error "root.h: define an assignment selection macro before including root.h."
#endif

#endif
