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
    int i = 0; // Basic integer to iterate thru each character of the string until the reverse binary algo is done
    while (integerValue > 0)
    {
        binaryValue[i] = (integerValue % 2) + '0'; // Adding '0' will convert the int digit into a char, essentially adds 48 to the int
        integerValue = integerValue / 2;           // Next step of reverse binary algorithm to update int value
        i++;                                       // Refer to above comment when i is declared
    }
}

void stringReverse(char inputString[], char reversedString[])
{
    int actualStringSize = 0;                     // Fetches the true size of the string until the null char is reached
    while (inputString[actualStringSize] != '\0') // This is a loop that iterates thru the string as per above line
    {
        actualStringSize++;
    }

    int j = 0; // Basic integer to iterate thru each character of string until string-reverse algo is done
    for (int i = actualStringSize - 1; i >= 0; i--)
    {
        reversedString[j] = inputString[i]; // Fetches end char of input string, puts it in adjacent char of reverse string
        j++;                                // Refer to above comment when j is declared
    }
}

int main(void)
{

    int inputNum;           // Basic int var to store user input
    char reverseBinary[32]; // Reference array to store reverse binary
    char outputBinary[32];  // Reference array to store output binary
    // DC Note - Why does 32 work, and not 33 to account for buffer null char from 2/4 byte usage that comes with an int?

    // User prompt to collect the integer that is to be converted
    printf("Please enter an integer to convert to binary: ");
    scanf("%d", &inputNum);

    // Basic backend ops to prepare output, refer to functions defined above
    intToReverseBinary(inputNum, reverseBinary);
    stringReverse(reverseBinary, outputBinary);

    // Outputs the final converted binary
    printf("\nHere is your input converted to binary: %s", outputBinary);

    return 0;
}
