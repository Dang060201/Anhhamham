// rf95_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_server
// Tested with Anarduino MiniWirelessLoRa, Rocket Scream Mini Ultra Pro with
// the RFM95W, Adafruit Feather M0 with RFM95
 
#include <SPI.h>
#include <RH_RF95.h>
#include <RHMesh.h>
#include <Wire.h>


#define MOSI  7
#define MISO  2
#define SCK   6
#define SS    9
#define DIO   0
 
// #define SCK    12
// #define SS    16
// // #define SS2    16
// #define MOSI   14
// #define MISO   13
// #define DIO  39

#define RUN_LED 1
#define MQ4_DO_PIN 26 //TX
#define MP2_DO_PIN 27 //RX

#define CLIENT22_ADDRESS   50
#define SERVER3_ADDRESS  252
// Singleton instance of the radio driver
// RH_RF95 rf95(9, 0); // Rocket Scream Mini Ultra Pro with the RFM95W
RH_RF95 rf95(SS, DIO); // Rocket Scream Mini Ultra Pro with the RFM95W
 
// RHMesh *manager;
RHMesh manager(rf95, CLIENT22_ADDRESS);
// Need this on Arduino Zero with SerialUSB port (eg RocketScream Mini Ultra Pro)
//#define Serial SerialUSB
 
void setup() 
{
  Serial.begin(115200);

  SPI.begin(SCK, MISO, MOSI, SS);

  // manager = new RHMesh(rf95, CLIENT22_ADDRESS);
  while (!Serial) ; // Wait for serial port to be available
  if (!manager.init())
    Serial.println("init failed");
  else
    Serial.println("init client sucess!");

  rf95.setFrequency(915.0);
  // driver.setSignalBandwidth(434.8);
  rf95.setTxPower(22);
}
uint8_t data[2];
void loop()
{
  Serial.println("Sending to rf95_server");
  // Send a message to rf95_server
  // rf95.send(data, sizeof(data));
  Serial.printf("I'm %d \n", CLIENT22_ADDRESS);
  // rf95.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  uint8_t from;
 
  if (manager.recvfromAckTimeout(buf, &len, 200, &from))
  {
    digitalWrite(RUN_LED, HIGH);
    Serial.print("got request: ");
    Serial.println((char*)buf);
    Serial.print("RSSI: ");
    Serial.println(rf95.lastRssi(), DEC);
    
    // Send a reply
    uint8_t data[] = "And hello back to you";
    // Should be a reply message for us now   
    if (manager.sendtoWait(data, sizeof(data), from) == RH_ROUTER_ERROR_NONE)
    {
      Serial.println("sendtoWait success");  
    }
    else
    {
      Serial.println("sendtoWait failed");
    }
  }
  else
  {
    digitalWrite(RUN_LED, LOW);
    Serial.println("recv failed");
  }
}