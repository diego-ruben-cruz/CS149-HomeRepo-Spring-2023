/**
 * Description:Define a function named SwapValues that takes four integers as parameters and swaps the first with the second, and the third with the fourth values. Then write a main program that reads four integers from input, 
 calls function SwapValues() to swap the values, and prints the swapped values on a single line separated with spaces.
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 03/19/2023
 * Creation Date: 03/19/2023
 */

#include <stdio.h>

void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4)
{
    int a = *userVal1;
    *userVal1 = *userVal2 ;
    *userVal2 = a ;
    
    int b = *userVal3;
    *userVal3 = *userVal4 ;
    *userVal4 = b ;
   
}

int main()
{
    int userVal1, userVal2, userVal3, userVal4;
    
    scanf("%d %d %d %d\n", &userVal1, &userVal2, &userVal3, &userVal4);
    
    SwapValues(&userVal1,&userVal2,&userVal3,&userVal4);
    printf("%d %d %d %d\n", userVal1, userVal2, userVal3, userVal4);
    return 0;
}


