#include <stdio.h>
#include <math.h>
#define f(x) x *x *x - x - 11
int main()
{
    float x0, x1, x2, f0, f1, f2;
    int i = 0;
    float e = 0.001;
    printf("Enter x0, x1: ");
    scanf("%f %f", &x0, &x1);
    do
    {
        f0 = f(x0);
        f1 = f(x1);
        x2 = (x0 + x1) / 2;
        f2 = f(x2);
        if (f0 * f2 < 0)
        {
            x1 = x2;
        }
        else
        {
            x0 = x2;
        }
        i++;
        printf("root = %f\n", x2);
        printf("value of function : %f\n", f2);
    } while (fabsf(f2) > e);
    return 0;
}