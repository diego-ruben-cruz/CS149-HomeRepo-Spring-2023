/**
 * Description:
 * You will develop a proc_manager program that executes multiple commands.
 * It reads a command for each execution from stdin on one line of input.
 * So, it reads in the command and its parameters to execute from the stdin
 * (FD0 - file descriptor 0) with each line specifying one command execution.
 *
 * You will execute one command and its parameters as specified on each line of stdin input.
 * The proc_manager program will start up all the processes with the exec command
 * and wait for them to complete, while each command will write its stdout and stderr
 * to log files.
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
 *
 * To compile with warnings and errors
 * gcc -o proc_manager proc_manager.c -Wall -W
 *
 * To execute
 * ./proc_manager.c cmds01.txt cmds02.txt
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

    // If the filedesc isn't prim n proper, it returns a -1 for the error
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failure - check code");
        return 1;
    }

    // This loops for each file, such that a separate process is made for each one
    for (int i = 1; i < argc; i++)
    {
        char currentCMD[MAX_LENGTH]; // Creates a current working array for the current 'read' name
        char cmdlist[MAX_LINES][MAX_LENGTH];
        int lineIndex = 0;

        int childPID = fork(); // Duplicates number of processes, essentially makes a new one for every files

        if (childPID == 0)
        {
            FILE *file = fopen(argv[i], "r"); // Opens a file from the specified arguments, configured to readonly
            if (!file)                        // Essentially throws an error if the filename does not exist within the directory
            {
                printf("Unable to open specified file\n");
                return -1;
            }

            // removes new line in fgets and copies the name as long if not empty.
            // We'll have to do some refactoring
            // Note 21 March 2023: We need to edit this chunk to execute the lines as opposed to copying the lines
            // We should use execvp() as per <https://sjsu.instructure.com/courses/1560213/files/folder/code/a3?preview=71399110>
            while (fgets(currentCMD, sizeof(currentCMD), file))
            {                                          // fgets reads and includes new line character
                char *ret = strchr(currentCMD, '\n'); // searches for first occurence of '\n' to replace with 0
                // can also use  if (buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';
                // https://aticleworld.com/remove-trailing-newline-character-from-fgets/   Links to an external site.
                if (ret)
                {
                    *ret = '\0';
                }

                if (strlen(currentCMD) != 0) // if the line is not empty copy the pointer and str name to be copied
                {
                    strcpy(cmdlist[lineIndex], currentCMD);
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
            write(fd[1], cmdlist, sizeof(cmdlist));

            exit(0); // Cleanup to prevent child from forking its respective children
        }
        // no error on child pid handling just yet
    }
    return 0;
}
