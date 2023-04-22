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
 * Understand how processes get executed in parallel, keep logs, track exit codes and signals, and duplicate file descriptors.
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 04/10/2023
 * Creation Date: 04/07/2023
 *
 * To compile with warnings and errors
 * gcc -o mem_tracer mem_tracer.c -Wall -W
 *
 * To check execution for memleaks
 * valgrind --leak-check=full ./mem_tracer < cmds.txt
 *
 * To execute
 * ./mem_tracer < cmds.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define UTIL_MAX_LENGTH 100

int size = 10;   // Initial size of the array, will be resized as needed as per as4 specs
int length = 50; // Initial length of the string buffer, resized as needed when going line-by-line

/**
 * Define structure for linkedlist node
 *
 * Size: 18 bytes
 */
typedef struct Node
{
    char *line;
    int lineIndex;
    struct Node *nextLine;

} Node;

// Define the functions which will be available for nodes
void PrintNodes(Node *refNode);                                          // Recursive function to print all nodes
void FreeNodes(Node *refNode);                                           // Recursive function to free all nodes in mem
void InitNode(Node *newNode, int lineIndex, char *line, Node *nextNode); // Function to initialize the node
void IncreaseArrayCapacity(char ***array, int j);                        // Function to increase the size of the array of strings

/**
 * TRACE_NODE_STRUCT is a linked list of pointers to function identifiers
 *
 * TRACE_TOP is the head of the list is the top of the stack
 */
struct TRACE_NODE_STRUCT
{
    char *functionid;               // ptr to function identifier (a function name)
    struct TRACE_NODE_STRUCT *next; // ptr to next frama
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE *TRACE_TOP = NULL; // ptr to the top of the stack

/**
 * function PUSH_TRACE
 *
 * The purpose of this stack is to trace the sequence of function calls,
 * just like the stack in your computer would do.
 * The "global" string denotes the start of the function call trace.
 * The char *p parameter is the name of the new function that is added to the call trace.
 */
void PUSH_TRACE(char *p) // push p on the stack
{
    TRACE_NODE *tnode;
    static char glob[] = "global";
    if (TRACE_TOP == NULL)
    {
        // initialize the stack with "global" identifier
        TRACE_TOP = (TRACE_NODE *)malloc(sizeof(TRACE_NODE));
        // no recovery needed if allocation failed, this is only
        // used in debugging, not in production
        if (TRACE_TOP == NULL)
        {
            printf("PUSH_TRACE: memory allocation error\n");
            exit(1);
        }
        TRACE_TOP->functionid = glob;
        TRACE_TOP->next = NULL;
    }

    // create the node for p
    tnode = (TRACE_NODE *)malloc(sizeof(TRACE_NODE));

    // no recovery needed if allocation failed, this is only used in debugging, not in production
    if (tnode == NULL)
    {
        printf("PUSH_TRACE: memory allocation error\n");
        exit(1);
    }

    tnode->functionid = p;
    tnode->next = TRACE_TOP; // insert fnode as the first in the list
    TRACE_TOP = tnode;       // point TRACE_TOP to the first node
}

/**
 * function POP_TRACE
 * Pop a function call from the stack
 */
void POP_TRACE() // remove the top of the stack
{
    TRACE_NODE *tnode;
    tnode = TRACE_TOP;
    TRACE_TOP = tnode->next;
    free(tnode);
}

/* function PRINT_TRACE prints out the sequence of function calls that are on the
stack at this instance */
char *PRINT_TRACE()
{
    int depth = 50; // A max of 50 levels in the stack will be combined in a string for printing out.
    int i, length, j;
    TRACE_NODE *tnode;
    static char buf[100];
    if (TRACE_TOP == NULL)
    {                          // stack not initialized yet, so we are
        strcpy(buf, "global"); // still in the `global' area
        return buf;
    }
    /* peek at the depth(50) top entries on the stack, but do not
    go over 100 chars and do not go over the bottom of the
    stack */
    sprintf(buf, "%s", TRACE_TOP->functionid);
    length = strlen(buf); // length of the string so far
    for (i = 1, tnode = TRACE_TOP->next;
         tnode != NULL && i < depth;
         i++, tnode = tnode->next)
    {
        j = strlen(tnode->functionid); // length of what we want to add
        if (length + j + 1 < 100)
        { // total length is ok
            sprintf(buf + length, ":%s", tnode->functionid);
            length += j + 1;
        }
        else // it would be too long
            break;
    }
    return buf;
}

// function REALLOC calls realloc
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void *REALLOC(void *p, int t, char *file, int line)
{
    p = realloc(p, t);
    dprintf(1, "File '%s', line %d, function %s reallocated the memory segment at address %p to new size %d\n", file, line, PRINT_TRACE(), &p, t);
    return p;
}

// function MALLOC calls malloc
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void *MALLOC(int t, char *file, int line)
{
    void *p;
    p = malloc(t);
    dprintf(1, "File '%s', line %d, function %s allocated new memory segment at address %p to size %d\n", file, line, PRINT_TRACE(), &p, t);
    return p;
}

// function FREE calls free
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void *p, char *file, int line)
{
    dprintf(1, "File '%s', line %d, function %s deallocated the memory segment at address %p\n", file, line, PRINT_TRACE(), &p);
    free(p);
}

