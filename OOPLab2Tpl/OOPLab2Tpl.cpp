#include <iostream>
#include <fstream>
#include <string>

int calculateExpression(int a, int b, int c, int d) {
    int result = 0;

    // Multiply a by 15 using bitwise shift operations
    int aBy15 = (a << 4) + a;

    // Multiply b by 312 using bitwise shift operations
    int bBy312 = (b << 8) - (b << 3);

    // Divide aBy15 by 64 using bitwise shift operations
    int aBy15Div64 = aBy15 >> 6;

    // Divide bBy312 by 64 using bitwise shift operations
    int bBy312Div64 = bBy312 >> 6;

    // Add aBy15Div64 and bBy312Div64
    int sum = aBy15Div64 + bBy312Div64;

    // Subtract c multiplied by 120
    int cMul120 = (c << 3) + (c << 5);
    sum -= cMul120;

    // Add d multiplied by 121
    int dMul121 = (d << 7) + d + (d << 4);
    sum += dMul121;

    result = sum;
    return result;
}