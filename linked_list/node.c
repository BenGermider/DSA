#include <stdlib.h>
#include "node.h"
#include "../utils/errors.h"


Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    node_allocation(newNode);
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

