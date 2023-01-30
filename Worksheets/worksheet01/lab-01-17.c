/**
 * Description:
 * Given two input integers for an arrow body and arrowhead (respectively), 
 * print a right-facing arrow.
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified:
 * Creation Date:
 */
#include <stdio.h>

int main(void)
{
    int baseInt = 0 ;        //0
    int headInt = 1 ;        //1
    
    // %d  = decimal integer
    
    scanf("%d %d", &baseInt, &headInt); 
    //gets input value and puts into variable baseInt and headInt. 
    //&baseInt, &headInt specifies where in memory the read value should be stored.

    printf("    %d\n", headInt); //4 space right
    printf("    %d%d\n", headInt, headInt);  //%d is porportional to amount of decimal variables. 
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
    printf("%d%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt, headInt);
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
    printf("    %d%d\n", headInt, headInt);
    printf("    %d\n", headInt);
    return 0;
}
