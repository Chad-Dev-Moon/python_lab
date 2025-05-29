#include <stdio.h>
#include <math.h>

// Function to integrate
double f(double x)
{
    return 1.0 / (1.0 + x * x);
}

int main()
{
    double a, b, h, sum;
    int n, i;

    printf("Enter lower limit : ");
    scanf("%lf", &a);
    printf("Enter upper limit : ");
    scanf("%lf", &b);
    printf("Enter number of sub-intervals (Multiple of 3) : ");
    scanf("%d", &n);

    if (n % 3 != 0 || n <= 0)
    {
        printf("Number of sub-intervals must be a positive multiple of 3.\n");
        return 1;
    }

    h = (b - a) / n;
    sum = f(a) + f(b);

    for (i = 1; i < n; i++)
    {
        if (i % 3 == 0)
        {
            sum += 2 * f(a + i * h);
        }
        else
        {
            sum += 3 * f(a + i * h);
        }
    }

    sum *= (3 * h / 8.0);

    printf("Approximate value of integral : %lf\n", sum);

    return 0;
}