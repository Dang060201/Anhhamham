#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <DHT22Lib.h>
#include <curl/curl.h>

#define THINGSBOARD_URL "https://demo.thingsboard.io/api/v1/qiUV09JFkUVl6kuo6rLz/telemetry"
#define DHT_PIN 2

int main(int argc, char* argv[]) {
    int Temp, Hum;
    CURL *curl;
    CURLcode res;

    wiringPiSetupGpio();
    delay(1000);

    while (1)
   
    {
        curl = curl_easy_init();
        if(curl) {
            Read_DHT22(&Temp, &Hum, DHT_PIN);
            char payload[100];
            sprintf(payload, "{\"temperature\":%d,\"humidity\":%d}", Temp, Hum);

            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, THINGSBOARD_URL);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
            }
        delay(6000);
    }

    return 0;
}
