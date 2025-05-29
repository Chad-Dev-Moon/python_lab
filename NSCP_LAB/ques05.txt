#include <stdio.h>

int main()
{
    int n, i, j, k;
    double a[20][21], x[20];

    printf("Enter number of variables: ");
    scanf("%d", &n);

    printf("Enter the augmented matrix (coefficients and constants):\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= n; j++)
        {
            scanf("%lf", &a[i][j]);
        }
    }

    // Gauss-Jordan Elimination
    for (i = 0; i < n; i++)
    {
        // Make the diagonal element 1
        double diag = a[i][i];
        for (j = 0; j <= n; j++)
        {
            a[i][j] /= diag;
        }
        // Make the off-diagonal elements 0 in the current column
        for (k = 0; k < n; k++)
        {
            if (k != i)
            {
                double ratio = a[k][i];
                for (j = 0; j <= n; j++)
                {
                    a[k][j] -= ratio * a[i][j];
                }
            }
        }
    }

    // Solution
    printf("\nSolution:\n");
    for (i = 0; i < n; i++)
    {
        x[i] = a[i][n];
        printf("x%d = %.4lf\n", i + 1, x[i]);
    }

    return 0;
}