// Define re-definitions of in-house functions when working with the stack in particular
#define realloc(a, b) REALLOC(a, b, __FILE__, __LINE__)
#define malloc(a) MALLOC(a, __FILE__, __LINE__)
#define free(a) FREE(a, __FILE__, __LINE__)

/**
 * Prints ALL of the lines to the console using printf()
 * Makes the assumption that the provided node is the head node.
 *
 * @param refNode   The reference node.
 */
void PrintNodes(Node *refNode)
{
    if (refNode != NULL) // Quick check to see if not nullpointer
    {
        // Push Function to stack
        PUSH_TRACE("Printing Nodes...\n");                         // Refer to PUSH_TRACE in memtrace.c
        dprintf(2, "%d: %s\n", refNode->lineIndex, refNode->line); // Print out to logfile somethin like this: '###: insert_line_string_here' into its own line
        PrintNodes(refNode->nextLine);                             // Recursive call to each node until the last one gets called
        POP_TRACE();                                               // Refer to POP_TRACE in memtrace.c
    }
}

/**
 * Initializes a new node given a pointer to store the information.
 *
 * @param newNode   The pointer for the new node that was initialized
 * @param newLineIndex  The line index that corresponds to the node
 * @param newLine   The string with which to initialize the new node
 * @param newNextLine   The pointer to the next node, if it is the very last node, this value should be NULL
 */
void InitNode(Node *newNode, int newLineIndex, char *newLine, Node *newNextLine)
{
    PUSH_TRACE("Initializing node...");            // Push function to stack
    newNode->line = malloc(length * sizeof(char)); // allocate memory to the
    strcpy(newNode->line, newLine);                // Copy the string from the newLine pointer to the pointer inside of the new node
    newNode->lineIndex = newLineIndex;             // Sets line index of node info to the one given
    newNode->nextLine = newNextLine;               // Sets pointer for the next node in succession to the given value
    POP_TRACE();                                   // Pop the function from the stack
}

/**
 * Frees the nodes from memory, provided a pointer to a node. This is sequential, so it is best to free using the head node.
 *
 * @param refNode   The node from which to free each individual node
 */
void FreeNodes(Node *refNode)
{
    if (refNode != NULL) // Quick check to see if not nullpointer
    {
        // Push Function To Stack
        PUSH_TRACE("Free-Nodes");     // Refer to PUSH_TRACE in memtracer.c
        FreeNodes(refNode->nextLine); // Recursive call to each node until the last one is called
        free(refNode->line);          // frees memory allotted to the string inside the struct
        free(refNode);                // frees mem occupied by rest of node
        POP_TRACE();                  // Refer to POP_TRACE in memtracer.c
    }
}

