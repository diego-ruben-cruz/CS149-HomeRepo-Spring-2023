/**
 * Description:
 * Write a hello world program that writes out the following:
 * Hello World!
 * How are you?
 *  (I'm fine).
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
#include <stdio.h>

int main(void)
{
    printf("Hello World!\n"); // printf is a C library function to print formatted strings to console
    printf("How are you?\n");
    printf("    (I'm fine)\n"); // tab was added to match zyBooks output
    return 0;                   // C convention to end a program, mostly seen in Java/C/C++/C#
}