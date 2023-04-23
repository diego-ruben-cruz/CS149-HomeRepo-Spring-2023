/**
 * Write a simple program that allocates memory using malloc()
 * but forgets to free it before exiting.
 *
 * Responses are below main()
 * What happens when this program runs?
 * Can you use gdb to find any problems with it? (skip this step)
 * How about Valgrind?
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
 * 
 * To compile with warnings and errors
 * gcc -o q4 q4.c -Wall -W
 * 
 * To check for memleaks during execution
 * valgrind --leak-check=full ./q4
 * 
 * To run:
 * ./q4
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *example = malloc(sizeof(int)); // Basic malloc for int variable, no free.
    *example = 1337;
    printf("Example int value: %d\n", *example);
    printf("Expect no free after this point...\n");
    // free(example); // Was not specified in question, not included when executed
}
/**
 * What happens when this program runs?
 * 
 * The program compiles and runs with the following output:
 * Example int value: 1337
 * Expect no free after this point...
*/

/**
 * Can you use Valgrind to find any problems with it?
 * 
 * Valgrind can be used to find the problem.
 * It outlines that there are 4 bytes in use at exit, with 2 mem allocs having taken place.
 * There is only 1 free that takes place, and 4 bytes total are lost as memleak. 
*/