/**
 * Define structure for node
*/
#ifndef NODE_H
#define NODE_H
typedef struct Node
{
    char *line;
    int lineIndex;
    struct Node *nextLine;

} Node;

void PrintNodes(Node refNode); // Recursive function to

#endif