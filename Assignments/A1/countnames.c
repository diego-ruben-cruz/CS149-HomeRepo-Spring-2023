/**
 * Description:
 * Assume that you have a text file with a name on each line,
 * and names are separated by newlines. Assume each row has one name (keep things simple) and a name can occur
 * many times in the file. Assume you are dealing with up to 100 individual names (since you would need dynamic
 * memory allocation for expanding an array to deal with more names, which we'll see later). You want to read the
 * names in and count the occurrences of each. Since we want to be flexible on the type and size of characters we
 * can handle, you can assume Ascii code and you expect a file to contain simple characters of Ascii values from
 * 0-128. A name can be up to 30 characters long.
 You must be able to handle a file with any number of rows, including no names. It is ok if this is slow
 (since you would need dynamic data structures like hash tables to make it fast, which we'll see later). You can
 assume that the input file contains only valid characters and rows are separated by newlines; the input file may
 contain a few empty lines as well (which you will ignore).
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 2/12/2023
 * Creation Date: 2/12/2023
 */
#include<stdio.h>

int main(int argc, char *argv[]) {
    //argc and argv are how command line arguments are passed to main(0 in C/C++.
    //Argc will be # of strings pointed to by argv
    //Argv = pointer
    int counter[100];
    int i;
    char names[100][30];

    FILE* file = fopen(filename, "r");

    
    fclose(file);
    return 0;
}

