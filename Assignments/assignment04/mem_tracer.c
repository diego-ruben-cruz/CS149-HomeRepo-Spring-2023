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
 * gcc -o mem_tracer mem_tracer.c -Wall -W
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

int size = 10;
int length = 50;

/**
 * Define structure for linkedlist node
 */
#ifndef NODE_H
#define NODE_H
typedef struct Node
{
    char *line;
    int lineIndex;
    struct Node *nextLine;

} Node;
void PrintNodes(Node *refNode);                                          // Recursive function to print all nodes
void FreeNodes(Node *refNode);                                           // Recursive function to free all nodes in mem
void InitNode(Node *newNode, int lineIndex, char *line, Node *nextNode); // Function to initialize the node
void IncreaseArrayCapacity(char ***array, int j);
#endif

/**
 * Prints ALL of the lines to the console using printf()
 * Makes the assumption that the provided node is the head node.
 *
 * @param refNode   The reference node.
 */
void PrintNodes(Node *refNode)
{
    if (!refNode) // Quick check to see if not nullpointer
    {
        // Push Function to stack
        PUSH_TRACE("Printing Nodes...\n");                         // Refer to PUSH_TRACE in memtrace.c
        dprintf(2, "%d: %s\n", refNode->lineIndex, refNode->line); // Print out to logfile somethin like this: '###: insert_line_string_here' into its own line
        PrintNodes(refNode->nextLine);                             // Recursive call to each node until the last one gets called
        POP_TRACE();                                               // Refer to POP_TRACE in memtrace.c
    }
}

/**
 * Initializes a new node given a pointer to work with
 */
void InitNode(Node *newNode, int newLineIndex, char *newLine, Node *newNextLine)
{
    PUSH_TRACE("Initializing node..."); // Push function to stack
    newNode->line = malloc(length * sizeof(newLine));
    strcpy(newNode->line, newLine);
    newNode->lineIndex = newLineIndex;
    newNode->nextLine = newNextLine;
    POP_TRACE(); // Pop the function from the stack
}

void FreeNodes(Node *refNode)
{
    if (!refNode) // Quick check to see if not nullpointer
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
 * Increases the array capacity by a factor of 2
 */
void IncreaseArrayCapacity(char ***totalArray, int refIndex)
{
    size *= 2;
    *totalArray = (char **)realloc(*totalArray, size * sizeof(char *));
    for (int i = refIndex; i < size; i++)
    {
        (*totalArray)[i] = malloc(length * sizeof(char));
    }
}

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
 * See the examples of calling PUSH_TRACE and POP_TRACE below
 * in the main, make_extend_array, add_column functions.
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
void POP_TRACE() // remove the op of the stack
{
    TRACE_NODE *tnode;
    tnode = TRACE_TOP;
    TRACE_TOP = tnode->next;
    free(tnode);
}

/* function PRINT_TRACE prints out the sequence of function calls that are on the
stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC. */
/* Printing the function call sequence the other way around is also ok:
funcC:funcB:funcA:global */
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

#define realloc(a, b) REALLOC(a, b, __FILE__, __LINE__)
#define malloc(a) MALLOC(a, __FILE__, __LINE__)
#define free(a) FREE(a, __FILE__, __LINE__)

// function main
int main(int argc, char *argv)
{
    char **array;
    char *currentLine; // A brief holding variable to hold the line
    int lineCount = 0;
    Node *headNode = (Node *)malloc(sizeof(Node));
    Node *temp = headNode;
    InitNode(headNode, 0, "Dummy to hold index", NULL); // Inits head node as a dummy node

    // Create filedesc for writing to log file
    int file_desc_out = open("memtrace.out", O_RDWR | O_CREAT | O_APPEND, 0777);
    dup2(file_desc_out, 1);

    // Declare that the main function has begun
    PUSH_TRACE("main function has begun:");
    array = malloc(size * sizeof(char *)); // initializes array of size 10 Nodes

    while (fgets(currentLine, sizeof(), stdin) != NULL) // This is for the rest of the nodes
    {
        linecount++;
        currentLine[strcspn(nextNode->line, "\r\n")] = 0;                 // What this does is remove \n or \r from the input, removes newlines while preserving spaces
        strcpy(array[lineCount], currentLine);                            // copies the to the char** array that will be used later
        Node *nextNode = (Node *)malloc(sizeof(Node));                    // Makes new node with proper allocation
        InitNode(nextNode, i, strcpy(nextNode->line, currentLine), NULL); // Initializes new node using strcopy
        temp->nextLine = nextNode;                                        // Sets the tail of the linked-list to the newly created node
        temp = nextNode;                                                  // Sets the temp variable to the newly created node to create a new tail for the next line
        if (i + 1 == size)                                                // Increases capacity if size has been used up
        {
            IncreaseArrayCapacity(&array, i + 1);
        }
    }

    dprintf(2, "Array Values:\n");
    for (int i = 0; i < lineCount; i++)
    {
        dprintf(2, "%d: %s\n"i, array[i]); // Prints out array values for debugging purposes
    }

    dprintf(2, "\nLinkedList Values:\n");
    PrintNodes(headNode->nextLine); // Prints out linked-list values for debugging

    // This code block deallocates memoray to avoid memleaks
    free(currentLine);
    for (int i = 0; i < size; i++)
    {
        free(array[i]);
    }
    free(array);
    FreeNodes(headNode);
    POP_TRACE();
    free(TRACE_TOP);

    return 0;

} // end main
