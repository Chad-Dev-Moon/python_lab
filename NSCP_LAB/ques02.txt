#include <stdio.h>
#include <math.h>
float f(float x)
{
    return x * x * x - x - 11;
}
float regularfalse(float a, float b)
{
    float c, fa, fb, fc;
    int i = 1;
    do
    {
        fa = f(a);
        fb = f(b);
        // c = (a * fb - b * fa) / (fb - fa); // slower
        c = b - (fb * (b - a)) / (fb - fa); // faster
        fc = f(c);
        if (fa * fc < 0)
            b = c;
        else
            a = c;
        printf("Iteration : %d\n", i);
        printf("root : %f\n", c);
        i++;
    } while (fa != fc && fb != fc);
    return c;
}
int main()
{
    float a, b;
    printf("Enter the values of a and b : ");
    scanf("%f %f", &a, &b);
    float root = regularfalse(a, b);
    printf("The root is : %f\n", root);
}
