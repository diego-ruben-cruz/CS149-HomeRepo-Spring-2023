/**
 * Description:
 * Write a program that counts all the individual names, provided a txt file as input
 *
 * Assume that you have a text file with a name on each line, and names are separated by newlines.
 * Assume each row has one name (keep things simple) and a name can occur many times in the file.
 * Assume you are dealing with up to 100 individual names
 * You can assume that the input file contains only valid characters and rows are separated by newlines
 *
 * A name can be up to 30 characters long
 * You must be able to handle a file with any number of rows, including no names
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

int main(int argc, char *argv[])
{
    // argc and argv are how command line arguments are passed to main(0 in C/C++.
    // Argc will be # of strings pointed to by argv
    // Argv = pointer
    int counter[100];
    int i;
    int j;
    int k;

    char names[100][30];

    // tentatively added argv since it seems to be a char array anyhow, worth a shot - DC
    FILE *file = fopen(argv, "r");

    // DC Note
    // Brute force loop to traverse through the array looking for a particular name value
    // and add to the counter array, has a flaw in that it will double-count arrays in the file

    // Need to find method to get unique names and then stop looking for those unique names once they've already been searched
    // Not sure if Strcmp will play nice with the char array we've got, despite the fact that this is how they handle strings in C
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        {
            if (Strcmp(names[i], names[j]) == 0) // Native C library function to use Strcmp, returns 0 if the strings are the same
                                                 // Not sure if I want to use formatted strings for clarification to insert the 'proper' string in there or not
                                                 // Requires further testing
            {
                counter[j] = counter[j] + 1; // increments the counter for that one specific name, still flawed, refer to comments above nested loop
            }
        }
    }

    fclose(file); // Closes out file
    return 0;     // Native C function to return, not quite void, not quite
}