/**
 * Description:
 * Create a program that is capable of outputting the following,
 * provided that the user inputs different integers.
 *
 * Enter integer: 4 (user-defined input)
 * You entered: 4
 * 4 squared is 16
 * And 4 cubed is 64!!
 * Enter another integer: 5 (user defined input)
 * 4 + 5 is 9
 * 4 * 5 is 20
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 31 Jan 2023
 * Creation Date: 29 Jan 2023
 */
#include <stdio.h>

int main(void)
{
    // Basic int variables to store user input
    int inputNum1;
    int inputNum2;

    // Prompts user to enter any integer
    printf("Please enter an integer: ");
    scanf("%d", &inputNum1); // %d is a formatting tool to accept num input as string
                             // &inputNum1 contains storage reference to mem address of variable
                             // Think [variable] from x86 MASM

    // Reviews user input and does some computations with them.
    printf("\nYou entered: %d\n", inputNum1);
    printf("%d squared is %d\n", inputNum1, inputNum1 * inputNum1);                  // squares the number
    printf("And %d cubed is %d!!!\n", inputNum1, inputNum1 * inputNum1 * inputNum1); // cubes the number

    // Another prompt for user to enter integer
    printf("Please enter another integer: ");
    scanf("%d", &inputNum2);

    // Reviews second input and does some computations using both input variables
    printf("\n%d + %d is %d\n", inputNum1, inputNum2, inputNum1 + inputNum2); // adds both vars
    printf("%d * %d is %d\n", inputNum1, inputNum2, inputNum1 * inputNum2);   // multiplies both vars

    return 0; // C convention to end a program, mostly seen in Java/C/C++/C#
}