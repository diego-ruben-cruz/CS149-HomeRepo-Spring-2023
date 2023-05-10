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
 * ./countnames_threaded.c names.txt names2.txt
 *
 * To check for memleaks
 * valgrind --leak-check=full ./countnames_threaded.c names1.txt names2.txt
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
    pthread_t threadID;
    char *filename;
    pthread_t creator;
};

// Linked List for each name, count will get updated, features its own lock for access
typedef struct nameNode
{
    char name[MAX_LENGTH];
    int count;
    pthread_mutex_t nodeLock;

    struct nameNode *next;
} nameNode;

// ==================================================================
// Global vars are here

pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER; // thread mutex lock for access to the log index
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER; // thread mutex lock for critical sections of allocating THREADDATA

typedef struct THREADDATA_STRUCT THREADDATA;
nameNode *name_counts = NULL; // Useful dummy head node for later

int logIndex = 0; // Log index, shared b/w threads

// =================================================================
// Utility functions go here

void timer()
{
    int hours, minutes, seconds, day, month, year; // Utility variables for each timefield
    time_t now;                                    // Utility temp variable to capture UNIX timestamp
    time(&now);

    struct tm *local = localtime(&now);

    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;

    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;

    // PRINT Current Date
    printf("Date => %02d/%02d/%d ",
           day, month, year);

    // PRINT Local Time
    if (hours < 12) // Before Midday
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
    pthread_mutex_lock(&(name_counts->nodeLock));

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
    // Release Lock
    // After Accessing LinkedList
    pthread_mutex_unlock(&(name_counts->nodeLock));
}

void FreeNodes(nameNode *refNode)
{
    if (refNode != NULL) // Quick check to see if not nullpointer
    {
        // Push Function To Stack
        FreeNodes(refNode->next); // Recursive call to each node until the last one is called
        free(refNode->name);      // frees memory allotted to the string inside the struct
        pthread_mutex_destroy(&(refNode->nodeLock));
        free(refNode); // frees mem occupied by rest of node
    }
}

// PRINT name and name_counts In LinkedList
void print_name_counts()
{
    // Acquire Lock
    // Before Accessing LinkedList
    pthread_mutex_lock(&(name_counts->nodeLock));
    // PRINT name and name_counts In LinkedList
    nameNode *current = name_counts;
    while (current != NULL)
    {
        printf("%s: %d\n", current->name, current->count);
        current = current->next;
    }
    // Release Lock
    // After Accessing LinkedList
    pthread_mutex_unlock(&(name_counts->nodeLock));
}

// Count Names In File
void *count_names(void *data)
{
    // Get Thread ID & Filename
    // From Thread Data
    pthread_t thread_id = ((THREADDATA *)data)->threadID;
    char *filename = ((THREADDATA *)data)->filename;
    // Open File
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", filename);
        return NULL;
    }
    // Log Messages
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
    // If File Opened - Log
    char log_message[100];
    sprintf(log_message, "Log index %d, thread_id %ld, PID %d, ",
            logIndex++, thread_id, getpid());
    printf("%s", log_message);
    timer();
    printf("opened file %s\n", filename);
    // Read Names
    // From File & Add To LinkedList
    char name[MAX_LENGTH];
    while (fscanf(
               file, "%s", name) == 1)
    {
        add_name(name, 1);
    }
    // Close File
    fclose(file);
    return NULL;
}

/**
 * Main function that takes in two files as arguments
 *
 * Most functions will be called from the ones above:
 *
 */
int main(int argc, char *argv[])
{
    // Check If
    // Two Files Provided
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }
    // Initialize Lock
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

    // printf("WAIT FOR FIRST THREAD TO EXIT\n");
    pthread_join(thread_one, NULL);
    printf("first thread exited\n");
    // printf("WAIT FOR SECOND THREAD TO EXIT\n");
    pthread_join(thread_two, NULL);
    printf("second thread exited\n");

    // PRINT name_counts
    printf("=============== Name Counts ===============\n");
    print_name_counts();
    // Destroy Lock
    pthread_mutex_destroy(&tlock1);
    pthread_mutex_destroy(&tlock2);
    FreeNodes(name_counts->next);
    return 0;
}