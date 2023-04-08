/**
 * main() function for ItemToPurchase Struct as defined in lab-07-06
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
 */
#include <stdio.h>
#include <string.h>
#include "ItemToPurchase.h"

int main(void)
{
    // Define both items of purchase before prompting to fill in the info.
    ItemToPurchase itemOne;
    ItemToPurchase itemTwo;

    // Item prompt for naming item 1
    printf("Item 1\n");
    printf("Enter the item name:\n");
    // Refer to slides on fgets, it essentially reads the whole line
    if (fgets(itemOne.itemName, MAX_LENGTH, stdin) != NULL)
    {
        // What this does is remove \n or \r from the input, removes newlines while preserving spaces
        itemOne.itemName[strcspn(itemOne.itemName, "\r\n")] = 0;
    }
    // printf("%s\n", itemOne.itemName); // Feedback/debugging line to show what was entered as the input

    // Item prompt for pricing item 1
    printf("Enter the item price:\n");
    scanf("%d", &itemOne.itemPrice);
    // printf("%d\n", itemOne.itemPrice); // Feedback/debugging line to show what was entered as the input

    // item prompt for quantifying item 1
    printf("Enter the item quantity:\n");
    scanf("%d", &itemOne.itemQuantity);
    // printf("%d\n", itemOne.itemQuantity); // Feedback/debugging line to show what was entered as the input


    char c = getchar();
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }

    // Item prompt for naming item 2
    printf("\nItem 2\n");
    printf("Enter the item name:\n");
    // Refer to slides on fgets, it essentially reads the whole line
    if (fgets(itemTwo.itemName, MAX_LENGTH, stdin) != NULL)
    {
        // What this does is remove \n or \r from the input, removes newlines while preserving spaces
        itemTwo.itemName[strcspn(itemTwo.itemName, "\r\n")] = 0;
    }
    // printf("%s\n", itemTwo.itemName); // Feedback/debugging line to show what was entered as the input

    // Item prompt for pricing item 2
    printf("Enter the item price:\n");
    scanf("%d", &itemTwo.itemPrice);
    // printf("%d\n", itemTwo.itemPrice); // Feedback/debugging line to show what was entered as the input


    // item prompt for quantifying item 2
    printf("Enter the item quantity:\n");
    scanf("%d", &itemTwo.itemQuantity);
    // printf("%d\n", itemTwo.itemQuantity); // Feedback/debugging line to show what was entered as the input


    printf("\nTOTAL COST\n");
    PrintItemCost(itemOne);
    PrintItemCost(itemTwo);

    printf("\nTotal: $%d\n", (itemOne.itemPrice * itemOne.itemQuantity) + (itemTwo.itemPrice * itemTwo.itemQuantity));

    return 0;
}