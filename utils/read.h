#include "../linked_list/list.h"
#include "errors.h"

#ifndef DSA_READ_H
#define DSA_READ_H

typedef struct {
    int num_list;
    List* list;
} ListMapping;

typedef enum {
    FUNC_CLEAR,      // Function type for clearing a list
    FUNC_ZERO_ARG,   // Function type for zero-argument functions
    FUNC_ONE_ARG,    // Function type for single-argument functions
    FUNC_THREE_ARG   // Function type for three-argument functions
} FunctionType;

typedef union {
    List* (*func_clear)(List*);
    int (*func_zero_arg)(List*, List*, int);
    int (*func_one_arg)(List *);
    int (*func_three_arg)(List *, int, int);
} FunctionPointer;

typedef struct {
    const char *name;
    FunctionType type;
    FunctionPointer function;
} FunctionMapping;


/**
 * Trim leading and trailing whitespace characters from a string.
 * Modifies the original string.
 *
 * @param str The string to trim
 */
void trim(char *str);

/**
 * Read a string input from the user, removing newline characters and trimming whitespace.
 *
 * @return Dynamically allocated string containing user input
 */
char* read_string_from_user();

/**
 * Split an input string into two parts based on the first space character found.
 *
 * @param input Input string to split
 * @param part1 Output buffer for the first part of the string
 * @param part2 Output buffer for the second part of the string
 * @param max_len Maximum length for output buffers
 */
void split_string(const char *input, char *part1, char *part2, size_t max_len);

/**
 * Parse and retrieve integer arguments from a string.
 * Returns an array where the first element is the number of arguments parsed,
 * and the second element is the integer value parsed (or INT_MAX if not present).
 *
 * @param args String containing arguments to parse
 * @return Array containing parsed arguments
 */
int* get_args(char* args);

/**
 * Execute a function based on its name and arguments, using a list mapping.
 *
 * @param function_name Name of the function to execute
 * @param args Arguments for the function
 * @param list_map Array mapping lists to their indices
 * @param is_sorted Flag indicating if lists are sorted
 */
void execute_function(const char *function_name, char *args, ListMapping list_map[], int is_sorted);

/**
 * Read user commands continuously, executing corresponding functions until "stop" command is received.
 *
 * @param list1 Pointer to the first list
 * @param list2 Pointer to the second list
 */
void read_from_user(List *list1, List *list2);

#endif /* DSA_READ_H */
