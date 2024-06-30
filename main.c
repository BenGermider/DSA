#include <stdio.h>
#include "linked_list/list.h"
#include "utils/read.h"

int main(){
    List* f_heap = make_heap(NULL);
    List* s_heap = make_heap(NULL);
    read_from_user(f_heap, s_heap);
};