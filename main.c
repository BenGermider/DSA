#include <stdio.h>
#include "linked_list/list.h"

int main(){
    int min;
    List* f_heap = make_heap();
    List* s_heap = make_heap();
    insert(f_heap, 7);
    insert(f_heap, 500);
    insert(f_heap, 23);
    insert(f_heap, 9);
    insert(f_heap, 66);
    insert(f_heap, 145);
    insert(f_heap, 13);
    insert(f_heap, 212);
    min = extract_min(f_heap);
    print_list(f_heap);
    printf("[MINIMUM]: %d\n", min);
};