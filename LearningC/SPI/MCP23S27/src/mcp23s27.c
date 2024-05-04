/*------------------------------------------------------------------
 MCP23S17 SPI LED FLASH
 ======================
In this program an LED is connected to MCP23S17 chip which is a SPI
based chip. The program flashes the LED every second
The MCP23S17 chip is programmed from first principles
Author: Dogan Ibrahim
File : SPILED2.c
Date : December 2020
--------------------------------------------------------------------*/
#include <wiringPiSPI.h>
#include <wiringPi.h>
#define SPI_Address 0x40 // Device addr
#define channel 0 // Use CE0
#define MCP_GPIOA 0x12 // GPIOA
#define MCP_IODIRA 0 // IODIRA
int handle;
//
// This function configures the MCP23S17. I/O direction for PORTA
// is set as output
//
void configure()
{
char buff[3];
buff[0]=SPI_Address;
buff[1] = MCP_IODIRA;
buff[2] = 0;
wiringPiSPIDataRW(handle, buff, 3);
}
//
// This function sends data to port GPIOA
//
void send(char RegAddr, char data)
{
char buff[3];
buff[0]=SPI_Address;
buff[1] = RegAddr;
buff[2] = data;
wiringPiSPIDataRW(handle, buff, 3);
}
//
// Start of MAIN program
//
int main(void)
{
 wiringPiSetupGpio();
handle = wiringPiSPISetup(channel, 1000000);
configure();
while(1)
{
 send(0x12, 0); // GPIOA (LED ) ON
 delay(1000); // 1 sec delay
 send(0x12, 1); // GPIOA (LED) OFF
 delay(1000); // 1 sec delay
}
}