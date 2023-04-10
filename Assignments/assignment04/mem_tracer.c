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
 * insert line here
 * 
 * To execute
 * insert line here
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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
void PrintNodes(Node *refNode); // Recursive function to print all nodes
#endif

void FreeNodes(Node *refNode)
{
    if (!refNode) // Quick check to see if not nullpointer
    {
        // Push Function To Stack
        PUSH_TRACE("Free-Nodes");  // Refer to PUSH_TRACE in memtracer.c
        FreeNodes(refNode->nextLine); // Recursive call to each node until the last one is called
        free(refNode->line);          // frees memory allotted to the string inside the struct
        free(refNode);                // frees mem occupied by rest of node
        POP_TRACE();               // Refer to POP_TRACE in memtracer.c
    }
}

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
        PUSH_TRACE("Printing Nodes...\n");                           // Refer to PUSH_TRACE in memtrace.c
        dprintf(2, "%d: %s\n", refNode->lineIndex, refNode->line); // Print out to logfile somethin like this: '###: insert_line_string_here' into its own line
        PrintNodes(refNode->nextLine);                          // Recursive call to each node until the last one gets called
        POP_TRACE();                                         // Refer to POP_TRACE in memtrace.c
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
    dprintf(1,"File '%s', line %d, function %s reallocated the memory segment at address %p to new size %d\n", file, line, PRINT_TRACE(), &p, t);
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

// function add_column will add an extra column to a 2d array of ints.
// This function is intended to demonstrate how memory usage tracing of realloc is done
// Returns the number of new columns (updated)
int add_column(int **array, int rows, int columns)
{
    PUSH_TRACE("add_column");
    int i;
    for (i = 0; i < rows; i++)
    {
        array[i] = (int *)realloc(array[i], sizeof(int) * (columns + 1));
        array[i][columns] = 10 * i + columns;
    } // for
    POP_TRACE();
    return (columns + 1);
}

// function make_extend_array
// Example of how the memory trace is done
// This function is intended to demonstrate how memory usage tracing of malloc and free is done
void make_extend_array()
{
    PUSH_TRACE("make_extend_array");
    int i, j;
    int **array;
    int ROW = 4;
    int COL = 3;
    // make array
    array = (int **)malloc(sizeof(int *) * 4); // 4 rows
    for (i = 0; i < ROW; i++)
    {
        array[i] = (int *)malloc(sizeof(int) * 3); // 3 columns
        for (j = 0; j < COL; j++)
            array[i][j] = 10 * i + j;
    } // for
    // display array
    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
            printf("array[%d][%d]=%d\n", i, j, array[i][j]);
    // and a new column
    int NEWCOL = add_column(array, ROW, COL);
    // now display the array again
    for (i = 0; i < ROW; i++)
        for (j = 0; j < NEWCOL; j++)
            printf("array[%d][%d]=%d\n", i, j, array[i][j]);
    // now deallocate it
    for (i = 0; i < ROW; i++)
        free((void *)array[i]);
    free((void *)array);
    POP_TRACE();
    return;
}

// function main
int main()
{
    PUSH_TRACE("main");
    make_extend_array();
    POP_TRACE();
    return (0);
} // end main
