#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "list.h"
#include "../utils/errors.h"


/**
 * Build a heap out of a LinkedList.
 * @param list - linked list to order as a heap.
 */



List* make_heap() {
    List* heap = (List*)malloc(sizeof(List));
    if (heap != NULL) {
        heap->head = NULL;
    }
    return heap;
}

/**
 * Insert a new node to the heap.
 * @param value value of new node.
 */
//void insert(List* list, int value, char is_sorted){
//    Node* newNode = createNode(value);
//    if(list->head == NULL){
//        list->head = newNode;
//        list->tail = newNode;
//        return;
//    }
//
//
//}
//
//void insert_sorted(List* list, Node* newNode){
//    sort_error(list, newNode);
//    newNode->prev = list->tail;
//    list->tail->next = newNode;
//    list->tail = newNode;
//}
//
//void common_insert(List* list, Node* node){
//
//}


int getSize(List* list) {
    int size = 0;
    Node* current = list->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

Node* getNodeAt(Node* head, int index) {
    Node* current = head;
    for (int i = 0; i < index; i++) {
        if (current == NULL) return NULL;
        current = current->next;
    }
    return current;
}

Node* getParent(Node* head, Node* node) {
    int index = 0;
    Node* current = head;
    while (current != NULL) {
        if (current == node) break;
        current = current->next;
        index++;
    }
    if (index == 0) return NULL;
    return getNodeAt(head, (index - 1) / 2);
}

Node* getLeftChild(Node* head, Node* node) {
    int index = 0;
    Node* current = head;
    while (current != NULL) {
        if (current == node) break;
        current = current->next;
        index++;
    }
    return getNodeAt(head, 2 * index + 1);
}

Node* getRightChild(Node* head, Node* node) {
    int index = 0;
    Node* current = head;
    while (current != NULL) {
        if (current == node) break;
        current = current->next;
        index++;
    }
    return getNodeAt(head, 2 * index + 2);
}

void min_heapify(Node* head, Node* node) {
    if (node == NULL) return;

    Node* smallest = node;
    Node* left = getLeftChild(head, node);
    Node* right = getRightChild(head, node);

    if (left != NULL && left->data < smallest->data) {
        smallest = left;
    }
    if (right != NULL && right->data < smallest->data) {
        smallest = right;
    }

    if (smallest != node) {
        int temp = node->data;
        node->data = smallest->data;
        smallest->data = temp;
        min_heapify(head, smallest);
    }
}

void insert(List* list, int new_data) {
    Node* new_node = createNode(new_data);

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* last = list->head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
        new_node->prev = last;

        Node* current = new_node;
        Node* parent = getParent(list->head, current);
        while (parent != NULL && parent->data > current->data) {
            int temp = parent->data;
            parent->data = current->data;
            current->data = temp;
            current = parent;
            parent = getParent(list->head, current);
        }
    }
}


void print_list(Node* node) {
    printf("\nTraversal in forward direction:\n");
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

/**
 * @return the minimum value of the heap.
 */
int minimum(List* list){
    heap_underflow(list);
    return list->head->data;
}

/**
 * Extracts the minimum value from the heap.
 * @return the minimum value.
 */
int extract_min(List* list){
    heap_underflow(list);

}


/**
 * Merges two heaps.
 */
void union_heap(){

}



