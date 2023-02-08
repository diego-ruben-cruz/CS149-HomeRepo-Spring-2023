/**
 * Description:
 * Write a program whose inputs are three integers, and whose output is the smallest of the three values.
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 2/07/2023
 * Creation Date: 2/07/2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void) {
    int x, y, z;
    int min1, min2;
    /* 1. Scan*/
    scanf("%d %d %d", &x, &y, &z);
    // 2. Two methods to find min : Array or Ternary expression
    min1 = x < y ? x : y;    //Read this as if/else statement, if x<y return x... if not x:y means return y
    //min1 is going to return the smallest of either x or y
//now compare to z
    min2 = min1 < z ? min1 : z;
    printf("%d\n", min2);

    return 0;

    /* By array
    1). Initialize array [2] for 3 inputs
    2).  for loop to put the inputs into array, then another for loop to compare each index with each other and return minimum
    */
}
