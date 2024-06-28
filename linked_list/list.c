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

int insert(List* list, int new_data) {
    printf("[INSERT] %d\n", new_data);
    Node* new_node = createNode(new_data);
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
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
    return 0;
}


int pop_node(List* list, Node* node){
    Node* ptr;
    int data;
    heap_underflow(list);
    if (node == list->head) {
        data = list->head->data;
        list->head = node->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL; // If the list becomes empty
        }
    }
        // If node to be removed is the tail
    else if (node == list->tail) {
        data = list->tail->data;
        list->tail = node->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        } else {
            list->head = NULL; // If the list becomes empty
        }
    } else {
        ptr = list->head;
        while(ptr != NULL){
            if(ptr == node){
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                data = ptr->data;
                free(ptr);
            }
        }
    }
    return data;
}

int print_list(List* list) {
    printf("\nTraversal in forward direction:\n");
    Node* head = list->head;
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
    return 0;
}

/**
 * @return the minimum value of the heap.
 */
int minimum(List* list){
    heap_underflow(list);
    printf("[MINIMUM] %d\n", list->head->data);
    return list->head->data;
}

/**
 * Extracts the minimum value from the heap.
 * @return the minimum value.
 */
int extract_min(List* list){
    int min;
    heap_underflow(list);
    min = pop_node(list, list->head);
    min_heapify(list->head, list->tail);
    printf("[EXTRACT MIN] %d\n", min);
    return min;
}

void purge_list(List* list){
    Node* node = (list)->head;
    Node* next;
    while(node != NULL){
        next = node->next;
        free(node);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

/**
 * Merges two heaps.
 */
int union_heap(List* list1, List* list2){
    if(list1->head == NULL){
        list1->head = list2->head;
        purge_list(list2);
    }

}



