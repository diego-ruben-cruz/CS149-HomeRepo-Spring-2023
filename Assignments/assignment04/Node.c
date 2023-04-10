/**
 * Define a structure to allow for a linked list
 *
 */
#include "Node.h"

/**
 * Prints ALL of the lines to the console using printf()
 * Makes the assumption that the provided node is the head node.
 *
 * @param refNode   The reference node.
 */
void PrintNodes(Node *refNode) // Recursive function to
{
    printf("%s", refNode->line); // This prints the actual line of the function
    if (!refNode->nextLine)      // This checks for a possible nullpointer on nextLine var
    {
        PrintNodes(refNode->nextLine); // Calls the print again if the pointer is not null
    }
    // It only gets to this line when the nextLine is a nullpointer, which ends the operation
}

void FreeNodes(Node *node)
{
    if (!node) // Quick check to see if not nullpointer
    {
        // Push Function To Stack
        PUSH_TRACE("Free-Nodes");  // Refer to PUSH_TRACE in memtrace.c
        FreeNodes(node->nextLine); // Recursive call to each node until the last one is called
        free(node->line);          // frees memory allotted to the string inside the struct
        free(node);                // frees mem occupied by rest of node
        POP_TRACE();               // Refer to POP_TRACE in memtrace.c
    }
}

void PrintNodes(Node *node)
{
    if (!node) // Quick check to see if not nullpointer
    {
        // Push Function to stack
        PUSH_TRACE("Print-Nodes");                           // Refer to PUSH_TRACE in memtrace.c
        dprintf(2, "%d: %s\n", node->lineIndex, node->line); // Print out to logfile somethin like this: '###: insert_line_string_here' into its own line
        PrintNodes(node->nextLine);                          // Recursive call to each node until the last one gets called
        POP_TRACE();                                         // Refer to POP_TRACE in memtrace.c
    }
}
