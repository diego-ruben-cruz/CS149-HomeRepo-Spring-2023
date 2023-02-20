/**
 * Description:
 * Given a sorted list of integers, output the middle integer.
 * A negative number indicates the end of the input
 * Assume the number of integers is always odd.
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
    const int NUM_ELEMENTS = 9;
    int userValues[NUM_ELEMENTS]; // Set of data specified by the user
    int inputValue = 0;
    int arrSize = 0;
    int outputValue;

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

    if (arrSize == 3)
    {
        outputValue = userValues[1];
        printf("\nHere is the middle value, of the ones you entered: %d", outputValue);
    }
    else if (arrSize == 5)
    {
        outputValue = userValues[2];
        printf("\nHere is the middle value, of the ones you entered: %d", outputValue);
    }
    else if (arrSize == 7)
    {
        outputValue = userValues[3];
        printf("\nHere is the middle value, of the ones you entered: %d", outputValue);
    }
    else if (arrSize == 9)
    {
        outputValue = userValues[4];
        printf("\nHere is the middle value, of the ones you entered: %d", outputValue);
    }
    else
    {
        printf("\nError, an even number of values were entered");
    }

    return 0;
}
