/**
 * Description:
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 03/13/2023
 * Creation Date: 03/10/2023
 */

#include <stdio.h>
#define MAX_INPUT_SIZE 20

/**
 * Utility swap operation for sortArray()
 */
void swap(int *x, int *y)
{
    int tempStore = *x; // Utility var to hold one location while the other gets placed into it
    *x = *y;            // Basic swap where y is sent to x
    *y = tempStore;     // then x is sent to y
}

/**
 * Bubble sort implementation to sort an array of defined length
 *
 * Adheres to maximum length of 20 by forcing confines of user-defined length
 */
void sortArray(int sortingList[], int numVals)
{
    for (int i = 0; i < numVals - 1; i++)
    {
        for (int j = 0; j < numVals - i - 1; j++)
        {
            if (sortingList[j] < sortingList[j + 1])
            {
                swap(&sortingList[j], &sortingList[j + 1]);
            }
        }
    }
}

/**
 * Main operation to execute the program
 *
 */
int main(void)
{
    int inputStorage[MAX_INPUT_SIZE]; // Basic array to store the input ints
    int defArraySize;                 // Int var to measure how many integers to sort

    // Prompt to collect the number of ints we expect to sort
    printf("Please enter how many integers you would like to sort: ");
    scanf("%d", &defArraySize);

    // Collect actual input for later sorting
    printf("Please enter %d integer(s):\n", defArraySize);
    for (int i = 0; i < defArraySize; i++)
    {
        int userValue;
        scanf("%d", &userValue);
        inputStorage[i] = userValue;
    }

    // Uses basic BubbleSort implementation, refer to function above
    sortArray(inputStorage, defArraySize);

    // Basic loop to print contents of the array
    printf("Here is the sorted list of integers: ");
    for (int i = 0; i < defArraySize; i++)
    {
        printf("%d, ", inputStorage[i]);
    }
    printf("\n"); // Additional newline for cleanup purposes

    return 0;
}