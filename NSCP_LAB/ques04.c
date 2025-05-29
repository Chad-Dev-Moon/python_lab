#include <stdio.h>

int main()
{
    int i, j, k, n;
    float A[20][21], c, x[20], sum = 0;

    printf("Enter the order of the matrix: ");
    scanf("%d", &n);

    printf("Enter the elements of the augmented matrix row-wise:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n + 1; j++)
        {
            printf("A[%d][%d]: ", i + 1, j + 1);
            scanf("%f", &A[i][j]);
        }
    }

    // Forward elimination
    for (j = 0; j < n; j++)
    {
        for (i = 0; i < n; i++)
        {
            if (i > j)
            {
                c = A[i][j] / A[j][j];
                for (k = 0; k < n + 1; k++)
                {
                    A[i][k] = A[i][k] - c * A[j][k];
                }
            }
        }
    }

    // Back substitution
    x[n - 1] = A[n - 1][n] / A[n - 1][n - 1];
    for (i = n - 2; i >= 0; i--)
    {
        sum = 0;
        for (j = i + 1; j < n; j++)
        {
            sum += A[i][j] * x[j];
        }
        x[i] = (A[i][n] - sum) / A[i][i];
    }

    printf("\nThe solution is:\n");
    for (i = 0; i < n; i++)
    {
        printf("x[%d] = %f\n", i + 1, x[i]);
    }

    return 0;
}