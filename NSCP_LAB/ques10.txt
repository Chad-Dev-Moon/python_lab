#include <stdio.h>
#include <windows.h>

// Function to calculate f(x, y)
float f(float x, float y)
{
    return (x * x + y * y) / 10.0;
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, 1);

    float x0 = 0.2, y0 = 2.0, xn = 2.0, h = 0.2;
    float k1, k2, k3, k4;
    int i, n;

    n = (int)((xn - x0) / h);

    printf("Solve dy/dx = (x^2 + y^2) / 10\n");
    printf("Initial condition: x0 = %.2f, y0 = %.2f\n", x0, y0);
    SetConsoleTextAttribute(hConsole, 2);
    printf("|--------|--------|\n");
    printf("|%8c|%8c|\n", 'x', 'y');
    printf("|--------|--------|\n");

    for (i = 0; i <= n; i++)
    {
        SetConsoleTextAttribute(hConsole, 6);
        printf("| %.4f | %.4f |\n", x0, y0);

        k1 = h * f(x0, y0);
        k2 = h * f(x0 + h / 2.0, y0 + k1 / 2.0);
        k3 = h * f(x0 + h / 2.0, y0 + k2 / 2.0);
        k4 = h * f(x0 + h, y0 + k3);

        y0 = y0 + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
        x0 = x0 + h;
    }

    // Restore original attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
    return 0;
}