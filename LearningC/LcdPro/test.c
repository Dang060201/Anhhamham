#include <stdio.h>
#include "liblcd.h"
#include <wiringPi.h>
#define DeviceAddress 0x27 // Device addr
const int PCF = 100; // Port offset
int main()
{
    unsigned char d, b,i,c;
    c = 'c';
d = c;
d = (d >> 4); // Upper nibble
printf("%d\n",d);
for(i = 0; i < 4; i++)
{
 b = d & 1;
printf("%d\n",b);
 digitalWrite(PCF+4+i,b); // Set pins
 d = d >> 1;
 printf("%d\n",d);
}
digitalWrite(PCF, 1);
lcd_strobe();
d = c;
printf("%d k\n",d);
for(i = 0; i < 4; i++)
{
 b = d & 1;
 printf("%d\n",b);
 digitalWrite(PCF+4+i, b);
 d = d >> 1;
 printf("%d\n",d);
}
digitalWrite(PCF, 1);
lcd_strobe();
delay(0.1);
digitalWrite(PCF, 1);
}
