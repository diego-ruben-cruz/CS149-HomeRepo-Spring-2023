/**
 * Description:
 * Write a program that reads a list of integers, and outputs those integers in reverse.
 *
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
        // Will take user input based on first number and add to the array in reverse order
        int value;
        scanf("%d", &value);
        userVals[defArraySize - 1 - i] = value; // Places elements from the list into the array in reverse order
        /**
         * Theory behind the line:
         *
         * Suppose we have our defined array size variable used as a place holder
         * defArraySize = 4
         *
         * We then input the following 4 values: 3 4 5 6
         *
         * For each value, this is what occurs
         * 3    =>  userVals[4 - 1 - i] =>  userVals[4 - 1 - 0] = 3 =>  userVals[3] = 3
         * 4    =>  userVals[4 - 1 - i] =>  userVals[4 - 1 - 1] = 4 =>  userVals[2] = 3
         * 5    =>  userVals[4 - 1 - i] =>  userVals[4 - 1 - 2] = 5 =>  userVals[1] = 3
         * 6    =>  userVals[4 - 1 - i] =>  userVals[4 - 1 - 3] = 6 =>  userVals[0] = 3
         */
    }

    // Prints out each element of the array in a proper sequence, since the sorting was already done on insertion.
    for (int i = 0; i < defArraySize; i++)
    { // print array in reverse
        printf("%d,", userVals[i]);
    }
    return 0;
}