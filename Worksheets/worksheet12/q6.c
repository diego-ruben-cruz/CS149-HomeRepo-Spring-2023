/**
 * Write a program that allocates an array of integers like Q5,
 * frees them, and then tries to print the value of one of the elements of the array
 *
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
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *data = malloc(100 * sizeof(int));
    free(data);

    printf("Attempting to print data[100] after free(): %d\n", data[100]);
}