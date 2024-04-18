#include <wiringPi.h>
#include <pcf8574.h>
#define DeviceAddress 0x27 // Device addr
// #define PCF 199
const int PCF = 100; // Port offset
//

// Start of MAIN program.
//
int main(void)
{
 wiringPiSetupGpio();
pcf8574Setup(PCF, DeviceAddress);
lcd_init();
lcd_clear();
lcd_goto(1,0);
lcd_puts("Elektor");
delay(2000);
lcd_clear();
lcd_goto(3,1);
lcd_puts("ahihihi");
}