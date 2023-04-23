/**
 * Write a program that creates an array of integers called data of size 100 using malloc
 * Then set data[100] to 0
 *
 * Responses are below main()
 * What happens when you run this program?
 * What happens when you run this program using valgrind?
 * Is the program correct?
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
 * gcc -o q5 q5.c -Wall -W
 * 
 * To check for memleaks during execution
 * valgrind --leak-check=full ./q5
 * 
 * To run:
 * ./q5
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *data = malloc(100*sizeof(int));
    data[100] = 0;
    
    printf("data[100] => %d\n", data[100]);

    //free(data); // Was not specified in question, not included when executed
}

/**
 * What happens when you run this program?
 * 
 * It compiles without any problems when using gcc.
 * 
 * When it is run, it produces the following output:
 * data[100] => 0
*/

/**
 * What happens when you run this program using Valgrind?
 * 
 * When run using Valgrind, it outlines that there are 400 bytes in use at exit.
 * Valgrind also outlines that there were two mem allocs but only one free.
 * This means that the 400 total bytes allocated are lost because they were not freed
 * at the end of the program.
*/

/** 
 * Is the program correct?
 * 
 * No, the program is not correct, it requires a free(data) to be considered verified
 * against high-quality software standards.
*/