#include <stdio.h>

// Function to calculate factorial
double factorial(int n)
{
    double fact = 1.0;
    for (int i = 2; i <= n; i++)
        fact *= i;
    return fact;
}

// Function to calculate forward differences table
void forwardDifferenceTable(double y[][20], int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            y[j][i] = y[j + 1][i - 1] - y[j][i - 1];
        }
    }
}

// Function to calculate the value using Newton's Forward Interpolation
double newtonForwardInterpolation(double x[], double y[][20], int n, double x_value)
{
    double h = x[1] - x[0];
    double u = (x_value - x[0]) / h;
    double result = y[0][0];
    double u_term = 1.0;

    for (int i = 1; i < n; i++)
    {
        u_term *= (u - (i - 1));
        result += (u_term * y[0][i]) / factorial(i);
    }
    return result;
}

int main()
{
    int n;
    double x[20], y[20][20], x_value;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter the values of x: ");
    for (int i = 0; i < n; i++)
        scanf("%lf", &x[i]);

    printf("Enter the corresponding values of y: ");
    for (int i = 0; i < n; i++)
        scanf("%lf", &y[i][0]);

    printf("Enter the value of x to interpolate: ");
    scanf("%lf", &x_value);

    forwardDifferenceTable(y, n);

    double result = newtonForwardInterpolation(x, y, n, x_value);

    printf("\nInterpolated value at x = %.4lf is: %.4lf\n", x_value, result);

    return 0;
}