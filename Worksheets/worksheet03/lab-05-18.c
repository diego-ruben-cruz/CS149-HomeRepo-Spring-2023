/**
 * Description:
 * Write a program that first gets a list of integers from input.
 * The input begins with an integer indicating the number of integers that follow.
 * Then, get the last value from the input, which indicates a threshold.
 * Output all integers less than or equal to that last threshold value.
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

int main()
{
    const int NUM_ELEMENTS = 20; // Number of input integers
    int userVals[NUM_ELEMENTS];  // Array to hold the user's input integers

    int defArraySize; // Variable that stores the total numbers that will be input into the console

    // Prompt to enter in the defined array size from user input
    printf("Input Starting Integer less than 20: ");
    scanf("%d", &defArraySize); // starting integer, specifies array size

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
        if (value < userVals[defArraySize - 1])
        {
            printf("%d,", value);
        }
    }

    return 0;
}