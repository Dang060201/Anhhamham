extern int PCF;
#include <wiringPi.h>
#define RS PCF+0 // RS pin
#define RW PCF+1 // RW pin
#define E PCF+2 // E pin
#define LED PCF+3 // Backlight
#define D4 PCF+4 // D4 pin
#define D5 PCF+5 // D5 pin
#define D6 PCF+6 // D6 pin
#define D7 PCF+7 // D7 pin
void lcd_strobe(void);
void lcd_write(unsigned char c, int mode) //0=cmd,1=data
{
unsigned char d, b,i;
d = c;
d = (d >> 4); // Upper nibble
for(i = 0; i < 4; i++)
{
 b = d & 1;
 digitalWrite(PCF+4+i,b); // Set pins
 d = d >> 1;
}
digitalWrite(RS, mode);
lcd_strobe();
d = c;
for(i = 0; i < 4; i++)
{
 b = d & 1;
 digitalWrite(PCF+4+i, b);
 d = d >> 1;
}
digitalWrite(RS, mode);
lcd_strobe();
delay(0.1);
digitalWrite(RS, 1);
}
//
// This function send strobe pulse to LCD
//
void lcd_strobe(void)
{
digitalWrite(E, 1);
delay(0.1);
digitalWrite(E, 0);
delay(0.1);
}
//
// This function clears the LCD
//
void lcd_clear(void)
{
lcd_write(0x01, 0);
delay(5);
}
//
// This function homes the cursor
//
void lcd_home(void)
{
lcd_write(0x02, 0);
delay(5);
}
//
// This function sets cursor blinking ON
//
void lcd_cursor_blink_on(void)
{
lcd_write(0x0D, 0);
delay(1);
}
//
// This function sets cursor blinking OFF
//
void lcd_cursor_blink_off(void)
{
lcd_write(0x0C, 0);
delay(1);
}
//
// This function sets cursor ON
//
void lcd_cursor_on(void)
{
lcd_write(0x0E, 0);
delay(1);
}
//
// This function sets cursor OFF
//
void lcd_cursor_off(void)
{
lcd_write(0x0C, 0);
delay(1);
}
//
// This function displays string
//
void lcd_puts(const char *s)
{
while(*s) lcd_write(*s++, 1);
}
//
// This function displays a character
//
void lcd_putch(unsigned char c)
{
lcd_write(c, 1);
}
//
// This function positions cursor at col,row. Top left is 0,0
//
void lcd_goto(int col, int row)
{
char address, c;
c = col + 1;
if(row == 0)address = 0;
if(row == 1)address = 0x40;
address += c - 1;
lcd_write(0x80 | address, 0);
}
//
// This function initializes the LCD
//
void lcd_init(void)
{
char i;
delay(120);
for(i = 0; i < 8; i++)digitalWrite(PCF+i, 0);
delay(50);
digitalWrite(D4, 1); digitalWrite(D5, 1);
lcd_strobe();
delay(10);
lcd_strobe();
delay(10);
lcd_strobe();
delay(10);
digitalWrite(D4, 0);
lcd_strobe();
delay(5);
lcd_write(0x28, 0); //28
delay(1);
lcd_write(0x08,0); //0f
delay(1);
lcd_write(0x01,0);
delay(10);
lcd_write(0x06,0);
delay(5);
lcd_write(0x0C,0);
delay(10);
digitalWrite(LED, 1);
}
