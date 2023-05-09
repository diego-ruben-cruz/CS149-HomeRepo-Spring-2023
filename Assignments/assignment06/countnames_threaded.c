/**
 * Description:
 * Assume that you have several text file with a name on each line, and names are separated by newlines.
 * Assume each row has one name (keep things simple) and a name can occur many times in the file.
 * Assume you are dealing with up to 100 individual names (since you would need dynamic
 * memory allocation for expanding an array to deal with more names, which we'll see later).
 * You want to read the names in and count the occurrences of each.
 * Since we want to be flexible on the type and size of characters we can handle,
 * you can assume Ascii code and you expect a file to contain simple characters of Ascii values from
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
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

// thread mutex lock for access to the log index
// TODO you need to use this mutexlock for mutual exclusion
// when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;

// thread mutex lock for critical sections of allocating THREADDATA
// TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;

// thread mutex lock for access to the name counts data structure
// TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void *thread_runner(void *);
pthread_t tid1, tid2;

// struct points to the thread that created the object.
// This is useful for you to know which is thread1. Later thread1 will also
// deallocate.
struct THREADDATA_STRUCT
{
    pthread_t creator;
};

typedef struct THREADDATA_STRUCT THREADDATA;
THREADDATA *p = NULL;

int logindex = 0; // variable for indexing of messages by the logging function.
int *logip = &logindex;

// The name counts.
//  You can use any data structure you like, here are 2 proposals: a linked list OR an array(up to 100 names).
// The linked list will be faster since you only need to lock one node, while for the array you need to lock the whole array.
// You can use a linked list template from A5. You should also consider using a hash table, like in A5(even faster).
struct NAME_STRUCT
{
    char name[30];
    int count;
};

typedef struct NAME_STRUCT THREAD_NAME;
// array of 100 names
THREAD_NAME names_counts[100];

// node with name_info for a linked list
struct NAME_NODE
{
    THREAD_NAME name_count;
    struct NAME_NODE *next;
};

int main()
{
    // TODO similar interface as A2: give as command-line arguments three filenames of
    // numbers(the numbers in the files are newline - separated).
    printf("create first thread");
    pthread_create(&tid1, NULL, thread_runner, NULL);
    printf("create second thread");
    pthread_create(&tid2, NULL, thread_runner, NULL);
    printf("wait for first thread to exit");
    pthread_join(tid1, NULL);
    printf("first thread exited");
    printf("wait for second thread to exit");
    pthread_join(tid2, NULL);
    printf("second thread exited");
    // TODO print out the sum variable with the sum of all the numbers
    exit(0);
} // end main

void *thread_runner(void *x)
{
    pthread_t me;
    me = pthread_self();
    printf("This is thread %ld (p=%p)", me, p);
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
    thread_runner argument from main.
    * Or use the logindex to index argv, since every thread will increment the
    logindex anyway
    * when it opens a file to print a log message (e.g. logindex could also index
    argv)....
    * //Make sure to use any mutex locks appropriately
    */
    // TODO use mutex to make this a start of a critical section
    // critical section starts
    if (p != NULL && p->creator == me)
    {
        printf("This is thread %ld and I delete THREADDATA", me);
        /**
         * TODO Free the THREADATA object.
         * Freeing should be done by the same thread that created it.
         * See how the THREADDATA was created for an example of how this is done.
         */
    }
    else
    {
        printf("This is thread %ld and I can access the THREADDATA", me);
    }
}