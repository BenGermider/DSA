# MMN 13

* הגשה מאוחרת כחלק מזכאות לכוחות הביטחון. תודה על ההזדמנות!

### Coding Exercise

The program implements two merge-able heaps.

By executing the program, an instruction message will be printed to the screen.
First of all the user will be asked to choose if he inserts lists in sort order or not.
Then, the executable functions are shown to the user and the way to use them. Using the function
differently will cause a print of an error.

To insert numbers to the heap, the user will be asked to type insert {{ number of heap }} 
{{ number }}.

### Explanations and time complexities:

1) The heap is stored in a linked-list. A new value is added to the heap in the following order:
If the user said the heap he's giving the program is sorted, then the heap just add the value to the end of the list.
The program runs in O(1) - goes to tail and adds there a value.
If the user said the heap is not necessarily sorted, then the value added to the end of the linked-list and then,
min-heapify is executed until the new node gets to its right place.
The program runs in O(n) - Adds to the end of the list and runs min_heapify which runs in O(n) because it runs in the
linked list, so no indexing here is possible.

2) Minimum returns the value of the first node. 
Runs in O(1) - Returns the value of the head of the list.

3) Extract-min returns the value of the first node and pops it out of the heap. Then, runs moves the tail to the head and
runs min_heapify.
Runs in O(n) - Pops the first value (O(1)) and then runs min_heapify on what was the last leaf, which run in O(n).

4) Make heap - Clears the list the user wanted.
Runs in O(1) - Gets the list and frees it.

5) Union heap - Unions the two heaps. After that, it runs min-heapify on the non-leafs nodes. Function runs in
O(n^2) - Runs min-heapify of O(n) on the non-leafs of the heap.

6) Heap sort - Receives a heap and sorts it with heap sort. The function runs in O(nlgn) because it receives a heap
and runs min_heapify on the relevant nodes (which concludes to be lgn).


To stop the program, the user is asked to type "stop".

The heaps are printable during the entire run. The user just has to type print {{ number of heap }}.




