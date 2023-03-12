/**
 * Description:
 * Write a program that takes in a line of text as input, and outputs that line of text in reverse.
 * You may assume that each line of text will not exceed 50 characters.The program repeats,
 * ending when the user enters "Done", "done", or "d" for the line of text.
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 03/11/2023
 * Creation Date: 03/11/2023
 */
#include <stdio.h>
#include <string.h>

int main()
{
    char str[60];

    while (fgets(str, 60, stdin) != NULL)
    {
        char *ptr = strchr(str, '\n');
        if (ptr)
        {
            //if new line found replace with a null character
            *ptr  = '\0';
        }

        if (strcmp(str, "d") == 0 || strcmp(str, "done") == 0 || strcmp(str, "Done") == 0) return 0;

        int n = strlen(str);

        for (int i = n - 1; i >= 0; i--)
        {
            printf("%c", str[i]);
        }
        printf("\n");
    }

    return 0;
}
