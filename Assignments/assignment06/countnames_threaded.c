/**
 * Description:
 * Assume that you have several text file with a name on each line, and names are separated by newlines.
 * Assume each row has one name (keep things simple) and a name can occur many times in the file.
 * Assume you are dealing with up to 100 individual names (since you would need dynamic
 * memory allocation for expanding an array to deal with more names, which we'll see later).
 * You want to read the names in and count the occurrences of each.
 * Since we want to be flexible on the type and size of characters we can handle,
 * you can assume ASCII code and you expect a file to contain simple characters of ASCII values from
 * 0-128. A name can be up to 30 characters long.
 *
 * You must be able to handle a file with any number of rows, including no names. It is ok if this is slow
 * (since you would need dynamic data structures like hash tables to make it fast, which we'll see later). You can
 * assume that the input file contains only valid characters and rows are separated by newlines; the input file may
 * contain a few empty lines as well (which you will ignore).
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 05/10/2023
 * Creation Date: 05/03/2023
 *
 * To compile with warnings and errors
 * gcc -o countnames_threaded countnames_threaded.c -Wall -W
 *
 * To execute
 * ./countnames_threaded.c names1.txt names2.txt
 *
 * To check for memleaks
 * valgrind --leak-check=full ./countnames_threaded.c names1.txt names2.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#define MAX_LENGTH 30 // Constant for length of string including nullchar
#define MAX_LINES 100 // Constant for max number of lines in a given file
#define MAX_ARGS 3    // Constant for the number of arguments expected from the command line

// ========================================================================
// Structs get defined here

// Contains data that should be known about a thread
struct THREADDATA_STRUCT
{
    pthread_t threadID;
    char *filename;
    pthread_t creator;
};

// Linked List for each name, count will get updated, features its own lock for access
typedef struct nameNode
{
    char name[MAX_LENGTH];
    int count;
    struct nameNode next;
    pthread_mutex_t nodeLock;
} nameNode;

// ==================================================================
// Global vars are here

pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER; // thread mutex lock for access to the log index
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER; // thread mutex lock for critical sections of allocating THREADDATA

typedef struct THREADDATA_STRUCT THREADDATA;
nameNode *name_counts = NULL; // Useful temp node for later

int logIndex = 0; // Log index, shared b/w threads

/**
 * Function for each thread to run independently while the overall proc is running
 *
 * @param x
 */
void *thread_runner(void *x)
{
    pthread_t me;
    me = pthread_self();
    printf("This is thread %ld (p=%p)", me, p); // Replace p with some form of getpid()
    pthread_mutex_lock(&tlock2); // critical section starts
    if (p == NULL)
    {
        p = (THREADDATA *)malloc(sizeof(THREADDATA));
        p->creator = me;
    }
    pthread_mutex_unlock(&tlock2); // critical section ends
    if (p != NULL && p->creator == me)
    {
        printf("This is thread %ld and I created THREADDATA %p", me, p);
    }
    else
    {
        printf("This is thread %ld and I can access the THREADDATA %p", me, p);
    }
    /**
     * //TODO implement any thread name counting functionality you need.
     * Assign one file per thread. Hint: you can either pass each argv filename as a
     * thread_runner argument from main.
     * Or use the logIndex to index argv, since every thread will increment the
     * logIndex anyway
     * when it opens a file to print a log message (e.g. logIndex could also index argv)....
     * Make sure to use any mutex locks appropriately
     */

    // We must use this line with a buffer string before
    // inserting a name into the linked list to remove newlines
    // currentLine[strcspn(currentLine, "\r\n")] = 0;

    pthread_mutex_lock(&tlock2); // critical section starts
    if (p != NULL && p->creator == me)
    {
        printf("This is thread %ld and I delete THREADDATA", me);
        pthread_mutex_lock(&tlock2);
        free(p);
        p = NULL;
        // pthread_mutex_unlock(&tlock2);
    }
    else
    {
        printf("This is thread %ld and I can access the THREADDATA", me);
        // pthread_mutex_unlock(&tlock2);
    }
    pthread_mutex_unlock(&tlock2); // critical section ends
}

/**
 * Main function that takes in two files as arguments
 *
 * Expects to do
 *
 */
int main(int argc, char *argv[])
{
    int fd[2]; // file descriptor integration

    if (argc != MAX_ARGS) // Check if two files are provided
    {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    FILE *file1 = fopen(argv[1], "r"); // Opens a file from the specified arguments, configured to readonly
    if (!file1)                        // Essentially throws an error if the filename does not exist within the directory
    {
        printf("Unable to open specified file\n");
        return -1;
    }

    FILE *file2 = fopen(argv[2], "r"); // Opens a file from the specified arguments, configured to readonly
    if (!file2)                        // Essentially throws an error if the filename does not exist within the directory
    {
        printf("Unable to open specified file\n");
        return -1;
    }

    // TODO similar interface as A2: give as command-line arguments two filenames of
    // numbers(the numbers in the files are newline - separated).
    printf("create first thread");
    pthread_create(&tid1, NULL, thread_runner, NULL); // DC Note: Replace tid with one provided by thread struct

    printf("create second thread");
    pthread_create(&tid2, NULL, thread_runner, NULL); // DC Note: Replace tid with one provided by thread struct

    printf("wait for first thread to exit");
    pthread_join(tid1, NULL);
    printf("first thread exited");

    printf("wait for second thread to exit");
    pthread_join(tid2, NULL);
    printf("second thread exited");
    // TODO print out the sum variable with the sum of all the numbers

    fclose(file1);
    fclose(file2);

    close(fd[0]);
    exit(0);
} // end main