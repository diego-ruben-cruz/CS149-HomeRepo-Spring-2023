/**
 * Write a simple program that allocates memory using malloc()
 * but forgets to free it before exiting.
 *
 * What happens when this program runs?
 * Can you use gdb to find any problems with it?
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
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *example = malloc(sizeof(int)); // Basic malloc for int variable, no free.
    example = 1337;
    printf("Example int value: %d\n", example);
    printf("Expect no free after this point...");
    // free(example);
}