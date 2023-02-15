/**
 * Description:
 * Write a program with 2 inputs for a given household,
 * current price and last month's price.
 *
 * Then, output a summary listing the price, the chage since last month,
 * and the estimated monthly mortgage computed as currentPrice * 0.051 / 12
 * End the last output with a newline
 *
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 2/09/2023
 * Creation Date: 2/09/2023
 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Basic variables for storing user input
    int currentPrice;
    int lastMonthsPrice;

    // Prompts for entering in the current price of the home
    // and the previous month's price
    printf("Please enter the current price of the house: $");
    scanf("%d", &currentPrice);
    printf("Please enter the price of the house from the previous month: $");
    scanf("%d", &lastMonthsPrice);

    // Thse lines accomplish the basic computation using formatted strings.
    printf("This house currently costs $%d. The change is $%d since last month.\n", currentPrice, currentPrice - lastMonthsPrice);
    printf("The estimated monthly mortgage is $%0.6lf.\n", (currentPrice * 0.051) / 12);

    return 0; // Basic exit code for the program since nothing
              // gets output from main operation

    /**
     * Test values:
     * 200000
     * 210000
     *
     * Expected output:
     * This house is $200000. The change is $-10000 since last month.
     * The estimated monthly mortgage is $850.000000.
     */
}