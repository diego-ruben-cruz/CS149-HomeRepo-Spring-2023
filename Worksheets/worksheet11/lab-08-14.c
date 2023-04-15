/**
 * Define a structure ContactNode that implements a linked list.
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 04/17/2023
 * Creation Date: 04/15/2023
 */

#include <stdio.h>
#include <string.h>
#define UTIL_MAX_LENGTH 100

typedef struct ContactNode_struct
{
    int nodeIndex;
    char *contactName;
    char *contactPhoneNumber;
    ContactNode *nextNodePtr;

} ContactNode;

static void initializeContactNode(ContactNode *newNode, char *initName, char *initNumber, ContactNode *initNextNode)
{
    newNode->contactName = initName;
    newNode->contactPhoneNumber = initNumber;
    newNode->nextNodePtr = initNextNode;
}

static char *GetName(ContactNode *targetNode)
{
    return targetNode->contactName;
}

static char *GetPhoneNumber(ContactNode *targetNode)
{
    return targetNode->contactPhoneNumber;
}

static ContactNode *GetNext(ContactNode *targetNode)
{
    return targetNode->nextNodePtr;
}

static void InsertAfter(ContactNode *nodeToInsert, ContactNode *precedingNode)
{
    precedingNode->nextNodePtr = nodeToInsert;
}

static void PrintContactNode(ContactNode *targetNode)
{
    printf("Name: %s\n", GetName(targetNode));
    printf("Phone number: %s\n", GetPhoneNumber(targetNode));
}

int main(void)
{
    ContactNode *head = (ContactNode *)malloc(sizeof(ContactNode));
    initializeContactNode(head, "Dummy Head Node", "", NULL);
    ContactNode *temp = head;
    int contactIndex = 0

    // Loop to collect input  for 
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if(fgets() != NULL)
                }
    }



    // printf("Person %d: %s, %s", targetNode->nodeIndex, GetName(targetNode), GetPhoneNumber(targetNode));

    return 0;
}
