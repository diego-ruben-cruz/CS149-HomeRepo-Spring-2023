/**
 * Description:
 * Output the following ASCII art
 *
 *     *
 *    ***
 *   *****
 *  *******
 *    ***
 *
 *
 *  /\   /\
 *    o o
 *   =   =
 *    ---
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 31 Jan 2023
 * Creation Date: 29 Jan 2023
 */

int main(void)
{
    // Print out tree
    printf("   *\n");  // printf is a C library function to print formatted strings to console
    printf("  ***\n"); // \n is an in-string formatting tool to produce a newline in console
    printf(" *****\n");
    printf("*******\n");
    printf("  ***\n\n\n");

    // Print out kitty
    printf("/\\   /\\\n");
    printf("  o o\n");
    printf(" =   =\n");
    printf("  ---\n");

    return 0; // C convention to end a program, mostly seen in Java/C/C++/C#
}