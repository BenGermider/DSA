#include "../linked_list/node.h"
#include "../linked_list/list.h"

#ifndef DSA_ERRORS_H
#define DSA_ERRORS_H

void node_allocation(Node* newNode);

void heap_underflow(List* list);

int invalid_command();

#endif //DSA_ERRORS_H
