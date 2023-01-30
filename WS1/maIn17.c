#include <stdio.h>

int main(void)
{
    int baseInt = 0;        //0
    int headInt = 1;        //1
    
    // %d  = decimal integer
    
    scanf("%d %d", &baseInt, &headInt); 
    //gets input value and puts into variable baseInt and headInt. 
    //&baseInt/headInt specifies where in memory the read value should be stored.

    printf("    %d\n", headInt);
    printf("    %d%d\n", headInt, headInt);
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
    printf("%d%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt, headInt);
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
    printf("    %d%d\n", headInt, headInt);
    printf("    %d\n", headInt);
    return 0;
}
