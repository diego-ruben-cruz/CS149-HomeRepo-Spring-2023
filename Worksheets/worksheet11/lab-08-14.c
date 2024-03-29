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
#include <stdlib.h>
#include <string.h>
#define UTIL_MAX_LENGTH 100

typedef struct ContactNode
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
 * @param newName  The name with which to initialize the new node
 * @param newNumber The number with which to initialize the new node
 * @param newNextNode The pointer to the next node in the linked list
 */
void InitializeContactNode(ContactNode *newNode, char *newName, char *newNumber)
{
    newNode->contactName = malloc(UTIL_MAX_LENGTH * sizeof(char));
    newNode->contactPhoneNumber = malloc(UTIL_MAX_LENGTH * sizeof(char));
    strcpy(newNode->contactName, newName);
    strcpy(newNode->contactPhoneNumber, newNumber);
    newNode->nodeIndex = 0;
    newNode->nextNodePtr = NULL;
}

/**
 * Accessor function to retrieve the name of the node
 *
 * @param targetNode The node from which to retrieve the contact name
 */
char *GetName(ContactNode *targetNode)
{
    return targetNode->contactName;
}

/**
 * Accessor function to retrieve the number of the node
 *
 * @param targetNode The node from which to retrieve the contact number
 */
char *GetPhoneNumber(ContactNode *targetNode)
{
    return targetNode->contactPhoneNumber;
}

/**
 * Accessor function to retrieve the pointer to the next node in the linked list
 *
 * @param targetNode The node from which to retrieve the pointer
 */
ContactNode *GetNext(ContactNode *targetNode)
{
    return targetNode->nextNodePtr;
}

/**
 * Accessor function to insert a node following a given node
 *
 * @param nodeToInsert The node that shall be inserted into the linked list
 * @param precedingNode The node which shall point to the node to be inserted
 */
void InsertAfter(ContactNode *nodeToInsert, ContactNode *precedingNode)
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
void PrintContactNode(ContactNode *targetNode)
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
    // Variables are set up here
    ContactNode *head = (ContactNode *)malloc(sizeof(ContactNode));        // Create head node with mem allocated
    ContactNode *temp = head;                                              // Create temp variable that will help for creation of new nodes
    int contactIndex = 0;                                                  // Utility index int variable to add to node
    char tempName[UTIL_MAX_LENGTH];                                        // Utility name string storage to temporarily process then copy onto the structure
    char tempNum[UTIL_MAX_LENGTH];                                         // Utility phoneNum string storage to temporarily process then copy onto the structure
    InitializeContactNode(head, "Dummy Head Node", "Nothing to see here"); // Initialize dummy head node so subsequent nodes are from input
    head->nodeIndex = contactIndex;                                        // Init head node index to 0

    // Loop to collect input for 3 contacts
    for (int i = 0; i < 3; i++)
    {
        if (fgets(tempName, UTIL_MAX_LENGTH, stdin) != NULL) // Checks if input is null
        {
            contactIndex++;                         // Increase index of contact number
            fgets(tempNum, UTIL_MAX_LENGTH, stdin); // Retrieve number from the command line as well

            // Function to remove newline chars from the input
            tempName[strcspn(tempName, "\r\n")] = 0;
            tempNum[strcspn(tempNum, "\r\n")] = 0;

            // Create new node, and initialize it
            ContactNode *nextNode = (ContactNode *)malloc(sizeof(ContactNode)); // Create next node with mem allocated
            InitializeContactNode(nextNode, tempName, tempNum);                 // Initialize node with proper values
            nextNode->nodeIndex = contactIndex;                                 // Set index number of newly created node
            InsertAfter(nextNode, temp);                                        // Set tail of preceding node to current node
            temp = GetNext(temp);                                               // Set ptr to current node to process next possible node
        }
        else // It should not get to this point in the context of the program, but figured it was worth implementing out of principle
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
    // EXAMPLE====
    // CONTACT LIST
    // Name: John Doe
    // Phone number: 408-867-5309
    //
    // Name: Jane Doe
    // Phone number: 443-555-2864
    // END====
    // And so on for each name
    printf("\nCONTACT LIST\n");
    temp = GetNext(head);
    for (int i = 0; i < contactIndex; i++)
    {
        PrintContactNode(temp);
        temp = GetNext(temp); // Set ptr to next node
    }

    // Free allocation of memory for each node, refer to FreeNodes() function defined above
    FreeNodes(head);

    return 0;
} // End main
