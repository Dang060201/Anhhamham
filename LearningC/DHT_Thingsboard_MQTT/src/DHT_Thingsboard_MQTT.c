#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <DHT22Lib.h>
#include <MQTTClient.h>

#define ADDRESS     "demo.thingsboard.io"
#define CLIENTID    "6a13c980-6cdc-11ed-b78f-b9a3f0002242"
#define TOPIC       "v1/devices/me/telemetry"
#define QOS         1
#define TIMEOUT     10000L
#define DHT_PIN     2
#define ACCESS_TOKEN "OmUEGmnxmJBK0i6rm7kI"

void deliveryComplete(void* context, MQTTClient_deliveryToken dt) {
    printf("Message with token value %d delivery confirmed\n", dt);
}

int main(int argc, char* argv[]) {
    int rc;
    int Temp, Hum;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    wiringPiSetupGpio();
    delay(1000);

    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to create MQTT Client, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = ACCESS_TOKEN;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect to MQTT broker, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    printf("Connected to MQTT broker\n");

    while(1) {
        Read_DHT22(&Temp, &Hum, DHT_PIN);
        // Temp = 20;
        // Hum = 60;
        char payload[100];
        sprintf(payload, "{\"Temperature\":%d,\"Humidity\":%d}", Temp, Hum);
        pubmsg.payload = payload;
        pubmsg.payloadlen = strlen(payload);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
        printf("Message sent: %s\n", payload);
        delay(6000); // delay 1 minute
    }

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return rc;
}
