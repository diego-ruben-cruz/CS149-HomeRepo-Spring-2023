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
#include<string.h>
int main(int argc, char *argv[]) {
    //argc and argv are how command line arguments are passed to main(0 in C/C++.
    //Argc will be # of strings pointed to by argv
    //Argv = pointer
    const char *filename=argv[1];   //filename is taken as argument, pointer reference, assume each line max 30 char
    char length[30];
    char names[100][30];    //100 by 30 2D array        character array

    int counter[100];
    int i, j,k;


    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("Not able to open the file.");
        return -1;
    }
    else{
        printf("Opening the file...");
    }
    // DC Note
    // Brute force loop to traverse through the array looking for a particular name value
    // and add to the counter array, has a flaw in that it will double-count arrays in the file
    /*FGET from https://www.w3schools.com/c/c_files_read.php
     * The first parameter specifies where to store the file content, which will be in the length array we just created.
    The second parameter specifies the maximum size of data to read, which should match the size of length [30].
    The third parameter requires a file pointer that is used to read the file (fptr in our example).
     *
     */


    //REMOVES NEW LINE FROM FGETS AND COPES LINE with name as long as not empty.
    while(fgets(length,30,file)){      //fgets reads and includes new line character
        char *ret = strchr(length, '\n');   //searches for first occurence of '\n' to replace with 0
        // can also use  char *key_word = (char*)malloc(sizeof(char) * SIZE);
        // and then      key_word[strlen(key_word) - 1] = '\0'; to remove new lines
        if (ret){
            *ret  = '\0';
        }
         j=0;
        if (strlen(length) != 0){                   //if the line is not empty copy the name and length
            strcpy(names[j], length);
            j++;
        }
        else {
            printf(stderr, "[WARNING] : Line %d is empty\n", j);
        }
    }

    // Need to find method to get unique names and then stop looking for those unique names once they've already been searched
    // Not sure if Strcmp will play nice with the char array we've got, despite the fact that this is how they handle strings in C
    //Updating counter for duplicate names while also removing the duplicates, finally print at end of looping through character array
    int count = 0;
    for (i = 0; i < j; i++) {       //loop through lines of names
        for (k = i+1; k < j; k++) {
            if (strcmp(names[i], names[k]) ==       //check if same line
                0) {// Native C library function to use Strcmp, returns 0 if the strings are the same
                count++;            //if names are equal/match, count up.
                counter[k] = 0;     //reset
            }
        }
        if (counter[i]==0){
            counter[i]=count;
        }

        for(i=0;i<j;i++){
            if (counter[i]!=0){
                fprintf("%s: %d\n", names[i], counter[i]);
            }
        }

        fclose(file);
        return 0;
    }

}