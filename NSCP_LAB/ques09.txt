#include <stdio.h>
#include <math.h>

#define f(x) (1.0 / (1 + pow(x, 2)))

int main()
{
    float lower, upper, integration = 0.0, stepSize, k;
    int subInterval, i;

    // Input
    printf("Enter lower limit of integration : ");
    scanf("%f", &lower);
    printf("Enter the upper limit of integration : ");
    scanf("%f", &upper);
    printf("Enter number of sub intervals: ");
    scanf("%d", &subInterval);

    // Step size
    stepSize = (upper - lower) / subInterval;

    // Apply trapezoidal rule
    integration = f(lower) + f(upper);
    for (i = 1; i < subInterval; i++)
    {
        k = lower + i * stepSize;
        integration += 2 * f(k);
    }
    integration = integration * stepSize / 2;

    printf("Required value of integration is : %.6f\n", integration);

    return 0;
}