/**
 * Description:
 * Write a program using integers userNum and x as input, and output userNum divided by x three times.
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

int main(void) {

	/* Type your code here. */
	int userNum;
	int x;
    printf("Enter two numbers:");
	scanf("%d %d", &userNum, &x); //User Input: use & to reference memory location of userNum and x when initializing
	/*need to make  userNum/x once, then result/x, then result1/x--            */
	/*Example input   2000/2   ,     1000/2         ,  500/2                   */

	int div1 = userNum / x;
	int div2 = div1 / x;   //Prev result/x 
	int div3 = div2 / x;   //Prev result/x
	/* In C, integer division discards fractions. Ex: 6 / 4 is 1 (the 0.5 is discarded). */

	printf("%d %d %d\n", div1, div2, div3);
	return 0;
}
