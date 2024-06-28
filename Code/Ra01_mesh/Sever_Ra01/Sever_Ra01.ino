// rf95_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_client
// Tested with Anarduino MiniWirelessLoRa, Rocket Scream Mini Ultra Pro with
// the RFM95W, Adafruit Feather M0 with RFM95
 
#include <RH_RF95.h>
#include <RHMesh.h>
#include <SPI.h>
// #include <RHSUBGHZSPI.h>
// RHSUBGHZSPI SubGhz;
#define SCK    12
#define SS1    16
#define SS2    16
#define MOSI   14
#define MISO   13
#define DIO_1  39

#define RUN_LED 1

#define CLIENT22_ADDRESS   20
#define SERVER3_ADDRESS  252
// Singleton instance of the radio driver
RH_RF95 driver(SS1, DIO_1); // Rocket Scream Mini Ultra Pro with the RFM95W
 
// RHMesh *manager;
RHMesh manager(driver, SERVER3_ADDRESS);
 
void setup() 
{
  Serial.begin(115200);

  SPI.begin(SCK, MISO, MOSI, SS1);

  // SubGhz.begin();

  if (!driver.init()) {
    Serial.println("RF module initialization failed");
  } else {
    Serial.println("RF module initialization successful");
  }
  
  if (!manager.init())
    Serial.println("init failed");  
    
  driver.setFrequency(915.0);
  driver.setTxPower(22);
}
 
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf); 
uint8_t addr = 21;
void loop()
{ 
  Serial.println("ping client");

  // Send a message to stm32wlx_server
  uint8_t data[] = "Hello World!";
  uint8_t from;
  if (manager.sendtoWait(data, sizeof(data), addr) == RH_ROUTER_ERROR_NONE)
  {
    digitalWrite(RUN_LED, LOW);
    Serial.printf("Send to address %d\n", addr);

    if(manager.recvfromAckTimeout(buf, &len, 2000, &from))
    {
      digitalWrite(RUN_LED, HIGH);
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(driver.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    digitalWrite(RUN_LED, LOW);
    Serial.println("No reply, is stm32wlx_server running?");
  }
  addr++;
  if(addr > 22)
  {
    addr = 21;
  }
}