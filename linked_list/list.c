#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "node.h"
#include "list.h"
#include "../utils/errors.h"

/**
 * Creates a new empty heap (List structure).
 * @return Pointer to the newly created heap (List structure).
 */
List* make_heap(List* list) {

    if(list != NULL){
        free(list);
    }
    List* heap = (List*)malloc(sizeof(List));
    if (heap != NULL) {
        heap->head = NULL;
        heap->tail = NULL;
        heap->min = 0; heap->max = 0;
    }
    return heap;
}


/**
 * Retrieves the node at the specified index in the linked list.
 * @param head - Head of the linked list.
 * @param index - Index position of the node to retrieve.
 * @return Node at the specified index, or NULL if index is out of bounds.
 */
Node* get_node_at(Node* head, int index) {
    Node* current = head;
    for (int i = 0; i < index; i++) {
        if (current == NULL) return NULL;
        current = current->next;
    }
    return current;
}

/**
 * Retrieves the parent node of a given node in the linked list (assuming min-heap).
 * @param head - Head of the linked list.
 * @param node - Node whose parent is to be found.
 * @return Parent node of the given node, or NULL if the node is the root or not found.
 */
Node* get_parent(Node* head, Node* node) {
    int index = 0;
    Node* current = head;
    while (current != NULL) {
        if (current == node) break;
        current = current->next;
        index++;
    }
    if (index == 0) return NULL; // Root node has no parent
    return get_node_at(head, (index - 1) / 2);
}

/**
 * Retrieves the left child node of a given node in the linked list (assuming min-heap).
 * @param head - Head of the linked list.
 * @param node - Node whose left child is to be found.
 * @return Left child node of the given node, or NULL if no left child exists.
 */
Node* get_left_child(Node* head, Node* node) {
    int index = 0;
    Node* current = head;
    while (current != NULL) {
        if (current == node) break;
        current = current->next;
        index++;
    }
    return get_node_at(head, 2 * index + 1);
}

/**
 * Retrieves the right child node of a given node in the linked list (assuming min-heap).
 * @param head - Head of the linked list.
 * @param node - Node whose right child is to be found.
 * @return Right child node of the given node, or NULL if no right child exists.
 */
Node* get_right_child(Node* head, Node* node) {
    int index = 0;
    Node* current = head;
    while (current != NULL) {
        if (current == node) break;
        current = current->next;
        index++;
    }
    return get_node_at(head, 2 * index + 2);
}

/**
 * Adjusts the heap to maintain the min-heap property starting from a node.
 * @param head - Head of the linked list representing the heap.
 * @param node - Node from which to start heapifying.
 */
void min_heapify(Node* head, Node* node) {
    if (node == NULL) return;

    Node* smallest = node;
    Node* left = get_left_child(head, node);
    Node* right = get_right_child(head, node);

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

/**
 * Internal function to insert a new node into the heap (used for sorted insertion).
 * @param list - Heap represented as a linked list.
 * @param new_data - Data to insert into the heap.
 * @return 0 on success, or appropriate error code on failure.
 */
int _insert(List* list, int new_data){
    Node* new_node = createNode(new_data);
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        list->min = new_data;
        list->max = new_data;
        list->size = 1;
    } else {
        if(list->max > new_data){
            printf("[ERROR] New int is not sorted, exiting\n");
            exit(1);
        }
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
        list->max = new_data;
        list->size++;
    }
    return 0;
}

/**
 * Inserts a new node into the heap (optionally maintaining heap property).
 * @param list - Heap represented as a linked list.
 * @param new_data - Data to insert into the heap.
 * @param is_sorted - Flag indicating whether the list is already sorted (0 or 1).
 * @return 0 on success, or appropriate error code on failure.
 */
int insert(List* list, int new_data, int is_sorted) {
    printf("[INSERT] %d\n", new_data);
    Node* new_node = createNode(new_data);
    if(is_sorted){
        return _insert(list, new_data);
    }
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        list->size = 1;
        list->min = INT_MIN;
        list->max = INT_MAX;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
        Node* current = new_node;
        Node* parent = get_parent(list->head, current);
        while (parent != NULL && parent->data > current->data) {
            int temp = parent->data;
            parent->data = current->data;
            current->data = temp;
            current = parent;
            parent = get_parent(list->head, current);
        }
        list->size++;
    }
    return 0;
}

/**
 * Removes a node from the heap.
 * @param list - Heap represented as a linked list.
 * @param node - Node to be removed.
 * @return Data of the removed node.
 */
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

