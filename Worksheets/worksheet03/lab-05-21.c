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
   // Code block for initial int prompt
   int numWordsEntered;
   printf("Please enter the number of words you are about to type: ");
   scanf("%d", &numWordsEntered);

   // Code block for taking in the string and parsing out the words input
   char wordParse[20][10];
   for (int i = 0; i < numWordsEntered; i++)
   {
      scanf("%s", wordParse[i]);
   }

   // Code block for character search prompt
   printf("Please enter the character you are searching for: ");
   char searchCharacter;
   scanf(" %c", &searchCharacter);

   // Code block for searching thru the array to output the words that contain search character
   printf("Here are the results of the search: ");
   for (int i = 0; i < numWordsEntered; i++)
   {
      if (strchr(wordParse[i], searchCharacter) != NULL)
      {
         printf("%s,", wordParse[i]);
      }
   }
   printf("\n"); // Basic newline op for cleanup purposes

   return 0;
}
