#include "../linked_list/list.h"
#include "errors.h"

#ifndef DSA_READ_H
#define DSA_READ_H

typedef int (*one_arg_func)(List *list);
typedef int (*two_arg_func)(List *list, int num);

typedef struct {
    int num_list;
    List* list;
} ListMapping;

typedef enum {
    FUNC_ONE_ARG,
    FUNC_TWO_ARGS
} FunctionType;

// Union for function pointers
typedef union {
    int (*func_one_arg)(List *);
    int (*func_two_args)(List *, int);
} FunctionPointer;

typedef struct {
    const char *name;
    FunctionType type;
    FunctionPointer function;
} FunctionMapping;

void read_from_user(List* list1, List* list2);

#endif /* DSA_READ_H */
