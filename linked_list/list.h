#ifndef DSA_LIST_H
#define DSA_LIST_H
#include "node.h"

typedef struct {
    Node* head;
    Node* tail;
    size_t size;
    int min;
    int max;
} List;


/**
 * Build a heap out of a LinkedList.
 */
List* make_heap(List* list);

/**
 * Insert a new node to the heap.
 * @param value value of new node.
 */
int insert(List* list, int value, int is_sorted);

/**
 * Adjusts the heap to maintain the min-heap property starting from a node.
 * @param head - Head of the linked list representing the heap.
 * @param node - Node from which to start heapifying.
 */
void min_heapify(Node* head, Node* node);

/**
 * Inserts a new node to a sorted array.
 * @param list the list to add to.
 * @param node the new node to be added to the array.
 */
int _insert(List* list, int new_data);

/**
 * @return the minimum value of the heap.
 */
int minimum(List* list);

/**
 * Extracts the minimum value from the heap.
 * @return the minimum value.
 */
int extract_min(List* list);

/**
 * Merges two heaps.
 */
int union_heap(List*, List*, int);  // Union is a

/**
 * Prints as a list.
 * @param node to print from.
 */
int print_list(List* list);

/**
 * Implemented a heap-sort on the heap.
 * @param list - heap to sort
 * @return 0 if succeeded, 1 otherwise.
 */
int heap_sort(List* list);

#endif //DSA_LIST_H
