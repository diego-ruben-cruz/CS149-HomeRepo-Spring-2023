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
 * ./countnames_threaded names.txt names2.txt
 *
 * To check for memleaks
 * valgrind --leak-check=full ./countnames_threaded names.txt names2.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#define MAX_LENGTH 30 // Constant for length of string including nullchar
#define MAX_LINES 100 // Constant for max number of lines in a given file
#define MAX_ARGS 3    // Constant for the number of arguments expected from the command line

// ========================================================================
// Structs get defined here

// Contains data that should be known about a thread
struct THREADDATA_STRUCT
{
    pthread_t threadID; // Basic threadID holding var, arbitrarily set by programmer
    char *filename;     // Which file the thread is working on
    pthread_t creator;  // The procID of the parent process of the thread
};

// Linked List for each name, count will get updated, features its own lock for access
typedef struct nameNode
{
    char name[MAX_LENGTH]; // Name string
    int count;             // Updates on repeated occurrences

    struct nameNode *next; // Pointer to the next name
} nameNode;

// ==================================================================
// Global vars are here

pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER; // thread mutex lock for access to the log index
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER; // thread mutex lock for critical sections of allocating THREADDATA
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER; // thread mutex lock when accessing name_counts

typedef struct THREADDATA_STRUCT THREADDATA;
nameNode *name_counts = NULL;

int logIndex = 0; // Log index, shared b/w threads

// =================================================================
// Utility functions go here

void timer()
{
    int hours, minutes, seconds, day, month, year; // Utility variables for each timefield
    time_t now;                                    // Utility temp variable to capture UNIX timestamp
    time(&now);

    struct tm *local = localtime(&now); // Captures time of local machine, means that it will not sync to servers

    // Running date conversions from UNIX to human-readable format
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;

    // Running time conversions from UNIX to human-readable format
    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;

    // print local date
    printf("Date => %02d/%02d/%d ",
           day, month, year);

    // print local time
    if (hours < 12) // Before Noon
        printf("and time => %02d:%02d:%02d am: ",
               hours, minutes, seconds);

    else
        printf("and time => %02d:%02d:%02d pm: ",
               hours - 12, minutes, seconds);
}

// add_name and name_count To LinkedList
void add_name(char *name, int count)
{
    // Acquire Lock
    // Before Accessing LinkedList
    pthread_mutex_lock(&tlock3);

    // Search Name In LinkedList
    nameNode *current = name_counts;
    while (current != NULL &&
           strcmp(current->name, name) != 0)
    {
        current = current->next;
    }

    if (current != NULL) // If the name is found, it will update count
    {
        current->count += count;
    }
    else // If the name is not found, it will create a new node and initialize count var
    {
        nameNode *new_node = malloc(sizeof(nameNode));
        strcpy(new_node->name, name);
        new_node->count = count;
        new_node->next = name_counts;
        name_counts = new_node;
    }
    // Release Lock after accessing LinkedList
    pthread_mutex_unlock(&tlock3);
}

// Utility function to free linked list to avoid memleaks
void FreeNodes(nameNode *refNode)
{
    if (refNode != NULL) // Quick check to see if not nullpointer
    {
        FreeNodes(refNode->next); // Recursive call to each node until the last one is called
        free(refNode);            // frees mem occupied by node
    }
}

// Print the name and name_counts in the list
void print_name_counts()
{
    // Acquire lock before accessing list
    pthread_mutex_lock(&tlock3);

    // Iterate thru list and print formatted output of name count
    nameNode *current = name_counts;
    while (current != NULL)
    {
        printf("%s: %d\n", current->name, current->count);
        current = current->next;
    }
    // Release lock after accessing list
    pthread_mutex_unlock(&tlock3);
}

// Count names in file
void *count_names(void *data)
{
    // Get threadID and filename from ThreadData
    pthread_t thread_id = ((THREADDATA *)data)->threadID;
    char *filename = ((THREADDATA *)data)->filename;

    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", filename);
        return NULL;
    }
    // Creation of log message, does not end the line, handles empty data and per-thread paths
    if ((data != NULL && ((THREADDATA *)data)->creator == thread_id))
    {
        printf("Log index %d, thread_id %ld, PID %d, ",
               logIndex++, thread_id, getpid());
        timer();
        printf("This is thread %ld and I created THREADDATA %p\n",
               thread_id, data);
    }
    else
    {
        printf("Log index %d, thread_id %ld, PID %d, ",
               logIndex++, thread_id, getpid());
        timer();
        printf("This is thread %ld and I created THREADDATA %p\n",
               thread_id, data);
        if (thread_id == 1)
        {
            printf("Log index %d, thread_id %d, PID %d, ",
                   logIndex++, 2, getpid());
            timer();
            printf("This is thread %d and I can access the THREADDATA %p\n",
                   2, data);
        }
        else
        {
            printf("Log index %d, thread_id %d, PID %d, ",
                   logIndex++, 1, getpid());
            timer();
            printf("This is thread %d and I can access the THREADDATA %p\n",
                   1, data);
        }
    }
    // If fopen sucess => log message
    char log_message[100];
    sprintf(log_message, "Log index %d, thread_id %ld, PID %d, ",
            logIndex++, thread_id, getpid());
    printf("%s", log_message);
    timer();
    printf("opened file %s\n", filename);
    
    // Read names from file and add to list on case-by-case basis
    char name[MAX_LENGTH];
    while (fgets(name, MAX_LENGTH, file) != NULL)
    {
        name[strcspn(name, "\r\n")] = '\0';
        if (strlen(name) != 0)
        {
            add_name(name, 1);
        }
    }

    // Close file
    fclose(file);
    return NULL;
}

/**
 * Main function that takes in two files as arguments
 *
 * Most functions will be called from the ones above.
 */
int main(int argc, char *argv[])
{
    // Check if two files were provided
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }
    // init Lock 2
    pthread_mutex_init(&tlock2, NULL);

    // Create Thread Data Structures
    THREADDATA thread_one_data;
    thread_one_data.threadID = 1;
    thread_one_data.filename = argv[1];

    THREADDATA thread_two_data;
    thread_two_data.threadID = 2;
    thread_two_data.filename = argv[2];

    // Create Threads
    printf("=============== Log Messages ===============\n");
    pthread_t thread_one, thread_two;
    printf("create first thread\n");
    pthread_create(&thread_one, NULL,
                   count_names, &thread_one_data);
    printf("create second thread\n");
    pthread_create(&thread_two, NULL,
                   count_names, &thread_two_data);

    // Wait For Threads To Finish
    pthread_join(thread_one, NULL);
    printf("first thread exited\n");
    pthread_join(thread_two, NULL);
    printf("second thread exited\n");

    // PRINT name_counts
    printf("=============== Name Counts ===============\n");
    print_name_counts();
    
    // Destroy Lock
    pthread_mutex_destroy(&tlock1);
    pthread_mutex_destroy(&tlock2);
    pthread_mutex_destroy(&tlock3);

    FreeNodes(name_counts); // This is the only free that is necessary to sucessfully dealloc total memory.
    return 0;
}