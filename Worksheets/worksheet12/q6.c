/**
 * Write a program that allocates an array of integers like Q5,
 * frees them, and then tries to print the value of one of the elements of the array
 *
 * Responses are below main()
 * Does the program run?
 * What happens when you use valgrind on it?
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 04/24/2023
 * Creation Date: 04/22/2023
 * To compile with warnings and errors
 * gcc -o q6 q6.c -Wall -W
 * 
 * To check for memleaks during execution
 * valgrind --leak-check=full ./q6
 * 
 * To run:
 * ./q6
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *data = malloc(100 * sizeof(int));
    free(data);

    printf("Attempting to print data[100] after free(): %d\n", data[100]);
}

/**
 * Does the program run?
 * 
 * Yes, the program compiles under gcc and produces the following output:
 * Attempting to print data[100] after free(): 0
*/

/**
 * What happens when you use Valgrind on it?
 * 
 * Valgrind throws an error relating to invalid mem access and attempts to explain what happened.
 * Valgrind throws one error for an invalid read of 4 bytes,
 * another for an address becoming 0 bytes after it was freed,
 * and one more for an allocation
 * 
 * Valgrind essentially describes that the pointer becomes NULL or 0 after data was freed.
*/