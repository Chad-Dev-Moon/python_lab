#include <stdio.h>
#include <math.h>

float f(float x)
{
    return cosf(x) - x * expf(x);
}

float df(float x)
{
    return -sinf(x) - x * expf(x) - expf(x);
}

int main()
{
    float a, b;
    int i;
    printf("Enter initial approximation : ");
    scanf("%f", &a);
    for (i = 1; i <= 10; i++)
    {
        b = a - f(a) / df(a);
        if (fabsf(f(b)) < 0.0001)
        {
            printf("Actual root : %f\n", b);
            break;
        }
        else
        {
            a = b;
            printf("Approximation to this root is : %f\n", b);
        }
    }
    return 0;
}

// pseudo code:
// function f(x) returns cos(x) - x * exp(x)
// function df(x) returns -sin(x) - x * exp(x) - exp(x)
// main function
//     read initial approximation a
//     for i from 1 to 10
//         b = a - f(a) / df(a)
//         if |f(b)| < 0.0001
//             print "Actual root : ", b
//             break
//         else
//             a = b
//             print "Approximation to this root is : ", b
// end main function