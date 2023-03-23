/**
 * Description:
 * Write a program that first gets a list of integers from input.
 * The input begins with an integer indicating the number of integers that follow
 * That list is followed by two more integers representing lower and upper bounds of a range.
 * Your program should output all integers from the list that are within that range (inclusive of the bounds).
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 2/20/2023
 * Creation Date: 2/16/2023
 */
#include <stdio.h>
#define NUM_ELEMENTS 20

int main()
{
    int userVals[NUM_ELEMENTS]; // Array to hold the user's input integers

    int defArraySize; // Variable that stores the total numbers that will be input into the console
    int lowerBound;   // Variable that stores the lower bound for the inclusive search
    int upperBound;   // Variable that stores the upper bound for the inclusive search

    // Prompt to enter in the defined array size from user input
    printf("Input starting integer less than 20: ");
    scanf("%d", &defArraySize); // starting integer, specifies array size

    // Prompt to enter in lower bound inclusive search parameter
    printf("Input lower bound for inclusive search: ");
    scanf("%d", &lowerBound);

    // Prompt to enter in upper bound inclusive search parameter
    printf("Input upper bound for inclusive search: ");
    scanf("%d", &upperBound);

    // Prompt to enter in the different values to be inserted into the array
    printf("Enter %d integer values...\n", defArraySize);
    for (int i = 0; i < defArraySize; i++)
    {
        // Will take user input based on first number and add to the array as it comes in.
        int value;
        scanf("%d", &value);
        userVals[i] = value;
    }

    // Traverses through the array
    for (int i = 0; i < defArraySize; i++)
    {
        int value = userVals[i];
        if (value >= lowerBound && value <= upperBound)
        {
            printf("%d,", value);
        }
    }

    return 0;
}