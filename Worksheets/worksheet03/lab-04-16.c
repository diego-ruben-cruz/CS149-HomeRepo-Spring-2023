/**
 * Description:
 * Write a program that takes any number of non-negative integers as input,
 * and outputs the max and average.
 * A negative integer ends the input and is not included in the statistics.
 * Assume the input contains at least one non-negative integer.
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
    int userValues[20]; // Hard-coded to 20, for purposes of this exercise
    int arrSize = 0;
    double computedAverage;
    int localMax;
    int inputValue = 0;

    printf("Please enter the values that you would like to statistically analyze, followed by a negative number to end the input:\n");
    while (inputValue >= 0)
    {
        scanf("%d", &inputValue);
        if (inputValue < 0)
        {
            break;
        }
        else
        {
            userValues[arrSize] = inputValue;
            arrSize++;
        }
    }

    // // block can be commented out, the following are debugging lines
    // printf("\nNumber of elements entered: %d", arrSize);
    // printf("\nHere are the computations that were done for your input:\n");
    // printf("computed average starting value: %0.2lf\n", computedAverage);

    for (int i = 0; i < arrSize; i++)
    {
        computedAverage += userValues[i];
        // printf("Computed Average per step: %0.2lf\n", computedAverage); // debugging line
    }

    computedAverage = computedAverage / arrSize;
    printf("Average: %0.2lf\n", computedAverage);

    for (int i = 1; i < arrSize; i++)
    {
        if (userValues[i] > userValues[i - 1])
        {
            localMax = userValues[i];
        }
    }
    printf("Maximum Value: %d\n", localMax);

    return 0;
}