#ifndef DSA_LIST_H
#define DSA_LIST_H
#include "node.h"

typedef struct {
    Node* head;
    Node* tail;
    int size;
} List;


/**
 * Build a heap out of a LinkedList.
 */
List* make_heap();

/**
 * Insert a new node to the heap.
 * @param value value of new node.
 */
int insert(List* list, int value);


void min_heapify(Node* head, Node* node);


int getSize(List* list);
Node* getNodeAt(Node* head, int index);
Node* getParent(Node* head, Node* node);
Node* getLeftChild(Node* head, Node* node);
Node* getRightChild(Node* head, Node* node);




/**
 * Inserts a new node to a sorted array.
 * @param list the list to add to.
 * @param node the new node to be added to the array.
 */
void insert_sorted(List* list, Node* node);
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
int union_heap();  // Union is a

/**
 * Prints as a list.
 * @param node to print from.
 */
int print_list(List* list);

#endif //DSA_LIST_H
