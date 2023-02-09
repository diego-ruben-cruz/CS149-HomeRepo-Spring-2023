/**
 * Description:
 * Given three floating-point numbers x, y, and z,
 *
 * output x to the power of z,
 * x to the power of (y to the power of 2),
 * the absolute value of y,
 * and the square root of (xy to the power of z).
 *
 * Output each floating-point value with two digits after the decimal point,
 * which can be achieved as follows:
 * printf("%0.2lf", yourValue);
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
#include <math.h>

int main(void)
{
    double x;
    double y;
    double z;

    // Takes in the three numbers separated by a space,
    // Used float instead of zybooks double to save on storage space,
    // since the program only requires two dec spaces to be displayed.
    printf("Please input three numbers (x, y, and z) separated by a space between them: ");
    scanf("%lf %lf %lf", &x, &y, &z);

    printf("\nBelow are the computations made with your input\n");
    // Outputs x to the power of z
    printf("x to the power of z: %0.2lf\n", pow(x, z));

    // prints out x to the power of y^2
    printf("x to the power of (y to the power of 2): %0.2lf\n", pow(x, pow(y, 2)));

    // prints out absolute value of y
    printf("Absolute value of y: %0.2lf\n", fabs(y));

    // prints out complex square root operation.
    printf("Square root of (xy to the power of z): %0.2lf\n", sqrt(pow(x * y, z)));

    return 0;
}