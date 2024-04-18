#include <stdio.h>

#include "userheader.h"
#include<wiringPi.h>

void greeter_func()
{
    printf("Hello, user! I hope you are ready for today's basic Mathematics class!\n");
    delay(2000);
}