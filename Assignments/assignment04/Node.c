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
    if (!node)
    {
        // Push Function To Stack
        PUSH_TRACE("Free-Nodes");
        FreeNodes(node->nextLine);
        free(node->line);
        free(node);
        POP_TRACE();
    }
}

void PrintNodes(Node *node)
{
    if (!node)
    {
        PUSH_TRACE("Print-Nodes");
        dprintf(2, "%d: %s\n", node->lineIndex, node->line);
        PrintNodes(node->nextLine);
        POP_TRACE();
    }
}
