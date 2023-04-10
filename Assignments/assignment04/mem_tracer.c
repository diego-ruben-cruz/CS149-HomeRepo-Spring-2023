/**
 * Description:
 * Store the command lines in an array and trace the memory usage
 * 
 * Implement a program that reads all lines from stdin into a dynamically allocated array of type char**
 * This will make it so that there are no longer any limitations such as 100 lines or 30 chars
 * 
 * Initialize the array mem with malloc up to 10 char* pointers,
 * and use realloc to expand the array if the init-size isn't big enough
 * 
 * Store each line in a linked list where a node contains the line as a string and line index
 * Implement a recursive function PrintNodes that prints to std_out the content of all nodes in the linked list
 * Call it at least once from the main() function.
 * 
 * Implement tracing of mem-consumption by using a stack to hold the function names that get called,
 * and print the mem consumed when mem gets allocated, reallocated, or freed
 * Write separate functinos for each case of allocation/deallocation
 * 
 * Your process will write all mem-tracing messages to a log file "memtrace.out"
 * You can use dup2 for the purpose of redirecting stdout(fd 1) to memtrace.out
 * 
 * Ensure there are no mem-leaks, use valgrind to detect mem-leaks
 * Your code should work on input files up to a few hundred lines.
 * 
 *  Understand how processes get executed in parallel, keep logs, track exit codes and signals, and duplicate file descriptors.
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 03/24/2023
 * Creation Date: 03/20/2023
 *
 * To compile with warnings and errors
 * gcc -o proc_manager proc_manager.c -Wall -W
 *
 * To execute
 * ./proc_manager.c < cmds.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LENGTH 30 // Constant for length of string including nullchar
#define MAX_LINES 100 // Constant for max number of lines in a given file

int main(int argc, char *argv[])
{

    int process = 0; // main index to keep track of line number

    char cmds[MAX_LINES][MAX_LENGTH]; // Creates 2D array of names listed in each file

    // read string and store in cmds array until end of file.
    while (scanf("%s", cmds[process++]) != EOF)
        ;

    // If the filedesc isn't prim n proper, it returns a -1 for the error

    // pids are stored in array
    int pids[process];
    // This loops for each file, such that a separate process is made for each one
    for (int i = 0; i < process; i++)
    {
        pids[i] = fork(); // Duplicates number of processes, makes a new one for every cmds file

        // CHILD PROCESS

        if (pids[i] == 0)
        {
            char *arr[50];
            int j = 0;
            // Getting list of args by splitting the command, cmds string for current i is tokenized into indivual arguments using strtok and stored in arr
            arr[j] = strtok(cmds[i], " ");
            while (arr[j] != NULL)
                arr[++j] = strtok(NULL, " ");
            arr[j] = NULL;

            // out is pathed to .out file
            char out[30];

            char err[30];

            // concatenate pids
            sprintf(out, "%d", getpid());
            sprintf(err, "%d", getpid());
            strcat(out, ".out");
            strcat(err, ".err");

            // create out and error files
            //  open two file descriptors for out and err files, if file exist
            // O_RDWR = file can be read/written to. O_creat creates file if doesn't exist, Append adds any writes to end of file, 0777 means all users have full permission read write execute
            int fd_out = open(out, O_RDWR | O_CREAT | O_APPEND, 0777);
            int fd_err = open(err, O_RDWR | O_CREAT | O_APPEND, 0777);

            // Dup2 redirects stdout and stderr to .out and err files
            dup2(fd_out, 1);
            dup2(fd_err, 2);

            dprintf(1, "Starting Command %d: Child %d PID of parent %d\n", i + 1, getpid(), getppid());

            // execute cmd
            char *args[] = {"wc", "-l", "-w", "-c", cmds[i], NULL};
            execvp("wc", args);

            // if execvp doesn't work, error has occurred/new process img not successful
            if (execvp(arr[0], arr) == -1)
            {
                fprintf(stderr, "Failed to execute command %d\n", i + 1);
                exit(EXIT_FAILURE);
            }
        }
    }
    // PARENT

    for (int i = 0; i < process; i++)
    {
        if (pids[i] > 0)
        {
            char out[30];
            char err[30];
            int status;
            int pid;

            if ((pid = wait(&status)) > 0)
            {
                sprintf(out, "%d", pid);
                sprintf(err, "%d", pid);
                strcat(out, ".out");
                strcat(err, ".err");

                int fd_out = open(out, O_RDWR | O_CREAT | O_APPEND, 0777);
                int fd_err = open(err, O_RDWR | O_CREAT | O_APPEND, 0777);

                dup2(fd_out, 1);
                dup2(fd_err, 2);

                dprintf(1, "Finished Child %d pID of Parent %d\n", pid, getpid());

               
                // When successfully exited, normal terminate w/exitcode
                if (WIFEXITED(status))
                {
                    dprintf(2, "Exited With Exitcode = %d\n", status);
                }
                // Unsuccessful exit, use kill w/signal
                else if (WIFSIGNALED(status))
                {
                    dprintf(2, "Killed With Signal %d\n", status);
                }
            }
        }
    }
    return 0;
}
