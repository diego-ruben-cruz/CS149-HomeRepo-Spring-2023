/**
 * Description:
 * Write a program that uses fork() to output
 * "hello world from PID {insert_pid_here}!"
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
#include <unistd.h> // For linux, this program will not run with MinGW on Windows

int main(int argc, char *argv[])
{
    printf("hello world from parent PID %d\n", (int)getpid());

    int child1 = fork(); // duplicates number of processes, currently 2
    int child2 = fork(); // duplicates number of processes, currently 4

    if (child1 < 0 || child2 < 0)
    { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (child1 == 0 && child2 == 0)
    { // child (new process)
        printf("hello world from PID %d!\n", (int)getpid());
    }
    else
    { // parent goes down this path (main)
        printf("hello world from parent PID %d!\n", (int)getpid());
    }
    return 0;
}