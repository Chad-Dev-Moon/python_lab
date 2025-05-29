#include <stdio.h>

// Function to calculate factorial
int fact(int n)
{
    int f = 1;
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

// Function to perform Newton's Backward Interpolation
double newtonBackward(double x[], double y[][10], int n, double value)
{
    // Calculate backward difference table
    for (int i = 1; i < n; i++)
    {
        for (int j = n - 1; j >= i; j--)
        {
            y[j][i] = y[j][i - 1] - y[j - 1][i - 1];
        }
    }
    // Find value of u
    double h = x[1] - x[0];
    double u = (value - x[n - 1]) / h;
    double result = y[n - 1][0];
    double term = 1;
    for (int i = 1; i < n; i++)
    {
        term *= (u + i - 1);
        result += (term * y[n - 1][i]) / fact(i);
    }
    return result;
}

int main()
{
    int n;
    double x[10], y[10][10];
    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter the values of x:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &x[i]);
    }

    printf("Enter the corresponding values of y:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &y[i][0]);
    }

    double value;
    printf("Enter the value of x to interpolate: ");
    scanf("%lf", &value);

    double result = newtonBackward(x, y, n, value);
    printf("\nInterpolated value at x = %.4lf is: %.4lf\n", value, result);

    return 0;
}