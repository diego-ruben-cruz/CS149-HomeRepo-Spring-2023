/**
 * Description:
 * Write a program that takes a positive integer as input, then outputs the number as a reverse binary string
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

int main(void)
{
    int inputNum;
    printf("Please input a positive integer: ");
    scanf("%d", &inputNum);

    printf("\nHere is the number in reverse binary: ");
    while (inputNum > 0)
    {
        printf("%d", inputNum % 2);
        inputNum = inputNum / 2;
    }

    return 0;
}