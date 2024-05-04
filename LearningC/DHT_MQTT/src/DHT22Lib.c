#include <DHT22Lib.h>
#include <wiringPi.h>

int WaitEdge(int mode, int PIN) {
    int counter = 0;
    while (digitalRead(PIN) == mode) {
        counter++;
        delayMicroseconds(1);
        if (counter == 255) return 1;
    }
    return 0;
}

void Read_DHT22(int *T, int *H, int DHT_PIN) {
    char res, i, state, counter, indx = 0;
    int data[5];
    for (i = 0; i < 5; i++) data[i] = 0;
    pinMode(DHT_PIN, OUTPUT);
    digitalWrite(DHT_PIN, LOW);
    delay(18);
    digitalWrite(DHT_PIN, HIGH);
    delayMicroseconds(40);
    pinMode(DHT_PIN, INPUT);
    res = WaitEdge(0,DHT_PIN);
    res = res + WaitEdge(1,DHT_PIN);
    i = 0;
    while (i < 80 && res == 0) {
        counter = 0;
        if (WaitEdge(0,DHT_PIN) == 1) break;
        while (digitalRead(DHT_PIN) == HIGH) {
            counter++;
            delayMicroseconds(1);
            if (counter == 255) break;
        }
        data[indx / 8] <<= 1;
        if (counter > 28) data[indx / 8] |= 1;
        indx++;
        i++;
    }

    // Check the Checksum
    if ((indx >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))) {
        *H = ((data[0] << 8) + data[1]) / 10; // Humidity
        *T = (((data[2] & 0x7F) << 8) + data[3]) / 10; // Temperature
        if (data[2] & 0x80) *T = -(*T); // Negative temperature
    }
}