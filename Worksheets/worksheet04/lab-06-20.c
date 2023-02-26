/**
 * Description:
 *
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 2/27/2023
 * Creation Date: 2/25/2023
 */
#include <stdio.h>

/**
 * Basic function to run conversion from laps to miles
 *
 * @param userLaps The number of laps to be converted
 * @return The number of miles
 */
double lapsToMiles(double userLaps)
{
    return userLaps * 0.25;
}

/**
 * Main function, collects user input and makes use of the function to return a conversion
 */
int main(void)
{
    double userInput; // User variable to store input

    // User prompt to collect the number of laps run
    printf("Please enter the number of laps you have done: ");
    scanf("%lf", &userInput);

    double resultingValue = lapsToMiles(userInput); // uses function to return lap-to-mile conversion
                                                    // Honestly could just do the conversion in the
                                                    // printf statement, but did this for showcase/simplicity

    // Print statement to output value
    printf("\nThe resulting number of miles is: %0.2lf", resultingValue);

    return 0; // default exit code for program
              // since nothing gets output
}