/**
 * Increases the array capacity by a factor of 2 to allow for more commands to be processed if there are more than what size currently measures.
 *
 * @param totalArray The array which contains the string array to allow for different files.
 * @param refIndex  The index of the very last node to increase the size with.
 */
void IncreaseArrayCapacity(char ***totalArray, int refIndex)
{
    size *= 2;                                                          // Doubles the size variable
    *totalArray = (char **)realloc(*totalArray, size * sizeof(char *)); // Runs a reallocation of memory according to the total length of the master array
    for (int i = refIndex; i < size; i++)                               // Loop to iterature thru the master array
    {
        (*totalArray)[i] = malloc(length * sizeof(char)); // Runs a new allocation of memory based on the length of each string in the array
    }
}

// BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{
    char **array;                                    // Utility string array to store each cmd in a variable setting, ignoring char/numOfCommand limits of previous assignments
    char commands[UTIL_MAX_LENGTH][UTIL_MAX_LENGTH]; // Utility fixed-size string array to run copies of already-processed lines to array
    char currentLine[UTIL_MAX_LENGTH];               // Utility string to take input from stdin and remove newlines before it gets passed to commands[][]
    int process_num = 0;                             // Utility int to keep track of how many lines have been processed

    while (fgets(currentLine, UTIL_MAX_LENGTH, stdin) != NULL) // While loop to iterature through the entirety of the file until EOF has been reached
    {
        process_num++;                                 // Increase the index num, will init to 1 to handle empty files with no commands
        currentLine[strcspn(currentLine, "\r\n")] = 0; // Quick operation to handle newline chars and remove them from the line before they get stored/executed
        strcpy(commands[process_num], currentLine);    // Copies already-processed line to commands[][]
    }

    // File Descriptor
    int file_descriptor_out = open("memtrace.out", O_RDWR | O_CREAT | O_APPEND, 0777); // Create File Descriptor
    dup2(file_descriptor_out, 1);                                                      // Linux syscall to assign filedesc 1 to memtrace.out
    PUSH_TRACE("main");                                                                // Push Main Function To Stack

    array = malloc(size * sizeof(char *)); // Allocate Array Of Size 10

    // Head Node
    Node *head = (Node *)malloc(sizeof(Node)); // Allocate Memory For LinkedList Head
    InitNode(head, 0, "Dummy Head Node", NULL);
    Node *temp = head; // Create Temp Pointer

    // Allocate Memory For Each Element
    for (int i = 0; i < size; i++)
    {
        array[i] = malloc(length * sizeof(char));
    }

    // Copy each line to the double pointer ** to eliminate char limit
    for (int i = 0; i < process_num; i++)
    {
        strcpy(array[i], commands[i]);                 // Copy string from commands[][] to *array[]
        Node *nextNode = (Node *)malloc(sizeof(Node)); // Create next node with mem allocated
        InitNode(nextNode, i, commands[i], NULL);      // Copy the string to the node
        temp->nextLine = nextNode;                     // Set tail of previous node to current node
        temp = nextNode;                               // Set ptr to current node to process the next node
        if (i + 1 == size)                             // Check if size is bigger than previously set value
        {
            IncreaseArrayCapacity(&array, i + 1); // If it is bigger, then increase array capacity to allow for more lines to be processed
        }
    }

    // Print Arrays
    dprintf(2, "Array values:\n");
    for (int i = 1; i < process_num; i++)
    {
        dprintf(2, "%d: %s\n", i, array[i]);
    }

    // Skip Dummy Head Nodes, Print LinkedList Values
    dprintf(2, "\nLinkedList values:\n");
    PrintNodes(head->nextLine->nextLine);

    for (int i = 0; i < size; i++)
    {
        free(array[i]); // Free strings stored in array
    }
    free(array);     // Free The Array
    FreeNodes(head); // Recursively Free Nodes In LinkedList
    POP_TRACE();     // Pop Main Function From Stack
    free(TRACE_TOP); // Free The Stack

    return 0; // end main
}