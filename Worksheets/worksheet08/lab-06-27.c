/**
 * Write a program whose input is a character and a string, and whose output indicates the number of times the character appears in the string.
 * The output should include the input character and use the plural form, n's, if the number of times the characters appears is not exactly 1.
 * Assume that the string does not contain spaces and will always contain less than 50 characters.
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 03/27/2023
 * Creation Date: 03/26/2023
 */
#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 50

/**
 * Determines the number of occurrences of a single character within a single string
 *
 * @param   userString  The string that will be searched
 * @param   userChar    The reference char value to search for
 */
int CalcNumCharacters(char *userString, char userChar)
{
    if (strchr(userString, userChar) == NULL) // Shortcut in case there are no occurrences to avoid iterating thru loop
    {
        return 0;
    }
    else
    {
        int count = 0;                       // utility int value to return the count value, initialized to 0 to avoid errors.
        for (int i = 0; i < MAX_LENGTH; i++) // Loop designed to iterate thru string to count number of occurrences of same character
        {
            if (userString[i] == userChar) // Comparison occurs on the grounds of having the same ASCII value
            {
                count++; // Count just gets incremented, nothing groundbreaking here
            }
        }
        return count;
    }
}

int main(void)
{
    // input storage vars for char and string to search thru
    char inputChar;
    char line[MAX_LENGTH];

    // Prompt to collect reference char value
    printf("Please enter a character you would like to search for: ");
    scanf("%c", &inputChar);

    // Prompt to collect string to search thru
    printf("Please enter a brief string of less than 50 characters: ");
    scanf("%s", &line);

    // Main operations are carried out here
    int outputNum = CalcNumCharacters(line, inputChar); // Refer to CalcNumCharacters function
    if (outputNum == 1)                                 // Special formatting if the output of the above function is 1
    {
        printf("There is 1 %c", inputChar);
    }
    else // Every other output possibility
    {
        printf("There are %d %c's", outputNum, inputChar);
    }

    return 0;
}