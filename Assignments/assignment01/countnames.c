/**
 * Description:
 * Assume that you have a text file with a name on each line,
 * and names are separated by newlines. Assume each row has one name (keep things simple) and a name can occur
 * many times in the file. Assume you are dealing with up to 100 individual names (since you would need dynamic
 * memory allocation for expanding an array to deal with more names, which we'll see later). You want to read the
 * names in and count the occurrences of each. Since we want to be flexible on the type and size of characters we
 * can handle, you can assume Ascii code and you expect a file to contain simple characters of Ascii values from
 * 0-128. A name can be up to 30 characters long.
 You must be able to handle a file with any number of rows, including no names. It is ok if this is slow
 (since you would need dynamic data structures like hash tables to make it fast, which we'll see later). You can
 assume that the input file contains only valid characters and rows are separated by newlines; the input file may
 contain a few empty lines as well (which you will ignore).
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
 * Creation Date: 2/12/2023
 */
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    // argc and argv are how command line arguments are passed to main(0 in C/C++.
    // Argc will be # of strings pointed to by argv
    // Argv = pointer
    const char *filename = argv[1]; // filename is taken as argument, pointer reference, assume each line max 30 char
    char length[30];
    char names[100][30]; // 100 by 30 2D array        character array

    int counter[100];
    int i = 0;
    int j = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Not able to open the file.");
        return -1;
    }

    for (int i = 0; i < 100; i++)
    {
        counter[i] = -1;
    }

    // removes new line in fgets and copies the name as long if not empty.
    while (fgets(length, 30, file))
    {                                     // fgets reads and includes new line character
        char *ret = strchr(length, '\n'); // searches for first occurence of '\n' to replace with 0
        // can also use  if (buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';
        // https://aticleworld.com/remove-trailing-newline-character-from-fgets/   Links to an external site.
        if (ret)
        {
            *ret = '\0';
        }

        if (strlen(length) != 0)
        { // if the line is not empty copy the pointer and str name to be copied
            strcpy(names[j], length);
            j++;
        }
        else
        {
            fprintf(stderr, "[WARNING] : Line %d is empty\n", j);
        }
    }

    // Need to find method to get unique names and then stop looking for those unique names once they've already been searched
    // Not sure if Strcmp will play nice with the char array we've got, despite the fact that this is how they handle strings in C

    // Updating counter for duplicate names while also removing the duplicates, finally print at end of looping through character array
    for (i = 0; i < j; i++)
    { // loop through lines of names
        int count = 1;
        for (int k = i + 1; k < j; k++)
        {
            if (strcmp(names[i], names[k]) == // check if same line
                0)
            {                   // Native C library function to use Strcmp, returns 0 if the strings are the same
                count++;        // if names are equal/match, count up.
                counter[k] = 0; // reset
            }
        }
        if (counter[i] != 0)
        {
            counter[i] = count; // updating count
        }
    }
    // Print: names + occurences
    for (i = 0; i < j; i++)
    {
        if (counter[i] != 0)
        {
            printf("%s: %d\n", names[i], counter[i]);
        }
    }

    fclose(file);
    return 0;
}