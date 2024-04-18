#include <stdio.h>

#include "userheader.h"

int main()
{
    greeter_func();

    printf("\nAdding 5 and 10 together gives us '%d'.\n", add(5, 10));
    printf("Subtracting 10 from 32 results in '%d'.\n", sub(10, 32));
    printf("If 43 is  multiplied with 2, we get '%d'.\n", mul(43, 2));
    printf("The result of dividing any even number like 78 with 2 is a whole number like '%f'.\n", div(78, 2));

    return 0;
}