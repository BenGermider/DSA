#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "read.h"
#include "errors.h"

#define MAX_LEN 1024

FunctionMapping function_map[] = {
        {"insert", FUNC_THREE_ARG, .function.func_three_arg = insert},
        {"minimum", FUNC_ONE_ARG,.function.func_one_arg = minimum},
        {"extract-min", FUNC_ONE_ARG,.function.func_one_arg = extract_min},
        {"union", FUNC_ZERO_ARG,.function.func_zero_arg = union_heap},
        {"sort", FUNC_ONE_ARG, .function.func_one_arg = heap_sort},
        {"print", FUNC_ONE_ARG, .function.func_one_arg = print_list},
        {"make-heap", FUNC_CLEAR, .function.func_clear = make_heap},
        {"default", FUNC_ONE_ARG,.function.func_one_arg = invalid_command}
};

/**
 * Trim leading and trailing whitespace characters from a string.
 * Modifies the original string.
 *
 * @param str The string to trim
 */
void trim(char *str) {
    char *start, *end;

    for (start = str; *start && isspace((unsigned char)*start); start++);

    for (end = str + strlen(start) - 1; end >= start && isspace((unsigned char)*end); end--);

    *(end + 1) = '\0';

    if (start > str) {
        memmove(str, start, end - start + 2);
    }
}

/**
 * Read a string input from the user, removing newline characters and trimming whitespace.
 *
 * @return Dynamically allocated string containing user input
 */
char* read_string_from_user(){
    char* buffer = (char*)malloc(MAX_LEN) ;
    printf("Enter a command: ");
    if (fgets(buffer, MAX_LEN, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
    } else {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }
    trim(buffer);
    return buffer;
}

/**
 * Split an input string into two parts based on the first space character found.
 *
 * @param input Input string to split
 * @param part1 Output buffer for the first part of the string
 * @param part2 Output buffer for the second part of the string
 * @param max_len Maximum length for output buffers
 */
void split_string(const char *input, char *part1, char *part2, size_t max_len) {
    const char *space_ptr = strchr(input, ' ');

    if (space_ptr != NULL) {
        size_t pos = space_ptr - input;
        strncpy(part1, input, pos);
        part1[pos] = '\0';
        strncpy(part2, space_ptr + 1, max_len - 1);
        part2[max_len - 1] = '\0';
    } else {
        strcpy(part1, input);
        part1[strlen(input)] = '\0';
        part2 = NULL;
    }
}

/**
 * Parse and retrieve integer arguments from a string.
 * Returns an array where the first element is the number of arguments parsed,
 * and the second element is the integer value parsed (or INT_MAX if not present).
 *
 * @param args String containing arguments to parse
 * @return Array containing parsed arguments
 */
int* get_args(char* args){
    int j = 0, inv_n = 0;
    char* ptr = args;
    char* max_arg = (char*)malloc(5);
    int* args_as_int = (int*)calloc(2, sizeof(int));
    args_as_int[1] = INT_MAX;
    while(*ptr != '\0'){
        if(!isspace(*ptr) && !isdigit(*ptr) && *ptr != '-'){
            args_as_int[0] = -1;
            return args_as_int;
        }
        while(isspace(*ptr)){
            ptr++;
        }
        if(isdigit(*ptr) && args_as_int[0] == 0){
            strncpy(max_arg, ptr, 1);
            max_arg[1] = '\0';
            args_as_int[0] = atoi(max_arg);
            if(args_as_int[0] > 2 || args_as_int[0] < 1){
                args_as_int[0] = -1;
                return args_as_int;
            }
            ptr++;
        }
        else if((*ptr == '-' || isdigit(*ptr)) && args_as_int[0] != 0){
            while(isdigit(*ptr) || *ptr == '-'){
                if(inv_n && *ptr == '-'){
                    args_as_int[0] = -1;
                    return args_as_int;
                }
                if(*ptr == '-'){
                    inv_n = 1;
                }
                max_arg[j++] = *ptr++;
            }
            max_arg[j] = '\0';
            args_as_int[1] = atoi(max_arg);
        }
    }
    return args_as_int;
}

/**
 * Execute a function based on its name and arguments, using a list mapping.
 *
 * @param function_name Name of the function to execute
 * @param args Arguments for the function
 * @param list_map Array mapping lists to their indices
 * @param is_sorted Flag indicating if lists are sorted
 */
void execute_function(const char *function_name, char *args, ListMapping list_map[], int is_sorted) {
    int *i_args;
    i_args = get_args(args);
    if(i_args[0] == -1 && (strcmp(function_name, "union") != 0)) {
        invalid_command();
        free(i_args);
        return;
    }
    List* list = list_map[i_args[0] - 1].list;
    for (int i = 0; i < sizeof(function_map) / sizeof(FunctionMapping); i++) {
        if (strcmp(function_map[i].name, function_name) == 0) {
            switch (function_map[i].type) {
                case FUNC_CLEAR:
                    function_map[i].function.func_clear(list);
                    return;
                case FUNC_ZERO_ARG:
                    function_map[i].function.func_zero_arg(list_map[0].list, list_map[1].list, is_sorted);
                    list_map[1].list = make_heap(NULL);
                    return;
                case FUNC_ONE_ARG:
                    function_map[i].function.func_one_arg(list);
                    return;
                case FUNC_THREE_ARG:
                    if(i_args[1] == INT_MAX){
                        invalid_command();
                        return;
                    }
                    function_map[i].function.func_three_arg(list, i_args[1], is_sorted);
                    return;
            }
        }
    }
    invalid_command();
    free(i_args);
}

/**
 * Read user commands continuously, executing corresponding functions until "stop" command is received.
 *
 * @param list1 Pointer to the first list
 * @param list2 Pointer to the second list
 */
void read_from_user(List* list1, List* list2){
    ListMapping list_map[] = {
            {0, list1},
            {1, list2}
    };
    char *text, *function, *args;
    int is_sorted;

    printf("Hello user, you may now work with mergeable heaps.\nFor now, you have two empty heaps. "
           "You can use the following functions:\n1) Insert - add an integer to a heap. To use, please type insert "
           "{{number of heap (1 or 2)}} {{integer to add}}\n2) Minimum - get the smallest integer from the heap. "
           "To use, please type minimum {{number of heap (1 or 2)}}\n3) Extract-min - get the smallest integer from the"
           " while popping it from the heap. heap. To use, please type extract-min {{number of heap (1 or 2)}}\n"
           "4) Union - Merge the two heaps into one heap. To use, please type union\n5) Sort - sort the desired"
           " heap. To use, please type sort {{number of heap (1 or 2)}}.\n6) Print heap - Print a desired "
           "list. To use, type print {{number of heap (1 or 2)}}\n7) Clear heap - Flushes the given heap. To use,"
           "please type make-heap {{number of heap (1 or 2)}}\n8) Stop - closes the loop. To use,"
           " please type stop.\n\nFirst, are the heaps you are willing to submit are sorted or not? 1 for \n"
           "sorted, 0 otherwise.\n");
    scanf("%d", &is_sorted);
    fflush(stdin);
    if(is_sorted != 0 && is_sorted != 1){
        printf("bad request, terminating.\n");
        exit(1);
    }
    while(1){
        text = read_string_from_user();
        if(strcmp(text, "stop") == 0){
            break;
        }
        args = (char*)malloc(7);
        function = (char*)malloc(MAX_LEN - 7);
        split_string(text, function, args, sizeof(text));
        execute_function(function, args, list_map, is_sorted);
        free(args);
        free(function);
    }
    free(text);
}