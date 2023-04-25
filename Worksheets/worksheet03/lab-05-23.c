/**
 * Description:
 * Write a program that reads a list of integers, and outputs the two smallest integers
 * in the list, in ascending order.
 * The input begins with an integer indicating the number of integers that follow.
 * You can assume that the list will have at least 2 integers and less than 20 integers.
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
 * Creation Date: 2/19/2023
 */
#include <stdio.h>

int main(void)
{
    // Local variables for sorting out
    int arrSize;
    int userValues[20];
    int localMin;
    int runnerUp;

    // Prompt for entering in how many numbers to expect for analysis
    printf("Please enter the amount of numbers you would like to analyze: ");
    scanf("%d", &arrSize);

    // For loop that inserts values into the pre-baked array
    for (int i = 0; i < arrSize; i++)
    {
        scanf("%d", &userValues[i]);
    }

    // For loop that gets the local minimum, given the numbers in the array
    for (int i = 1; i < arrSize; i++)
    {
        if (userValues[i] < userValues[i - 1])
        {
            localMin = userValues[i];
        }
    }

    // For loop that gets the runner up by having it satisfy being greater than local min
    // AND being the lowest number amongst the rest
    for (int i = 1; i < arrSize; i++)
    {
        if (userValues[i] > localMin && userValues[i] < userValues[i - 1])
        {
            runnerUp = userValues[i];
        }
    }

    // Final print statement to output two smallest numbers in the list
    printf("\nThe lowest values are %d and %d.", localMin, runnerUp);

    return 0;
}
