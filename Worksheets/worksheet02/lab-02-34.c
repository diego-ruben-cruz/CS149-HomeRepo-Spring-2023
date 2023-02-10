/**
 * Description:
 * Write a program that takes a first name as the input,
 * and outputs a welcome message to that name.
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 2/09/2023
 * Creation Date: 2/09/2023
 */
#include <stdio.h>

int main(void)
{
    // Basic variable to store username input
    char userName[50];

    // Prompt to take username to do further operations.
    printf("Please enter your name: ");
    scanf("%s", userName);

    // Prints out greeting message for the user
    printf("\nHello %s, and welcome to CS Online!", userName);

    return 0; // Basic exit code for the program since nothing
              // gets output from main operation
}