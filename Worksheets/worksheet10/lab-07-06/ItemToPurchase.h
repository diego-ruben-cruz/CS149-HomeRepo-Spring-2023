/**
 * Define the Struct and related function declarations
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
#ifndef ITEMTOPURCHASE_H
#define ITEMTOPURCHASE_H
#define MAX_LENGTH 60

/**
 * Struct that defines an item object as the building block of an online shopping cart.
 *
 * Size: 64 bytes
 *
 */
typedef struct ItemToPurchase
{
    char itemName[MAX_LENGTH]; // This represents 60 bytes
    int itemPrice;             // this represents 2 bytes
    int itemQuantity;          // this represents 2 bytes
} ItemToPurchase;

void MakeItemBlank(ItemToPurchase *itemToReset);
void PrintItemCost(ItemToPurchase itemToPrint);

#endif