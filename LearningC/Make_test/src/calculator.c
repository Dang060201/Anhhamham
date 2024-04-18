#include <stdio.h>

#include "userheader.h"

int add(int a, int b)
{
    return (a + b);
}

int sub(int a, int b)
{
    if (a > b)
        return (a - b);
    else if (a < b)
        return (b - a);
    else return 0;
}

int mul(int a, int b)
{
    return (a * b);
}

double div(int a, int b)
{

    if (a > b)
        return ((double)a / (double)b);
    else if (a < b)
        return ((double)b / (double)a);
    else
        return 0;
}