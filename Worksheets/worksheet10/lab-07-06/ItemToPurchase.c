/**
 * Define the function definitions for the ItemToPurchase struct
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
#include "ItemToPurchase.h"
#include <string.h>

void MakeItemBlank(ItemToPurchase *itemToReset)
{
    strncpy((*itemToReset).itemName, "none", sizeof((*itemToReset).itemName));
    (*itemToReset).itemPrice = 0;
    (*itemToReset).itemQuantity = 0;
}

void PrintItemCost(ItemToPurchase itemToPrint)
{
    printf("%s %d @ $%d = $%d\n", itemToPrint.itemName, itemToPrint.itemQuantity, itemToPrint.itemPrice, itemToPrint.itemPrice * itemToPrint.itemQuantity);
}