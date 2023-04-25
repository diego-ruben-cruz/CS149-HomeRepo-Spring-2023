/**
 * Description:
 * Edit lseek_example.c to read the 1st + (3*i)th bytes of a file
 * and copy them to another file
 *
 * Test run:
 * start.txt contains "ABCDEFGHIJKLM"
 * out.txt should contain "ADGJM"
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 03/20/2023
 * Creation Date: 03/20/2023
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void func(char arr[], int n)
{
    // Open the file for READ only.
    int f_read = open("start.txt", O_RDONLY);

    // Open the file for WRITE and READ only.
    int f_write = open("end.txt", O_WRONLY | O_CREAT, 0777);

    // Loop that iterates thru the input file to write spec char to output file, i
    // Includes 1st char, then skips n chars thereafter
    while (read(f_read, arr, 1))
    {
        lseek(f_read, n, SEEK_CUR);
        write(f_write, arr, 1);
    }
    close(f_write);
    close(f_read);
}

// Driver code
int main()
{
    char arr[100];
    int n;
    n = 2; // Changed this from original value n = 5,
           // reason is because we want to skip 2 chars at a time

    // Calling for the function
    func(arr, n);
    return 0;
}