/**
 * Prints the elements of the heap (linked list representation).
 * @param list - Heap represented as a linked list.
 * @return 0 on success, or appropriate error code on failure.
 */
int print_list(List* list) {
    printf("\nHeap:\n");
    Node* head = list->head;
    if(head == NULL){
        printf("Heap is empty\n");
    }
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
    return 0;
}

/**
 * Retrieves the minimum value of the heap.
 * @param list - Heap represented as a linked list.
 * @return Minimum value of the heap.
 */
int minimum(List* list){
    heap_underflow(list);
    printf("[MINIMUM] %d\n", list->head->data);
    return list->head->data;
}

/**
 * Extracts and returns the minimum value from the heap.
 * @param list - Heap represented as a linked list.
 * @return Minimum value extracted from the heap.
 */
int extract_min(List* list){
    int min;
    heap_underflow(list);
    min = pop_node(list, list->head);
    min_heapify(list->head, list->tail);
    printf("[EXTRACT MIN] %d\n", min);
    return min;
}

/**
 * Removes duplicate nodes from a linked list (assumed to be a heap).
 * @param head - Head of the linked list.
 */
void remove_duplicates(Node* head) {
    if (head == NULL) return;

    // Size of the hash set (adjust based on the range of possible values)
    int cache_size = 10000; // Assuming values range from 0 to 9999
    bool* cache = (bool*)malloc(cache_size * sizeof(bool));
    for (int i = 0; i < cache_size; ++i) {
        cache[i] = false; // Initialize hash set as false (not cached)
    }

    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        int data = current->data;

        if (data >= 0 && data < cache_size && cache[data]) {
            // Duplicate found, remove the node
            prev->next = current->next;
            free(current);
            current = prev->next; // Move current to the next node
        } else {
            // Mark the value as cached
            if (data >= 0 && data < cache_size) {
                cache[data] = true;
            }
            prev = current;
            current = current->next;
        }
    }

    free(cache); // Free dynamically allocated hash set memory
}

/**
 * Merges two heaps represented as linked lists.
 * @param list1 - First heap (linked list).
 * @param list2 - Second heap (linked list).
 * @param is_sorted - Flag indicating whether the heaps are already sorted.
 * @return 0 on success, or appropriate error code on failure.
 */
int union_heap(List* list1, List* list2, int is_sorted) {
    printf("[UNION CALLED]\n");

    if (list1 == NULL || list2 == NULL) {
        printf("Error: One or both lists are NULL\n");
        return 1;
    }

    if (list1->head == NULL && list2->head == NULL) {
        printf("Both heaps are empty\n");
        return 1;
    }

    if (list1->head == NULL) {
        list1->head = list2->head;
    } else if (list2->head != NULL) {
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
    }

    if (list2->head != NULL) {
        list1->tail = list2->tail;
    }

    if (is_sorted) {
        list1->max = (list1->max > list2->max) ? list1->max : list2->max;
        list1->min = (list1->min < list2->min) ? list1->min : list2->min;
    }

    list1->size += list2->size;

    remove_duplicates(list1->head);

    Node* helper = list1->head;
    for (int i = 0; i < list1->size / 2; i++) {
        helper = helper->next;
    }

    for (int i = list1->size / 2; i >= 0; i--) {
        min_heapify(list1->head, helper);
        helper = helper->prev;
    }

    make_heap(list2);

    return 0;
}

/**
 * Implemented a heap-sort on the heap.
 * @param list - heap to sort
 * @return 0 if succeeded, 1 otherwise.
 */
int heap_sort(List* list) {
    printf("[SORT]\n");
    Node* current = list->head;
    if(current == NULL){
        printf("Empty heap.\n");
        return 1;
    }
    while (current != NULL) {
        min_heapify(list->head, current);
        current = current->next;
    }

    // Extract elements from heap one by one
    Node* sorted_list = NULL;
    Node* last_sorted = NULL;
    while (list->head != NULL) {
        // Move current root to end of sorted list
        Node* temp = list->head;
        list->head = (list->head)->next;

        // Insert current root at the end of sorted list
        if (sorted_list == NULL) {
            sorted_list = temp;
            last_sorted = temp;
            sorted_list->next = NULL;
        } else {
            last_sorted->next = temp;
            last_sorted = temp;
            last_sorted->next = NULL;
        }

        // Heapify the reduced heap
        if (list->head != NULL)
            min_heapify(list->head, list->head);
    }

    // Update head pointer to the beginning of sorted list
    list->head = sorted_list;
    return 0;
}