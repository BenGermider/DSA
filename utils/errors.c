#include <stdio.h>
#include <stdlib.h>
#include "../linked_list/node.h"
#include "../linked_list/list.h"

void node_allocation(Node* newNode){
    if(newNode == NULL){
        printf("[ERROR] Failed to allocate memory for the node, exiting.\n");
        exit(1);
    }
}

void heap_underflow(List* list){
    if(list->head == NULL){
        printf("[ERROR] Encountered heap underflow, exiting.\n");
        exit(1);
    }
}

int invalid_command(){
    printf("[ERROR] Received an invalid command, try again!\n");
    return 1;
}

