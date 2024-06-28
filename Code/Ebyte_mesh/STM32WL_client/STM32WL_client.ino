#define RH_SX126x_MAX_MESSAGE_LEN 50
#include <SPI.h>
#include <RH_STM32WLx.h>
#include <RHMesh.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"
#define RUN_LED PA0
#define RELAY PB3
#define num 2
#define CLIENT22_ADDRESS   0
#define SERVER3_ADDRESS  252
ClosedCube_HDC1080 hdc1080;
RH_STM32WLx driver;
RHMesh manager(driver, CLIENT22_ADDRESS);
 
HardwareSerial Serial2(PA3, PA2);
void setup() 
{
  Serial2.begin(115200);
  Wire.setSDA(PB7);
  Wire.setSCL(PB6);
  Wire.begin();
  hdc1080.begin(0x40);

  while (!Serial2) ; // Wait for serial port to be available
  Serial2.println("ClosedCube HDC1080 Arduino Test");

  // Initialize the RF95 module
  if (!driver.init()) {
    Serial2.println("RF95 module initialization failed");
    // while (1);
  }
  else
    Serial2.println("RF95 module initialization sucess");

  if (!manager.init())
    Serial2.println("init failed");
  else
    Serial2.println("init server sucess!");

  // driver.setModemConfig(LoRa_Bw125Cr45Sf128);
  driver.setFrequency(915.0);
  // driver.setSignalBandwidth(434.8);
  if(driver.setTxPower(22) == 1)
  {
    Serial2.println("Set power sucess!");
  }
  else
  {
    Serial2.println("Set power failed!");
  }
  // driver.setCADTimeout(10000);
  // driver.setTxContinuous();
  pinMode(RUN_LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
}

void loop()
{
  Serial2.printf("I'm %d \n", CLIENT22_ADDRESS);
  
  uint8_t buf[RH_SX126x_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  uint8_t from;
  uint16_t temp = hdc1080.readTemperature()*100;
  uint16_t humi = hdc1080.readHumidity()*100;

    driver.init();
  // Serial2.println("wait server ping");
  // if(driver.available())
  // {
    // Serial2.print(manager.recvfromAckTimeout(buf, &len,2100, &from));
    // Should be a message for us now   
    if(manager.recvfromAckTimeout(buf, &len, 200, &from))
    {
      digitalWrite(RUN_LED, HIGH);
      Serial2.print("got reply: ");
      for(int i=0;i<num;i++)
      {
        Serial2.println(buf[i]);
      }
      Serial2.print("\nRSSI: ");
      Serial2.println(driver.lastRssi(), DEC);
      uint8_t data[4];
      data[0] = temp >> 8;
      data[1] = temp & 0xff;
      data[2] = humi >> 8;
      data[3] = humi & 0xff;
      if (manager.sendtoWait(data, sizeof(data), from) == RH_ROUTER_ERROR_NONE)
      {
        Serial2.println("sendtoWait success");  
        digitalWrite(RUN_LED, LOW);
      }
      else
      {
        // Serial2.println(manager.sendtoWait(data, sizeof(data), from));
        Serial2.println("sendtoWait failed");
        Serial2.println(from);
        
      }  
    }
    else
    {
      Serial2.println("recv failed");
    }
    if(buf[CLIENT22_ADDRESS]==0){
      digitalWrite(RELAY, LOW);
    }else{
      digitalWrite(RELAY, HIGH);
    }
    

// }
}
