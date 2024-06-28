#include <Wire.h>
#include "ClosedCube_HDC1080.h"
ClosedCube_HDC1080 hdc1080;
HardwareSerial Serial2(PA3, PA2);

void setup()
{
  Serial2.begin(115200);
  Serial2.println("ClosedCube HDC1080 Arduino Test");
  Wire.setSDA(PB7);
  Wire.setSCL(PB6);
  Wire.begin();



// Default settings:
// - Heater off
// - 14 bit Temperature and Humidity Measurement Resolutions
hdc1080.begin(0x40);

Serial2.print("Manufacturer ID=0x");
Serial2.println(hdc1080.readManufacturerId(), HEX); // 0x5449 ID of Texas Instruments
Serial2.print("Device ID=0x");
Serial2.println(hdc1080.readDeviceId(), HEX); // 0x1050 ID of the device


}

void loop()
{
Serial2.print("T=");
Serial2.print(hdc1080.readTemperature());
Serial2.print("C, RH=");
Serial2.print(hdc1080.readHumidity());
Serial2.println("%");
delay(3000);
}
