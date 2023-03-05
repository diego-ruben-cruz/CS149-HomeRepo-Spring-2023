/**
 * Description:
 * Write a program that can intake a positive integer as an input
 * and output a string of 1's and 0's representing the integer in binary
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
 * Last Modified: 03/06/2023
 * Creation Date: 03/04/2023
 */
#include <stdio.h>

void intToReverseBinary(int integerValue, char binaryValue[])
{
    int i = 0;
    while (integerValue > 0)
    {
        binaryValue[i] = (integerValue % 2) + '0'; // Adding 48 will convert the int digit into a char
        integerValue = integerValue / 2;
        i++;
    }
}

void stringReverse(char inputString[], char reversedString[])
{
    int actualStringSize = 0;
    while (inputString[actualStringSize] != '\0')
    {
        actualStringSize++;
    }

    int j = 0;
    for (int i = actualStringSize - 1; i > 0; i--)
    {
        reversedString[j] = inputString[i];
        j++;
    }
}

int main(void)
{

    int inputNum;
    char reverseBinary[33];
    char outputBinary[33];

    printf("Please enter an integer to convert to binary: ");
    scanf("%d", &inputNum);
    intToReverseBinary(inputNum, reverseBinary);
    stringReverse(reverseBinary, outputBinary);

    printf("\nHere is your input converted to binary: %s", outputBinary);

    return 0;
}
