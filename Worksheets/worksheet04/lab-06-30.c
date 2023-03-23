/**
 * Description:
 * Write a program whose inputs are four integers, and whose outputs are the maximum and the minimum of the four values.
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 2/25/2023
 * Creation Date: 2/25/2023
 */
#include <stdio.h>

// similar to what we did past worksheets, use ternary expressions to return minimum. Comparing two numbers and returning the lowest
int MinNumber(int num1, int num2, int num3, int num4)
{
    int min = num1; // set

    min = num2 < min ? num2 : min; // if num2 is less than num1, return num2, else current min
    min = num3 < min ? num3 : min; // if num3 is less than current min(num1/num2), else return current min
    min = num4 < min ? num4 : min; // if num4 is less than current min(n1/n2/n3) return num4, else current min

    return min;
}
// use ternary expressions to return max. Comparing two numbers and returning the max
int MaxNumber(int num1, int num2, int num3, int num4)
{
    int max = num1;
    max = num2 > max ? num2 : max; // if num2 > current max(num1), return num2, else keep current max
    max = num3 > max ? num3 : max;
    max = num4 > max ? num4 : max;
    return max;
}

// main: prompts user input for 4 numbers + returns min/max
int main(void)
{

    int num1, num2, num3, num4;
    printf("Enter 4 Numbers: ");
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4); // scan input s

    // print

    printf("Minimum is %d\n", MinNumber(num1, num2, num3, num4));
    printf("Maximum is %d\n", MaxNumber(num1, num2, num3, num4));
    return 0;
}
