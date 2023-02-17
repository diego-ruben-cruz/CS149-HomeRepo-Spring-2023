/**
 * Description:
 * Write a program that reads a list of integers, and outputs those integers in reverse.
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
 * Last Modified: 2/20/2023
 * Creation Date: 2/16/2023
 */
#include <stdio.h>

int main(void)
{
    int i = 0;
    int userVals[20]; // Array to hold the user's input integers

    printf("Please input a list of numbers (less than 20 numbers): ");
    /**
     * Taking in multiple numbers and adding them to an array will def require a loop
     *
     * The main concern for me is in how to take them in with space separating the numbers and a newline char entered as eof
     *
     * The only solution I've found thus far is this: <https://stackoverflow.com/a/25142013>
     *
     * Textbook uses this: <https://learn.zybooks.com/zybook/SJSUCS149SE149AndreopoulosSpring2023/chapter/5/section/8>
     * The main flaw of the textbook is that it doesn't quite stop whenever the user is finished with inserting values before the limit, and doesn't take in input as a single line.
     */

    return 0;
}
