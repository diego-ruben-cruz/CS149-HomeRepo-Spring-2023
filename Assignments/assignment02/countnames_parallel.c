/**
 * Description:
 * Assume that you have several text file with a name on each line,
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
 * Last Modified: 03/06/2023
 * Creation Date: 03/04/2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_LENGTH 30 // Constant for length of string including nullchar
#define MAX_LINES 100 // Constant for max number of lines in a given file

int main(int argc, char *argv[])
{
    int fd[2];                         // file descriptor integration
    int lineIndex = 0;                 // main index to keep track of line number
    int counter[MAX_LINES];            // Counter is equivalent to a logical index
    char names[MAX_LINES][MAX_LENGTH]; // Creates 2D array of names listed in each file
    char currentName[MAX_LENGTH];      // Creates a current working array for the current 'read' name

    // If the filedesc isn't prim n proper, it returns a -1 for the error
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failure - check code");
        return 1;
    }

    // This loops for each file, such that a separate process is made for each one
    for (int i = 1; i < argc; i++)
    {
        char currentName[MAX_LENGTH];
        char names[MAX_LINES][MAX_LENGTH];
        int lineIndex = 0;

        int childPID = fork(); // Duplicates number of processes, essentially makes a new one for every files
        if (childPID = 0)
        {
            FILE *file = fopen(argv[i], "r"); // Opens a file from the specified arguments, configured to readonly
            if (!file)                        // Essentially throws an error if the filename does not exist within the directory
            {
                printf("Unable to open specified file\n");
                return -1;
            }

            // removes new line in fgets and copies the name as long if not empty.
            while (fgets(currentName, sizeof(currentName), file))
            {                                          // fgets reads and includes new line character
                char *ret = strchr(currentName, '\n'); // searches for first occurence of '\n' to replace with 0
                // can also use  if (buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';
                // https://aticleworld.com/remove-trailing-newline-character-from-fgets/   Links to an external site.
                if (ret)
                {
                    *ret = '\0';
                }

                if (strlen(currentName) != 0) // if the line is not empty copy the pointer and str name to be copied
                {
                    strcpy(names[lineIndex], currentName);
                    lineIndex++;
                }
                else // Throws error warning if there are empty lines in the file
                {
                    fprintf(stderr, "[WARNING] : Line %d is empty\n", lineIndex);
                }
            }

            fclose(file); // Closes file after all operations said and done

            // Cleanup for file descriptors and writing to pipe
            close(fd[0]);
            write(fd[1], &lineIndex, sizeof(lineIndex));
            write(fd[1], names, sizeof(names));

            exit(0); // Cleanup to prevent child from forking its respective children
        }
        // no error on child pid handling just yet
    }

    while ((wait(NULL)) > 0) // Waits on any child processes to finish running then does the computing of as1
    {
        int readLine;                          // Utility line number
        char readNames[MAX_LINES][MAX_LENGTH]; // readNames array for computing

        // Quick closure and reading from child process pipe
        close(fd[1]);
        read(fd[0], &readLine, sizeof(readLine));
        read(fd[0], readNames, sizeof(names));

        // Copy the child names to the array
        for (int i = 0; i < readLine; i++)
        {
            if (strlen(names[lineIndex]) == 0)
            {
                strcpy(names[lineIndex], readNames[i]);
            }
            else
            {
                i--;
            }
            lineIndex++;
        }

        // count the number of names
        for (int i = 0; i < MAX_LINES; i++)
        {
            counter[i] = -1;
        }

        // Updating counter for duplicate names while also removing the duplicates, finally print at end of looping through character array
        for (int i = 0; i < lineIndex; i++)
        { // loop through lines of names
            int count = 1;
            for (int j = i + 1; j < lineIndex; j++)
            {
                if (strcmp(names[i], names[j]) == // check if same line
                    0)
                {                   // Native C library function to use Strcmp, returns 0 if the strings are the same
                    count++;        // if names are equal/match, count up.
                    counter[j] = 0; // reset
                }
            }
            if (counter[i] != 0)
            {
                counter[i] = count; // updating count
            }
        }
    }

    // Print: names + occurences
    for (int i = 0; i < lineIndex; i++)
    {
        if (counter[i] != 0)
        {
            printf("%s: %d\n", names[i], counter[i]);
        }
    }
}