/**
 * Write a program that creates an array of integers called data of size 100 using malloc
 * Then set data[100] to 0
 *
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
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *data = malloc(100*sizeof(int));
    data[100] = 0;
    
    printf("Data[100] Value: %d\n", data[100]);

    free(data); // Implicitly assumed a free.
}