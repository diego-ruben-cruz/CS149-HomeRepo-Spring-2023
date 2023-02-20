/**
 * Description:
 * Write a program that reads an integer, a list of words, and a character.
 * The integer signifies how many words are in the list.
 * The output of the program is every word in the list that
 * contains the character at least once.
 * For coding simplicity, follow each output word by a comma,
 * even the last one. Add a newline to the end of the last output.
 * Assume at least one word in the list will contain the given character.
 * Assume that the list will always contain less than 20 words.
 * Each word will always contain less than 10 characters and no spaces.
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
#include <string.h>

int main(void)
{
    int numWordsEntered;
    char searchChar;
    char inputString[200];
    char wordParse[20][10];

    // Prompt to collect number of words entered
    printf("Please enter how many words you will type: ");
    scanf("%d", &numWordsEntered);

    // Prompt to collect the words to be searched
    printf("Please enter the words you wish to search through: ");
    scanf("%s", &inputString);

    // Prompt to enter character to search for
    printf("Please enter the character you would like to search for: ");
    scanf("%c", &searchChar);

    // Block to parse the words from the string into array of strings
    int i, j, counter;
    j = 0;
    counter = 0;
    for (i = 0; i <= (strlen(inputString)); i++)
    {
        if (inputString[i] == ' ' || inputString[i] == '\0')
        {
            wordParse[counter][j] = '\0';
            counter++;
            j = 0;
        }
        else
        {
            wordParse[counter][j] = inputString[i];
            j++;
        }
    }

    // Block to iterate through array of strings,
    // and print out any that have the search char in them
    for (i = 0; i < numWordsEntered; i++)
    {
        if (strchr(wordParse[i], searchChar) != NULL)
        {
            printf("%s, ", wordParse[i]);
        }
    }

    return 0;
}
