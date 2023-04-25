/**
 * Define structure for linkedlist node
 *
 * Not needed for compiling AS4, just useful when working with just problems particular to the nodes.
 */
#ifndef NODE_H
#define NODE_H
typedef struct Node
{
    char *line;
    int lineIndex;
    struct Node *nextLine;

} Node;

void PrintNodes(Node refNode); // Recursive function to print all nodes

#endif