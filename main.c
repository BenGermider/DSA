#include <stdio.h>
#include "linked_list/list.h"
#include "linked_list/node.h"

int main(){
    List* list = make_heap();
    insert(list, 7);
    insert(list, 500);
    insert(list, 23);
    insert(list, 9);
    insert(list, 66);
    insert(list, 145);
    insert(list, 13);
    insert(list, 212);

    print_list(list->head);
    printf("[MINIMUM]: %d\n", minimum(list));
};