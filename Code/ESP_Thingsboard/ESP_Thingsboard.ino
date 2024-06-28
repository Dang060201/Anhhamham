// rf95_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_client
// Tested with Anarduino MiniWirelessLoRa, Rocket Scream Mini Ultra Pro with
// the RFM95W, Adafruit Feather M0 with RFM95
 

#include <RHMesh.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
// #include <RHSUBGHZSPI.h>
// RHSUBGHZSPI SubGhz;
#define num 3
#define SCK    12
#define SS1    16
#define SS2    16
#define MOSI   14
#define MISO   13
#define DIO_1  39

#define RUN_LED 1

#define CLIENT22_ADDRESS  10
#define SERVER3_ADDRESS  250

const char* ssid = "LOH_TECH";
const char* password = "13579LOH";

const char* server = "demo.thingsboard.io"; // Đổi thành server của bạn nếu không sử dụng ThingsBoard demo
const int mqttPort = 1883;
const char* token = "E07Ayp63Kafhei281I3N";
// Singleton instance of the radio driver
RH_RF95 driver(SS1, DIO_1); // Rocket Scream Mini Ultra Pro with the RFM95W
// RHMesh *manager;
RHMesh manager(driver, SERVER3_ADDRESS);
WiFiClient espClient;
PubSubClient client(espClient);
HTTPClient http;

// uint8_t switchState[num];
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);
char temperature[num];
char humidity[num];
uint8_t data[num] ;
uint8_t from;
float temp[num];
float humi[num];
uint8_t state[num];
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP32Client", token, "")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      delay(5000);
    }
  }
}
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
  setup_wifi();
  client.setServer(server, mqttPort);
} 

void getAttributesFromThingsBoard() {
  WiFiClient espClient;

  
  // Định dạng URL để lấy dữ liệu từ attributes trên ThingsBoard
  String url = "/api/v1/";
  url += token;
  url += "/attributes";
  
  // Gửi yêu cầu HTTP GET tới ThingsBoard
  http.begin(espClient, server, 80, url.c_str()); // Chuyển đổi String thành const char*
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Response payload: " + payload);

  // Xử lý dữ liệu JSON nhận được
  DynamicJsonDocument doc(1024); // Để xử lý payload JSON động, tối đa 1024 bytes

  DeserializationError error = deserializeJson(doc, payload);
  
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
  }

    bool switchState[num];
    char switchs[7];
  // Kiểm tra và xử lý các attributes từ ThingsBoard
  // if (doc.containsKey("shared")) {
    for(int k = 0; k < num; k++)
    {
      sprintf(switchs,"switch%d",k);
      // Serial.println(switchs);
      switchState[k] = doc["shared"][switchs];
      Serial.println(switchState[k]);
      Serial.printf("Received switch attribute value %d : ",k);
      if(switchState[k]){
        state[k]= 1;
      }else{
        state[k]= 0;
      }
      Serial.println(state[k]);
    }  
        

    } else {
      Serial.print("HTTP GET failed, error code: ");
      Serial.println(httpCode);
    }
  } else {
    Serial.println("HTTP GET failed");
  }
  
  http.end();
} 

void publishData(){

    if (!client.connected()) {
    reconnect();
  }

  client.loop();

  StaticJsonDocument<200> jsonDocument;
  for(uint8_t k = 0; k < num; k++)
  {
    sprintf(temperature,"temp%d",k);
    sprintf(humidity,"humi%d",k);
    jsonDocument[temperature] = temp[k];
    jsonDocument[humidity] = humi[k];
  }
  // Chuyển JSON thành chuỗi để gửi đi
  char jsonBuffer[512];
  serializeJson(jsonDocument, jsonBuffer);

  // Gửi dữ liệu lên ThingsBoard
  char topic[50];
  sprintf(topic, "v1/devices/me/telemetry");

  delay(1000);

  if (client.publish(topic, jsonBuffer)) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }
}

void loop()
{ 
  Serial.println("ping client");
  for(int i=0;i<num;i++)
  {
    data[i]=state[i];
  }

  for(int i=0;i<num;i++)
  {

    if (manager.sendtoWait(data, sizeof(data), i) == RH_ROUTER_ERROR_NONE)
    {
      digitalWrite(RUN_LED, LOW);
      Serial.printf("Send to address %d \n",i);

      if(manager.recvfromAckTimeout(buf, &len, 200, &from))
      {
        digitalWrite(RUN_LED, HIGH);
        Serial.print("RSSI: ");
        Serial.println(driver.lastRssi(), DEC);
        temp[i] = (buf[0]<<8) + buf[1];
        temp[i] /= 100;
        humi[i] = (buf[2]<<8) + buf[3];
        humi[i] /= 100;
        Serial.println(temp[i]);
        Serial.println(humi[i]);
      }
      else
      {
        Serial.println("recv failed");
      }
    }
    else
    {
      digitalWrite(RUN_LED, LOW);
      Serial.printf("No reply, is client %d running? \n",i);
    }
    delay(300);
  }

  publishData();
  getAttributesFromThingsBoard();
  
  delay(1000); // Thời gian delay giữa các lần gửi dữ liệu
  
}