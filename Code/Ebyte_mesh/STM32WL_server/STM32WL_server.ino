#define RH_SX126x_MAX_MESSAGE_LEN 50
#include <SPI.h>
#include <RH_STM32WLx.h>
#include <RHMesh.h>
#define RUN_LED PA0

#define CLIENT22_ADDRESS   20
#define SERVER3_ADDRESS  25

RH_STM32WLx driver;
RHMesh manager(driver, SERVER3_ADDRESS);
 
HardwareSerial Serial2(PA3, PA2);
// HardwareSerial Serial2(PB7, PB6);
void setup() 
{
  Serial2.begin(115200);
  while (!Serial2) ; // Wait for serial port to be available

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

  // driver.setModemConfig(LoRa_Bw125Cr48Sf4096);
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
}
  // Should be a reply message for us now  
// Now wait for a reply
uint8_t buf[RH_SX126x_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf); 

void loop()
{
  for(int i=50; i<53; i++)
      {Serial2.println("ping client ");

      // Send a message to stm32wlx_server
      uint8_t data[] = "Hello World!";
      uint8_t from;
      uint8_t a;
      a = manager.sendtoWait(data, sizeof(data), i);
      if (a == 0)
      {
        digitalWrite(RUN_LED, LOW);
        Serial2.printf("Send to address %d \n",i);
        // delay(200);
        Serial2.println(a);

        if(manager.recvfromAckTimeout(buf, &len, 200, &from))
        {
          digitalWrite(RUN_LED, HIGH);
          Serial2.print("got reply: ");
          Serial2.println((char*)buf);
          Serial2.print("RSSI: ");
          Serial2.println(driver.lastRssi(), DEC);
          
        }
        else
        {
          Serial2.printf("recv failed client %d \n",i);
        }
      }
      else
      {
        digitalWrite(RUN_LED, LOW);
        Serial2.printf("Don't send, is client %d \n",i);
        Serial2.println(a);
      }
    }
  delay(1000);
}
