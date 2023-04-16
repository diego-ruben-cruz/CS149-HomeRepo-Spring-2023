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
    struct ContactNode *nextNodePtr;

} ContactNode;

/**
 * A function to initialize the contact node by include a pointer to the new node, and fill in all corresponding values
 *
 * @param newNode   The new node to fill in
 * @param newIndex  The index which the new node belongs to
 * @param initName  The name with which to initialize the new node
 * @param initNumber The number with which to initialize the new node
 * @param initNextNode The pointer to the next node in the linked list
 */
static void initializeContactNode(ContactNode *newNode, int newIndex, char *initName, char *initNumber, ContactNode *initNextNode)
{
    newNode->nodeIndex = newIndex;
    strcpy(newNode->contactName, initName);
    strcpy(newNode->contactPhoneNumber, initNumber);
    newNode->nextNodePtr = initNextNode;
}

/**
 * Accessor function to retrieve the name of the node
 *
 * @param targetNode The node from which to retrieve the contact name
 */
static char *GetName(ContactNode *targetNode)
{
    return targetNode->contactName;
}

/**
 * Accessor function to retrieve the number of the node
 *
 * @param targetNode The node from which to retrieve the contact number
 */
static char *GetPhoneNumber(ContactNode *targetNode)
{
    return targetNode->contactPhoneNumber;
}

/**
 * Accessor function to retrieve the pointer to the next node in the linked list
 *
 * @param targetNode The node from which to retrieve the pointer
 */
static ContactNode *GetNext(ContactNode *targetNode)
{
    return targetNode->nextNodePtr;
}

/**
 * Accessor function to insert a node following a given node
 *
 * @param nodeToInsert The node that shall be inserted into the linked list
 * @param precedingNode The node which shall point to the node to be inserted
 */
static void InsertAfter(ContactNode *nodeToInsert, ContactNode *precedingNode)
{
    precedingNode->nextNodePtr = nodeToInsert;
}

/**
 * Utility function to print a node to the commandline in the following format:
 * ex)
 * Name: Roxanne Hughes
 * Phone number: 443-555-2864
 *
 * @param targetNode The node to be printed
 */
static void PrintContactNode(ContactNode *targetNode)
{
    printf("Name: %s\n", GetName(targetNode));
    printf("Phone number: %s\n\n", GetPhoneNumber(targetNode));
}

/**
 * Utility function to free all nodes in the linked list in a recursive fashion
 *
 * @param refNode The head node for the linked list
 */
void FreeNodes(ContactNode *refNode)
{
    if (refNode != NULL) // Quick check to see if not nullpointer
    {
        FreeNodes(refNode->nextNodePtr);   // Recursive call to each node until the last one is called
        free(refNode->contactName);        // frees memory allotted to the string inside the struct
        free(refNode->contactPhoneNumber); // frees memory allotted to the string inside the struct
        free(refNode);                     // frees mem occupied by rest of node
    }
}

// Begin Main
int main(void)
{
    ContactNode *head = (ContactNode *)malloc(sizeof(ContactNode));
    ContactNode *temp = head;
    int contactIndex = 0;
    char tempName[UTIL_MAX_LENGTH];
    char tempNum[UTIL_MAX_LENGTH];
    initializeContactNode(head, contactIndex, "Dummy Head Node", "Nothing to see here", NULL);

    // Loop to collect input for 3 contacts
    for (int i = 0; i < 3; i++)
    {
        if (fgets(tempName, UTIL_MAX_LENGTH, stdin) != NULL)
        {
            contactIndex++;                         // Increase index of contact number
            fgets(tempNum, UTIL_MAX_LENGTH, stdin); // Retrieve number from the command line as well

            // Function to remove newline chars from the input
            tempName[strcspn(tempName, "\r\n")] = 0;
            tempNum[strcspn(tempNum, "\r\n")] = 0;

            // Create new node, and initialize it
            ContactNode *nextNode = (ContactNode *)malloc(sizeof(ContactNode));     // Create next node with mem allocated
            initializeContactNode(nextNode, contactIndex, tempName, tempNum, NULL); // Initialize node with proper values
            InsertAfter(nextNode, temp);                                            // Set tail of preceding node to current node
            temp = GetNext(temp);                                                   // Set ptr to current node to process next possible node
            // temp = nextNode;
        }
        else
        {
            temp->nextNodePtr = NULL; // set pointer to final node to NULL
            break;                    // end the loop, handles if the number of inputs is shorter than 6
        }
    }

    // Loop to iterate thru linked list to print information of contact to following format:
    // ex) Person 1: Roxanne Hughes, 443-555-2864
    temp = GetNext(head);
    for (int i = 0; i < contactIndex; i++)
    {
        printf("Person %d: %s, %s\n", temp->nodeIndex, GetName(temp), GetPhoneNumber(temp));
        temp = GetNext(temp); // Set ptr to next node
    }

    // Loop to iterate thru linked list to print contact info to following format:
    printf("\nCONTACT LIST\n");
    temp = GetNext(head);
    for (int i = 0; i < contactIndex; i++)
    {
        PrintContactNode(temp);
        temp = GetNext(temp); // Set ptr to next node
    }

    free(contactIndex);
    free(tempName);
    free(tempNum);
    FreeNodes(head);

    return 0;
} // End main
